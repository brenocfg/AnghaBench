#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  loopSound; } ;
struct TYPE_8__ {scalar_t__ sound2to1; int /*<<< orphan*/  soundLoop; TYPE_1__ s; } ;
typedef  TYPE_2__ gentity_t ;
struct TYPE_9__ {int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_GENERAL_SOUND ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MOVER_2TO1 ; 
 int /*<<< orphan*/  MatchTeam (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ level ; 

void ReturnToPos1( gentity_t *ent ) {
	MatchTeam( ent, MOVER_2TO1, level.time );

	// looping sound
	ent->s.loopSound = ent->soundLoop;

	// starting sound
	if ( ent->sound2to1 ) {
		G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound2to1 );
	}
}