#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sessionTeam; scalar_t__ spectatorState; scalar_t__ spectatorClient; scalar_t__ spectatorNum; } ;
struct TYPE_5__ {scalar_t__ connected; } ;
struct TYPE_7__ {TYPE_2__ sess; TYPE_1__ pers; } ;
typedef  TYPE_3__ gclient_t ;
struct TYPE_8__ {int numPlayingClients; int maxclients; int warmupTime; TYPE_3__* clients; scalar_t__ intermissiontime; } ;

/* Variables and functions */
 scalar_t__ CON_CONNECTED ; 
 scalar_t__ SPECTATOR_SCOREBOARD ; 
 int /*<<< orphan*/  SetTeam (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ TEAM_SPECTATOR ; 
 int /*<<< orphan*/ * g_entities ; 
 TYPE_4__ level ; 

void AddTournamentPlayer( void ) {
	int			i;
	gclient_t	*client;
	gclient_t	*nextInLine;

	if ( level.numPlayingClients >= 2 ) {
		return;
	}

	// never change during intermission
	if ( level.intermissiontime ) {
		return;
	}

	nextInLine = NULL;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		client = &level.clients[i];
		if ( client->pers.connected != CON_CONNECTED ) {
			continue;
		}
		if ( client->sess.sessionTeam != TEAM_SPECTATOR ) {
			continue;
		}
		// never select the dedicated follow or scoreboard clients
		if ( client->sess.spectatorState == SPECTATOR_SCOREBOARD || 
			client->sess.spectatorClient < 0  ) {
			continue;
		}

		if(!nextInLine || client->sess.spectatorNum > nextInLine->sess.spectatorNum)
			nextInLine = client;
	}

	if ( !nextInLine ) {
		return;
	}

	level.warmupTime = -1;

	// set them to free-for-all team
	SetTeam( &g_entities[ nextInLine - level.clients ], "f" );
}