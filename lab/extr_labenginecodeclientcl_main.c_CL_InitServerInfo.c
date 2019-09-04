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
struct TYPE_3__ {char* hostName; char* mapName; int ping; char* game; scalar_t__ g_needpass; scalar_t__ g_humanplayers; scalar_t__ punkbuster; scalar_t__ netType; scalar_t__ gameType; scalar_t__ minPing; scalar_t__ maxPing; scalar_t__ maxClients; scalar_t__ clients; int /*<<< orphan*/  adr; } ;
typedef  TYPE_1__ serverInfo_t ;
typedef  int /*<<< orphan*/  netadr_t ;

/* Variables and functions */

void CL_InitServerInfo( serverInfo_t *server, netadr_t *address ) {
	server->adr = *address;
	server->clients = 0;
	server->hostName[0] = '\0';
	server->mapName[0] = '\0';
	server->maxClients = 0;
	server->maxPing = 0;
	server->minPing = 0;
	server->ping = -1;
	server->game[0] = '\0';
	server->gameType = 0;
	server->netType = 0;
	server->punkbuster = 0;
	server->g_humanplayers = 0;
	server->g_needpass = 0;
}