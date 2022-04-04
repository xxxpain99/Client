#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

enum OPERATION {
	OPEN,
	CLOSE,
	UP,
	DOWN
};

struct Data {
	int UserID;
	double value;
	char Name[32];
	OPERATION Operation;
};

Data userData;
void ReadServer(SOCKET);

void PrintCommand()
{
	std::cout << "0 - open new bill\n";
	std::cout << "1 - close old bill\n";
	std::cout << "2 - up bill\n";
	std::cout << "3 - down bill\n";
}

int main()
{
	std::cout << "Enter your name: ";
	std::cin >> userData.Name;
	std::cout << "\n";

	WSADATA data;
	int e = WSAStartup(MAKEWORD(2, 2), &data);
	if (e != 0)
	{
		cout << "data has destroyed and annihilation\n";
		return e;
	}
	SOCKET clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket < 0)
	{
		cout << "server has destroyed\n";
		return 1;
	}
	sockaddr_in serverAddress;
	memset((&serverAddress), 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.S_un.S_un_b.s_b1 = 127;
	serverAddress.sin_addr.S_un.S_un_b.s_b2 = 0;
	serverAddress.sin_addr.S_un.S_un_b.s_b3 = 0;
	serverAddress.sin_addr.S_un.S_un_b.s_b4 = 1;
	int error = connect(clientSocket, (sockaddr*)(&serverAddress), sizeof(serverAddress));
	if (error != 0) {
		cout << "server has infested 1\n";
		return error;
	}
	int operation;
	new std::thread(ReadServer, clientSocket);
	while (true)
	{
		PrintCommand();
		std::cout << "\n";
		std::cin >> operation;
		std::cout << "\n";
		userData.Operation = (OPERATION)operation;
		switch (operation)
		{
		case OPERATION::UP:
			std::cout << "Enter bill number\n";
			break;
		case OPERATION::DOWN:
			std::cout << "Enter bill number\n";
			break;
		case OPERATION::CLOSE:
			std::cout << "Enter bill number\n";
			break;
		default:
			break;
		}

		int n = send(clientSocket, (char*)(&userData), sizeof(userData), 0);
		if (n < 0)
		{
			closesocket(clientSocket);
			return -1;
		}
	}

	return 0;
}


        void ReadServer(SOCKET s) {
	      int n = 0;
	      Data recvData;
          while (true) {
	      n = recv(s, (char*)(&recvData), sizeof(recvData), 0);
	      if (n < 0) {
	 	closesocket(s);
		cout << "server has infested\n";
			return;
		}

	}
}


