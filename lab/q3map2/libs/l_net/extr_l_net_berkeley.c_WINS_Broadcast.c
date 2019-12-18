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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int WINS_MakeSocketBroadcastCapable (int) ; 
 int WINS_Write (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WinError (char*) ; 
 int /*<<< orphan*/  WinPrint (char*) ; 
 int /*<<< orphan*/  broadcastaddr ; 
 int net_broadcastsocket ; 

int WINS_Broadcast( int socket, byte *buf, int len ){
	int ret;

	if ( socket != net_broadcastsocket ) {
		if ( net_broadcastsocket != 0 ) {
			WinError( "Attempted to use multiple broadcasts sockets\n" );
		}
		ret = WINS_MakeSocketBroadcastCapable( socket );
		if ( ret == -1 ) {
			WinPrint( "Unable to make socket broadcast capable\n" );
			return ret;
		}
	}

	return WINS_Write( socket, buf, len, &broadcastaddr );
}