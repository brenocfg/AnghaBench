#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int socket; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ socket_t ;

/* Variables and functions */
 TYPE_1__* Net_AllocSocket () ; 
 int /*<<< orphan*/  WINS_AddrToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WINS_CloseSocket (int) ; 
 int /*<<< orphan*/  WINS_GetSocketAddr (int,int /*<<< orphan*/ *) ; 
 int WINS_Listen (int) ; 
 int WINS_OpenReliableSocket (int) ; 
 int /*<<< orphan*/  WinPrint (char*,int /*<<< orphan*/ ) ; 

socket_t *Net_ListenSocket( int port ){
	int newsock;
	socket_t *sock;

	newsock = WINS_OpenReliableSocket( port );
	if ( newsock == -1 ) {
		return NULL;
	}

	if ( WINS_Listen( newsock ) == -1 ) {
		WINS_CloseSocket( newsock );
		return NULL;
	} //end if
	sock = Net_AllocSocket();
	if ( sock == NULL ) {
		WINS_CloseSocket( newsock );
		return NULL;
	} //end if
	sock->socket = newsock;
	WINS_GetSocketAddr( newsock, &sock->addr );
	WinPrint( "listen socket opened at %s\n", WINS_AddrToString( &sock->addr ) );
	//
	return sock;
}