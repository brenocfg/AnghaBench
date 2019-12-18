#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int clients; int maxClients; int /*<<< orphan*/  ping; int /*<<< orphan*/  gameType; int /*<<< orphan*/  mapName; int /*<<< orphan*/  hostName; } ;
typedef  TYPE_1__ serverInfo_t ;

/* Variables and functions */
 TYPE_1__* LAN_GetServerPtr (int,int) ; 
 int Q_stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SORT_CLIENTS 132 
#define  SORT_GAME 131 
#define  SORT_HOST 130 
#define  SORT_MAP 129 
#define  SORT_PING 128 

__attribute__((used)) static int LAN_CompareServers( int source, int sortKey, int sortDir, int s1, int s2 ) {
	int res;
	serverInfo_t *server1, *server2;
	int clients1, clients2;

	server1 = LAN_GetServerPtr(source, s1);
	server2 = LAN_GetServerPtr(source, s2);
	if (!server1 || !server2) {
		return 0;
	}

	res = 0;
	switch( sortKey ) {
		case SORT_HOST:
			res = Q_stricmp( server1->hostName, server2->hostName );
			break;

		case SORT_MAP:
			res = Q_stricmp( server1->mapName, server2->mapName );
			break;
		case SORT_CLIENTS:
			// sub sort by max clients
			if ( server1->clients == server2->clients ) {
				clients1 = server1->maxClients;
				clients2 = server2->maxClients;
			} else {
				clients1 = server1->clients;
				clients2 = server2->clients;
			}

			if (clients1 < clients2) {
				res = -1;
			}
			else if (clients1 > clients2) {
				res = 1;
			}
			else {
				res = 0;
			}
			break;
		case SORT_GAME:
			if (server1->gameType < server2->gameType) {
				res = -1;
			}
			else if (server1->gameType > server2->gameType) {
				res = 1;
			}
			else {
				res = 0;
			}
			break;
		case SORT_PING:
			if (server1->ping < server2->ping) {
				res = -1;
			}
			else if (server1->ping > server2->ping) {
				res = 1;
			}
			else {
				res = 0;
			}
			break;
	}

	if (sortDir) {
		if (res < 0)
			return 1;
		if (res > 0)
			return -1;
		return 0;
	}
	return res;
}