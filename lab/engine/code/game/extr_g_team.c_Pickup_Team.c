#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int spawnflags; int /*<<< orphan*/  classname; TYPE_4__* client; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_15__ {int sessionTeam; } ;
struct TYPE_14__ {int generic1; } ;
struct TYPE_17__ {TYPE_2__ sess; TYPE_1__ ps; } ;
typedef  TYPE_4__ gclient_t ;
struct TYPE_18__ {scalar_t__ integer; } ;

/* Variables and functions */
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_HARVESTER ; 
 scalar_t__ GT_OBELISK ; 
 int /*<<< orphan*/  G_FreeEntity (TYPE_3__*) ; 
 int /*<<< orphan*/  PrintMsg (TYPE_3__*,char*) ; 
 int TEAM_BLUE ; 
 int TEAM_FREE ; 
 int TEAM_RED ; 
 int Team_TouchEnemyFlag (TYPE_3__*,TYPE_3__*,int) ; 
 int Team_TouchOurFlag (TYPE_3__*,TYPE_3__*,int) ; 
 TYPE_5__ g_gametype ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int Pickup_Team( gentity_t *ent, gentity_t *other ) {
	int team;
	gclient_t *cl = other->client;

#ifdef MISSIONPACK
	if( g_gametype.integer == GT_OBELISK ) {
		// there are no team items that can be picked up in obelisk
		G_FreeEntity( ent );
		return 0;
	}

	if( g_gametype.integer == GT_HARVESTER ) {
		// the only team items that can be picked up in harvester are the cubes
		if( ent->spawnflags != cl->sess.sessionTeam ) {
			cl->ps.generic1 += 1;
		}
		G_FreeEntity( ent );
		return 0;
	}
#endif
	// figure out what team this flag is
	if( strcmp(ent->classname, "team_CTF_redflag") == 0 ) {
		team = TEAM_RED;
	}
	else if( strcmp(ent->classname, "team_CTF_blueflag") == 0 ) {
		team = TEAM_BLUE;
	}
#ifdef MISSIONPACK
	else if( strcmp(ent->classname, "team_CTF_neutralflag") == 0  ) {
		team = TEAM_FREE;
	}
#endif
	else {
		PrintMsg ( other, "Don't know what team the flag is on.\n");
		return 0;
	}
#ifdef MISSIONPACK
	if( g_gametype.integer == GT_1FCTF ) {
		if( team == TEAM_FREE ) {
			return Team_TouchEnemyFlag( ent, other, cl->sess.sessionTeam );
		}
		if( team != cl->sess.sessionTeam) {
			return Team_TouchOurFlag( ent, other, cl->sess.sessionTeam );
		}
		return 0;
	}
#endif
	// GT_CTF
	if( team == cl->sess.sessionTeam) {
		return Team_TouchOurFlag( ent, other, team );
	}
	return Team_TouchEnemyFlag( ent, other, team );
}