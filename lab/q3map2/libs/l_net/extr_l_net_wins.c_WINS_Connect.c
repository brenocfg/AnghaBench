#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_long ;
struct sockaddr_s {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  WINS_ErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  WinPrint (char*,int /*<<< orphan*/ ) ; 
 int connect (int,struct sockaddr*,int) ; 
 int ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 

int WINS_Connect( int socket, struct sockaddr_s *addr ){
	int ret;
	u_long _true2 = 0xFFFFFFFF;

	ret = connect( socket, (struct sockaddr *)addr, sizeof( struct sockaddr_s ) );
	if ( ret == SOCKET_ERROR ) {
		WinPrint( "WINS_Connect: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		return -1;
	} //end if
	if ( ioctlsocket( socket, FIONBIO, &_true2 ) == -1 ) {
		WinPrint( "WINS_Connect: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		return -1;
	} //end if
	return 0;
}