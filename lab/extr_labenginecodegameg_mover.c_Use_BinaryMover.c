#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int trDuration; int trTime; } ;
struct TYPE_12__ {TYPE_1__ pos; int /*<<< orphan*/  loopSound; } ;
struct TYPE_13__ {int flags; scalar_t__ moverState; int nextthink; int wait; scalar_t__ sound2to1; TYPE_2__ s; scalar_t__ sound1to2; struct TYPE_13__* teammaster; int /*<<< orphan*/  soundLoop; struct TYPE_13__* activator; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_14__ {int time; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_GENERAL_SOUND ; 
 int FL_TEAMSLAVE ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MOVER_1TO2 ; 
 scalar_t__ MOVER_2TO1 ; 
 scalar_t__ MOVER_POS1 ; 
 scalar_t__ MOVER_POS2 ; 
 int /*<<< orphan*/  MatchTeam (TYPE_3__*,scalar_t__,int) ; 
 TYPE_5__ level ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_AdjustAreaPortalState (TYPE_3__*,int /*<<< orphan*/ ) ; 

void Use_BinaryMover( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	int		total;
	int		partial;

	// only the master should be used
	if ( ent->flags & FL_TEAMSLAVE ) {
		Use_BinaryMover( ent->teammaster, other, activator );
		return;
	}

	ent->activator = activator;

	if ( ent->moverState == MOVER_POS1 ) {
		// start moving 50 msec later, becase if this was player
		// triggered, level.time hasn't been advanced yet
		MatchTeam( ent, MOVER_1TO2, level.time + 50 );

		// starting sound
		if ( ent->sound1to2 ) {
			G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound1to2 );
		}

		// looping sound
		ent->s.loopSound = ent->soundLoop;

		// open areaportal
		if ( ent->teammaster == ent || !ent->teammaster ) {
			trap_AdjustAreaPortalState( ent, qtrue );
		}
		return;
	}

	// if all the way up, just delay before coming down
	if ( ent->moverState == MOVER_POS2 ) {
		ent->nextthink = level.time + ent->wait;
		return;
	}

	// only partway down before reversing
	if ( ent->moverState == MOVER_2TO1 ) {
		total = ent->s.pos.trDuration;
		partial = level.time - ent->s.pos.trTime;
		if ( partial > total ) {
			partial = total;
		}

		MatchTeam( ent, MOVER_1TO2, level.time - ( total - partial ) );

		if ( ent->sound1to2 ) {
			G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound1to2 );
		}
		return;
	}

	// only partway up before reversing
	if ( ent->moverState == MOVER_1TO2 ) {
		total = ent->s.pos.trDuration;
		partial = level.time - ent->s.pos.trTime;
		if ( partial > total ) {
			partial = total;
		}

		MatchTeam( ent, MOVER_2TO1, level.time - ( total - partial ) );

		if ( ent->sound2to1 ) {
			G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound2to1 );
		}
		return;
	}
}