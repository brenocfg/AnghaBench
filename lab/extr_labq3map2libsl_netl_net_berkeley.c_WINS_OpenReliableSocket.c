#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
typedef  int qboolean ;
typedef  int /*<<< orphan*/  address ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  WINS_ErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  WinPrint (char*,...) ; 
 int bind (int,void*,int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int WINS_OpenReliableSocket( int port ){
	int newsocket;
	struct sockaddr_in address;
	qboolean _true = 0xFFFFFFFF;

	//IPPROTO_TCP
	//
	if ( ( newsocket = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 ) {
		WinPrint( "WINS_OpenReliableSocket: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		return -1;
	} //end if

	memset( (char *) &address, 0, sizeof( address ) );
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl( INADDR_ANY );
	address.sin_port = htons( (u_short)port );
	if ( bind( newsocket, (void *)&address, sizeof( address ) ) == -1 ) {
		WinPrint( "WINS_OpenReliableSocket: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		closesocket( newsocket );
		return -1;
	} //end if

	//
	if ( setsockopt( newsocket, IPPROTO_TCP, TCP_NODELAY, (void *) &_true, sizeof( int ) ) == -1 ) {
		WinPrint( "WINS_OpenReliableSocket: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		WinPrint( "setsockopt error\n" );
	} //end if

	return newsocket;
}