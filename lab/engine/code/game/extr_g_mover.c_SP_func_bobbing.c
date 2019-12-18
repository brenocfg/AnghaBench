#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int trDuration; float trTime; float* trDelta; int /*<<< orphan*/  trType; int /*<<< orphan*/  trBase; } ;
struct TYPE_10__ {TYPE_2__ pos; int /*<<< orphan*/  origin; } ;
struct TYPE_8__ {int /*<<< orphan*/  currentOrigin; } ;
struct TYPE_11__ {float speed; int spawnflags; TYPE_3__ s; TYPE_1__ r; int /*<<< orphan*/  model; int /*<<< orphan*/  damage; } ;
typedef  TYPE_4__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_SpawnFloat (char*,char*,float*) ; 
 int /*<<< orphan*/  G_SpawnInt (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitMover (TYPE_4__*) ; 
 int /*<<< orphan*/  TR_SINE ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_SetBrushModel (TYPE_4__*,int /*<<< orphan*/ ) ; 

void SP_func_bobbing (gentity_t *ent) {
	float		height;
	float		phase;

	G_SpawnFloat( "speed", "4", &ent->speed );
	G_SpawnFloat( "height", "32", &height );
	G_SpawnInt( "dmg", "2", &ent->damage );
	G_SpawnFloat( "phase", "0", &phase );

	trap_SetBrushModel( ent, ent->model );
	InitMover( ent );

	VectorCopy( ent->s.origin, ent->s.pos.trBase );
	VectorCopy( ent->s.origin, ent->r.currentOrigin );

	ent->s.pos.trDuration = ent->speed * 1000;
	ent->s.pos.trTime = ent->s.pos.trDuration * phase;
	ent->s.pos.trType = TR_SINE;

	// set the axis of bobbing
	if ( ent->spawnflags & 1 ) {
		ent->s.pos.trDelta[0] = height;
	} else if ( ent->spawnflags & 2 ) {
		ent->s.pos.trDelta[1] = height;
	} else {
		ent->s.pos.trDelta[2] = height;
	}
}