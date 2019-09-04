#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ inuse; TYPE_4__* client; scalar_t__ health; } ;
typedef  TYPE_5__ gentity_t ;
struct TYPE_18__ {int integer; } ;
struct TYPE_17__ {scalar_t__ time; scalar_t__ lastTeamLocationTime; } ;
struct TYPE_13__ {scalar_t__ location; } ;
struct TYPE_14__ {scalar_t__ connected; TYPE_2__ teamState; } ;
struct TYPE_12__ {scalar_t__ sessionTeam; } ;
struct TYPE_15__ {TYPE_3__ pers; TYPE_1__ sess; } ;

/* Variables and functions */
 scalar_t__ CON_CONNECTED ; 
 scalar_t__ TEAM_BLUE ; 
 scalar_t__ TEAM_LOCATION_UPDATE_TIME ; 
 scalar_t__ TEAM_RED ; 
 TYPE_5__* Team_GetLocation (TYPE_5__*) ; 
 int /*<<< orphan*/  TeamplayInfoMessage (TYPE_5__*) ; 
 TYPE_5__* g_entities ; 
 TYPE_7__ g_maxclients ; 
 TYPE_6__ level ; 

void CheckTeamStatus(void) {
	int i;
	gentity_t *loc, *ent;

	if (level.time - level.lastTeamLocationTime > TEAM_LOCATION_UPDATE_TIME) {

		level.lastTeamLocationTime = level.time;

		for (i = 0; i < g_maxclients.integer; i++) {
			ent = g_entities + i;

			if ( ent->client->pers.connected != CON_CONNECTED ) {
				continue;
			}

			if (ent->inuse && (ent->client->sess.sessionTeam == TEAM_RED ||	ent->client->sess.sessionTeam == TEAM_BLUE)) {
				loc = Team_GetLocation( ent );
				if (loc)
					ent->client->pers.teamState.location = loc->health;
				else
					ent->client->pers.teamState.location = 0;
			}
		}

		for (i = 0; i < g_maxclients.integer; i++) {
			ent = g_entities + i;

			if ( ent->client->pers.connected != CON_CONNECTED ) {
				continue;
			}

			if (ent->inuse) {
				TeamplayInfoMessage( ent );
			}
		}
	}
}