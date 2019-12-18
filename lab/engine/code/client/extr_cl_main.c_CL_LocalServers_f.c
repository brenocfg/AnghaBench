#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  to ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {int /*<<< orphan*/  type; int /*<<< orphan*/  port; int /*<<< orphan*/  visible; } ;
typedef  TYPE_1__ netadr_t ;
struct TYPE_6__ {TYPE_1__* localServers; int /*<<< orphan*/  pingUpdateSource; scalar_t__ numlocalservers; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_LOCAL ; 
 int /*<<< orphan*/  BigShort (short) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int MAX_OTHER_SERVERS ; 
 int /*<<< orphan*/  NA_BROADCAST ; 
 int /*<<< orphan*/  NA_MULTICAST6 ; 
 int /*<<< orphan*/  NET_SendPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__) ; 
 int /*<<< orphan*/  NS_CLIENT ; 
 int NUM_SERVER_PORTS ; 
 scalar_t__ PORT_SERVER ; 
 TYPE_2__ cls ; 
 int /*<<< orphan*/  strlen (char*) ; 

void CL_LocalServers_f( void ) {
	char		*message;
	int			i, j;
	netadr_t	to;

	Com_Printf( "Scanning for servers on the local network...\n");

	// reset the list, waiting for response
	cls.numlocalservers = 0;
	cls.pingUpdateSource = AS_LOCAL;

	for (i = 0; i < MAX_OTHER_SERVERS; i++) {
		qboolean b = cls.localServers[i].visible;
		Com_Memset(&cls.localServers[i], 0, sizeof(cls.localServers[i]));
		cls.localServers[i].visible = b;
	}
	Com_Memset( &to, 0, sizeof( to ) );

	// The 'xxx' in the message is a challenge that will be echoed back
	// by the server.  We don't care about that here, but master servers
	// can use that to prevent spoofed server responses from invalid ip
	message = "\377\377\377\377getinfo xxx";

	// send each message twice in case one is dropped
	for ( i = 0 ; i < 2 ; i++ ) {
		// send a broadcast packet on each server port
		// we support multiple server ports so a single machine
		// can nicely run multiple servers
		for ( j = 0 ; j < NUM_SERVER_PORTS ; j++ ) {
			to.port = BigShort( (short)(PORT_SERVER + j) );

			to.type = NA_BROADCAST;
			NET_SendPacket( NS_CLIENT, strlen( message ), message, to );
			to.type = NA_MULTICAST6;
			NET_SendPacket( NS_CLIENT, strlen( message ), message, to );
		}
	}
}