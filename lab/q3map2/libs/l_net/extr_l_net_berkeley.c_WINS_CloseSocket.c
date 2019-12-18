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

/* Variables and functions */
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  WINS_ErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  WinPrint (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ closesocket (int) ; 

int WINS_CloseSocket( int socket ){
	/*
	   if (socket == net_broadcastsocket)
	    net_broadcastsocket = 0;
	 */
//	shutdown(socket, SD_SEND);

	if ( closesocket( socket ) == SOCKET_ERROR ) {
		WinPrint( "WINS_CloseSocket: %s\n", WINS_ErrorMessage( WSAGetLastError() ) );
		return SOCKET_ERROR;
	} //end if
	return 0;
}