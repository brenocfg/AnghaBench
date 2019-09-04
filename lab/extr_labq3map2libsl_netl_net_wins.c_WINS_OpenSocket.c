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
typedef  int u_long ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
typedef  int /*<<< orphan*/  address ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  WINS_ErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  WinPrint (char*,int /*<<< orphan*/ ) ; 
 int bind (int,void*,int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int WINS_OpenSocket( int port ){
	int newsocket;
	struct sockaddr_in address;
	u_long _true = 1;

	if ( ( newsocket = socket( PF_INET, SOCK_DGRAM, IPPROTO_UDP ) ) == -1 ) {
		WinPrint( "WINS_OpenSocket: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		return -1;
	} //end if

	if ( ioctlsocket( newsocket, FIONBIO, &_true ) == -1 ) {
		WinPrint( "WINS_OpenSocket: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		closesocket( newsocket );
		return -1;
	} //end if

	memset( (char *) &address, 0, sizeof( address ) );
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( (u_short)port );
	if ( bind( newsocket, (void *)&address, sizeof( address ) ) == -1 ) {
		WinPrint( "WINS_OpenSocket: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		closesocket( newsocket );
		return -1;
	} //end if

	return newsocket;
}