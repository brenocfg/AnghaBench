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

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  WINS_ErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  WinPrint (char*,int /*<<< orphan*/ ) ; 
 int ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 

int WINS_Listen( int socket ){
	u_long _true = 1;

	if ( ioctlsocket( socket, FIONBIO, &_true ) == -1 ) {
		WinPrint( "WINS_Listen: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		return -1;
	} //end if
	if ( listen( socket, SOMAXCONN ) == SOCKET_ERROR ) {
		WinPrint( "WINS_Listen: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		return -1;
	} //end if
	return 0;
}