#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_9__ {int /*<<< orphan*/ * origin; int /*<<< orphan*/  angles; } ;
struct TYPE_8__ {int /*<<< orphan*/  mins; int /*<<< orphan*/  maxs; } ;
struct TYPE_10__ {int speed; int wait; int damage; int spawnflags; int flags; int /*<<< orphan*/  think; scalar_t__ targetname; int /*<<< orphan*/  takedamage; scalar_t__ nextthink; int /*<<< orphan*/ * pos1; int /*<<< orphan*/ * pos2; TYPE_2__ s; int /*<<< orphan*/ * movedir; TYPE_1__ r; int /*<<< orphan*/  model; int /*<<< orphan*/  blocked; void* soundPos2; void* soundPos1; void* sound2to1; void* sound1to2; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_11__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  Blocked_Door ; 
 float DotProduct (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FL_TEAMSLAVE ; 
 scalar_t__ FRAMETIME ; 
 int /*<<< orphan*/  G_SetMovedir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* G_SoundIndex (char*) ; 
 int /*<<< orphan*/  G_SpawnFloat (char*,char*,float*) ; 
 int /*<<< orphan*/  G_SpawnInt (char*,char*,int*) ; 
 int /*<<< orphan*/  InitMover (TYPE_3__*) ; 
 int /*<<< orphan*/  Think_MatchTeam ; 
 int /*<<< orphan*/  Think_SpawnNewDoorTrigger ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ *,float,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fabs (int /*<<< orphan*/ ) ; 
 TYPE_5__ level ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_SetBrushModel (TYPE_3__*,int /*<<< orphan*/ ) ; 

void SP_func_door (gentity_t *ent) {
	vec3_t	abs_movedir;
	float	distance;
	vec3_t	size;
	float	lip;

	ent->sound1to2 = ent->sound2to1 = G_SoundIndex("sound/movers/doors/dr1_strt.wav");
	ent->soundPos1 = ent->soundPos2 = G_SoundIndex("sound/movers/doors/dr1_end.wav");

	ent->blocked = Blocked_Door;

	// default speed of 400
	if (!ent->speed)
		ent->speed = 400;

	// default wait of 2 seconds
	if (!ent->wait)
		ent->wait = 2;
	ent->wait *= 1000;

	// default lip of 8 units
	G_SpawnFloat( "lip", "8", &lip );

	// default damage of 2 points
	G_SpawnInt( "dmg", "2", &ent->damage );

	// first position at start
	VectorCopy( ent->s.origin, ent->pos1 );

	// calculate second position
	trap_SetBrushModel( ent, ent->model );
	G_SetMovedir (ent->s.angles, ent->movedir);
	abs_movedir[0] = fabs(ent->movedir[0]);
	abs_movedir[1] = fabs(ent->movedir[1]);
	abs_movedir[2] = fabs(ent->movedir[2]);
	VectorSubtract( ent->r.maxs, ent->r.mins, size );
	distance = DotProduct( abs_movedir, size ) - lip;
	VectorMA( ent->pos1, distance, ent->movedir, ent->pos2 );

	// if "start_open", reverse position 1 and 2
	if ( ent->spawnflags & 1 ) {
		vec3_t	temp;

		VectorCopy( ent->pos2, temp );
		VectorCopy( ent->s.origin, ent->pos2 );
		VectorCopy( temp, ent->pos1 );
	}

	InitMover( ent );

	ent->nextthink = level.time + FRAMETIME;

	if ( ! (ent->flags & FL_TEAMSLAVE ) ) {
		int health;

		G_SpawnInt( "health", "0", &health );
		if ( health ) {
			ent->takedamage = qtrue;
		}
		if ( ent->targetname || health ) {
			// non touch/shoot doors
			ent->think = Think_MatchTeam;
		} else {
			ent->think = Think_SpawnNewDoorTrigger;
		}
	}


}