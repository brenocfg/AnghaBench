#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int socket; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ socket_t ;
typedef  int /*<<< orphan*/  sockaddr_t ;
struct TYPE_8__ {int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ address_t ;

/* Variables and functions */
 TYPE_1__* Net_AllocSocket () ; 
 int /*<<< orphan*/  Net_FreeSocket (TYPE_1__*) ; 
 int /*<<< orphan*/  WINS_CloseSocket (int) ; 
 int WINS_Connect (int,int /*<<< orphan*/ *) ; 
 int WINS_OpenReliableSocket (int) ; 
 int /*<<< orphan*/  WINS_StringToAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WinPrint (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

socket_t *Net_Connect( address_t *address, int port ){
	int newsock;
	socket_t *sock;
	sockaddr_t sendaddr;

	// see if we can resolve the host name
	WINS_StringToAddr( address->ip, &sendaddr );

	newsock = WINS_OpenReliableSocket( port );
	if ( newsock == -1 ) {
		return NULL;
	}

	sock = Net_AllocSocket();
	if ( sock == NULL ) {
		WINS_CloseSocket( newsock );
		return NULL;
	} //end if
	sock->socket = newsock;

	//connect to the host
	if ( WINS_Connect( newsock, &sendaddr ) == -1 ) {
		Net_FreeSocket( sock );
		WINS_CloseSocket( newsock );
		WinPrint( "Net_Connect: error connecting\n" );
		return NULL;
	} //end if

	memcpy( &sock->addr, &sendaddr, sizeof( sockaddr_t ) );
	//now we can send messages
	//
	return sock;
}