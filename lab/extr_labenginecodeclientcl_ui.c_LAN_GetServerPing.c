#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ping; } ;
typedef  TYPE_1__ serverInfo_t ;
struct TYPE_4__ {TYPE_1__* favoriteServers; TYPE_1__* globalServers; TYPE_1__* localServers; } ;

/* Variables and functions */
#define  AS_FAVORITES 131 
#define  AS_GLOBAL 130 
#define  AS_LOCAL 129 
#define  AS_MPLAYER 128 
 int MAX_GLOBAL_SERVERS ; 
 int MAX_OTHER_SERVERS ; 
 TYPE_2__ cls ; 

__attribute__((used)) static int LAN_GetServerPing( int source, int n ) {
	serverInfo_t *server = NULL;
	switch (source) {
		case AS_LOCAL :
			if (n >= 0 && n < MAX_OTHER_SERVERS) {
				server = &cls.localServers[n];
			}
			break;
		case AS_MPLAYER:
		case AS_GLOBAL :
			if (n >= 0 && n < MAX_GLOBAL_SERVERS) {
				server = &cls.globalServers[n];
			}
			break;
		case AS_FAVORITES :
			if (n >= 0 && n < MAX_OTHER_SERVERS) {
				server = &cls.favoriteServers[n];
			}
			break;
	}
	if (server) {
		return server->ping;
	}
	return -1;
}