#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_10__ {float trDuration; int /*<<< orphan*/  trType; } ;
struct TYPE_11__ {TYPE_2__ pos; int /*<<< orphan*/  loopSound; int /*<<< orphan*/  origin; } ;
struct TYPE_9__ {int /*<<< orphan*/  svFlags; } ;
struct TYPE_12__ {float speed; int wait; TYPE_3__ s; int /*<<< orphan*/  think; scalar_t__ nextthink; int /*<<< orphan*/  soundLoop; TYPE_1__ r; int /*<<< orphan*/  pos1; int /*<<< orphan*/  pos2; struct TYPE_12__* nextTrain; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_13__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_UseTargets (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MOVER_1TO2 ; 
 int /*<<< orphan*/  SVF_NOCLIENT ; 
 int /*<<< orphan*/  SetMoverState (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TR_STATIONARY ; 
 int /*<<< orphan*/  Think_BeginMoving ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ level ; 

void Reached_Train( gentity_t *ent ) {
	gentity_t		*next;
	float			speed;
	vec3_t			move;
	float			length;

	// copy the appropriate values
	next = ent->nextTrain;
	if ( !next || !next->nextTrain ) {
		return;		// just stop
	}

	// fire all other targets
	G_UseTargets( next, NULL );

	// set the new trajectory
	ent->nextTrain = next->nextTrain;
	VectorCopy( next->s.origin, ent->pos1 );
	VectorCopy( next->nextTrain->s.origin, ent->pos2 );

	// if the path_corner has a speed, use that
	if ( next->speed ) {
		speed = next->speed;
	} else {
		// otherwise use the train's speed
		speed = ent->speed;
	}
	if ( speed < 1 ) {
		speed = 1;
	}

	// calculate duration
	VectorSubtract( ent->pos2, ent->pos1, move );
	length = VectorLength( move );

	ent->s.pos.trDuration = length * 1000 / speed;

	// Tequila comment: Be sure to send to clients after any fast move case
	ent->r.svFlags &= ~SVF_NOCLIENT;

	// Tequila comment: Fast move case
	if(ent->s.pos.trDuration<1) {
		// Tequila comment: As trDuration is used later in a division, we need to avoid that case now
		// With null trDuration,
		// the calculated rocks bounding box becomes infinite and the engine think for a short time
		// any entity is riding that mover but not the world entity... In rare case, I found it
		// can also stuck every map entities after func_door are used.
		// The desired effect with very very big speed is to have instant move, so any not null duration
		// lower than a frame duration should be sufficient.
		// Afaik, the negative case don't have to be supported.
		ent->s.pos.trDuration=1;

		// Tequila comment: Don't send entity to clients so it becomes really invisible 
		ent->r.svFlags |= SVF_NOCLIENT;
	}

	// looping sound
	ent->s.loopSound = next->soundLoop;

	// start it going
	SetMoverState( ent, MOVER_1TO2, level.time );

	// if there is a "wait" value on the target, don't start moving yet
	if ( next->wait ) {
		ent->nextthink = level.time + next->wait * 1000;
		ent->think = Think_BeginMoving;
		ent->s.pos.trType = TR_STATIONARY;
	}
}