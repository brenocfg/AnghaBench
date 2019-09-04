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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_8__ {int frame; int powerups; int /*<<< orphan*/  eventParm; int /*<<< orphan*/  angles; int /*<<< orphan*/  origin; int /*<<< orphan*/  origin2; int /*<<< orphan*/  clientNum; int /*<<< orphan*/  number; } ;
struct TYPE_7__ {int /*<<< orphan*/  ownerNum; } ;
struct TYPE_9__ {int spawnflags; TYPE_2__ s; int /*<<< orphan*/  target; TYPE_1__ r; } ;
typedef  TYPE_3__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  DirToByte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FreeEntity (TYPE_3__*) ; 
 TYPE_3__* G_PickTarget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_Printf (char*) ; 
 int /*<<< orphan*/  G_SetMovedir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void locateCamera( gentity_t *ent ) {
	vec3_t		dir;
	gentity_t	*target;
	gentity_t	*owner;

	owner = G_PickTarget( ent->target );
	if ( !owner ) {
		G_Printf( "Couldn't find target for misc_partal_surface\n" );
		G_FreeEntity( ent );
		return;
	}
	ent->r.ownerNum = owner->s.number;

	// frame holds the rotate speed
	if ( owner->spawnflags & 1 ) {
		ent->s.frame = 25;
	} else if ( owner->spawnflags & 2 ) {
		ent->s.frame = 75;
	}

	// swing camera ?
	if ( owner->spawnflags & 4 ) {
		// set to 0 for no rotation at all
		ent->s.powerups = 0;
	}
	else {
		ent->s.powerups = 1;
	}

	// clientNum holds the rotate offset
	ent->s.clientNum = owner->s.clientNum;

	VectorCopy( owner->s.origin, ent->s.origin2 );

	// see if the portal_camera has a target
	target = G_PickTarget( owner->target );
	if ( target ) {
		VectorSubtract( target->s.origin, owner->s.origin, dir );
		VectorNormalize( dir );
	} else {
		G_SetMovedir( owner->s.angles, dir );
	}

	ent->s.eventParm = DirToByte( dir );
}