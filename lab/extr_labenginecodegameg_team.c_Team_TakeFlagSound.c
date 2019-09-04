#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  svFlags; } ;
struct TYPE_9__ {int /*<<< orphan*/  trBase; } ;
struct TYPE_10__ {int /*<<< orphan*/  eventParm; TYPE_1__ pos; } ;
struct TYPE_12__ {TYPE_3__ r; TYPE_2__ s; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_14__ {int /*<<< orphan*/  time; } ;
struct TYPE_13__ {int /*<<< orphan*/  redTakenTime; int /*<<< orphan*/  redStatus; int /*<<< orphan*/  blueTakenTime; int /*<<< orphan*/  blueStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_GLOBAL_TEAM_SOUND ; 
 int /*<<< orphan*/  FLAG_ATBASE ; 
 int /*<<< orphan*/  GTS_BLUE_TAKEN ; 
 int /*<<< orphan*/  GTS_RED_TAKEN ; 
 int /*<<< orphan*/  G_Printf (char*) ; 
 TYPE_4__* G_TempEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVF_BROADCAST ; 
#define  TEAM_BLUE 129 
#define  TEAM_RED 128 
 TYPE_6__ level ; 
 TYPE_5__ teamgame ; 

void Team_TakeFlagSound( gentity_t *ent, int team ) {
	gentity_t	*te;

	if (ent == NULL) {
		G_Printf ("Warning:  NULL passed to Team_TakeFlagSound\n");
		return;
	}

	// only play sound when the flag was at the base
	// or not picked up the last 10 seconds
	switch(team) {
		case TEAM_RED:
			if( teamgame.blueStatus != FLAG_ATBASE ) {
				if (teamgame.blueTakenTime > level.time - 10000)
					return;
			}
			teamgame.blueTakenTime = level.time;
			break;

		case TEAM_BLUE:	// CTF
			if( teamgame.redStatus != FLAG_ATBASE ) {
				if (teamgame.redTakenTime > level.time - 10000)
					return;
			}
			teamgame.redTakenTime = level.time;
			break;
	}

	te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_TEAM_SOUND );
	if( team == TEAM_BLUE ) {
		te->s.eventParm = GTS_RED_TAKEN;
	}
	else {
		te->s.eventParm = GTS_BLUE_TAKEN;
	}
	te->r.svFlags |= SVF_BROADCAST;
}