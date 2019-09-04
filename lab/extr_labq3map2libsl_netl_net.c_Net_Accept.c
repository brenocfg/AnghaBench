#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int socket; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ socket_t ;
typedef  int /*<<< orphan*/  sockaddr_t ;

/* Variables and functions */
 TYPE_1__* Net_AllocSocket () ; 
 int WINS_Accept (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WINS_CloseSocket (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

socket_t *Net_Accept( socket_t *sock ){
	int newsocket;
	sockaddr_t sendaddr;
	socket_t *newsock;

	newsocket = WINS_Accept( sock->socket, &sendaddr );
	if ( newsocket == -1 ) {
		return NULL;
	}

	newsock = Net_AllocSocket();
	if ( newsock == NULL ) {
		WINS_CloseSocket( newsocket );
		return NULL;
	} //end if
	newsock->socket = newsocket;
	memcpy( &newsock->addr, &sendaddr, sizeof( sockaddr_t ) );
	//
	return newsock;
}