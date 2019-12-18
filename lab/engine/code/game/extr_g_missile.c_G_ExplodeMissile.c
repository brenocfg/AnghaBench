#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_14__ {size_t ownerNum; int /*<<< orphan*/  currentOrigin; } ;
struct TYPE_12__ {int /*<<< orphan*/  eType; int /*<<< orphan*/  pos; } ;
struct TYPE_15__ {TYPE_3__ r; int /*<<< orphan*/  splashMethodOfDeath; int /*<<< orphan*/  splashRadius; scalar_t__ splashDamage; int /*<<< orphan*/  parent; int /*<<< orphan*/  freeAfterEvent; TYPE_1__ s; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_17__ {TYPE_2__* client; } ;
struct TYPE_16__ {int /*<<< orphan*/  time; } ;
struct TYPE_13__ {int /*<<< orphan*/  accuracy_hits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_EvaluateTrajectory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  DirToByte (int*) ; 
 int /*<<< orphan*/  ET_GENERAL ; 
 int /*<<< orphan*/  EV_MISSILE_MISS ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ G_RadiusDamage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_SetOrigin (TYPE_4__*,int*) ; 
 int /*<<< orphan*/  SnapVector (int*) ; 
 TYPE_7__* g_entities ; 
 TYPE_6__ level ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_4__*) ; 

void G_ExplodeMissile( gentity_t *ent ) {
	vec3_t		dir;
	vec3_t		origin;

	BG_EvaluateTrajectory( &ent->s.pos, level.time, origin );
	SnapVector( origin );
	G_SetOrigin( ent, origin );

	// we don't have a valid direction, so just point straight up
	dir[0] = dir[1] = 0;
	dir[2] = 1;

	ent->s.eType = ET_GENERAL;
	G_AddEvent( ent, EV_MISSILE_MISS, DirToByte( dir ) );

	ent->freeAfterEvent = qtrue;

	// splash damage
	if ( ent->splashDamage ) {
		if( G_RadiusDamage( ent->r.currentOrigin, ent->parent, ent->splashDamage, ent->splashRadius, ent
			, ent->splashMethodOfDeath ) ) {
			g_entities[ent->r.ownerNum].client->accuracy_hits++;
		}
	}

	trap_LinkEntity( ent );
}