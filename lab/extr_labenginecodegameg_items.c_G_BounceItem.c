#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_12__ {scalar_t__* normal; } ;
struct TYPE_15__ {int fraction; double* endpos; TYPE_1__ plane; int /*<<< orphan*/  entityNum; } ;
typedef  TYPE_4__ trace_t ;
struct TYPE_11__ {int* trDelta; int trTime; int /*<<< orphan*/  trBase; } ;
struct TYPE_14__ {TYPE_10__ pos; int /*<<< orphan*/  groundEntityNum; } ;
struct TYPE_13__ {int /*<<< orphan*/  currentOrigin; } ;
struct TYPE_16__ {TYPE_3__ s; TYPE_2__ r; int /*<<< orphan*/  physicsBounce; } ;
typedef  TYPE_5__ gentity_t ;
struct TYPE_17__ {int previousTime; int time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_EvaluateTrajectoryDelta (TYPE_10__*,int,int /*<<< orphan*/ ) ; 
 float DotProduct (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  G_SetOrigin (TYPE_5__*,double*) ; 
 int /*<<< orphan*/  SnapVector (double*) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,scalar_t__*,int*) ; 
 int /*<<< orphan*/  VectorScale (int*,int /*<<< orphan*/ ,int*) ; 
 TYPE_6__ level ; 

void G_BounceItem( gentity_t *ent, trace_t *trace ) {
	vec3_t	velocity;
	float	dot;
	int		hitTime;

	// reflect the velocity on the trace plane
	hitTime = level.previousTime + ( level.time - level.previousTime ) * trace->fraction;
	BG_EvaluateTrajectoryDelta( &ent->s.pos, hitTime, velocity );
	dot = DotProduct( velocity, trace->plane.normal );
	VectorMA( velocity, -2*dot, trace->plane.normal, ent->s.pos.trDelta );

	// cut the velocity to keep from bouncing forever
	VectorScale( ent->s.pos.trDelta, ent->physicsBounce, ent->s.pos.trDelta );

	// check for stop
	if ( trace->plane.normal[2] > 0 && ent->s.pos.trDelta[2] < 40 ) {
		trace->endpos[2] += 1.0;	// make sure it is off ground
		SnapVector( trace->endpos );
		G_SetOrigin( ent, trace->endpos );
		ent->s.groundEntityNum = trace->entityNum;
		return;
	}

	VectorAdd( ent->r.currentOrigin, trace->plane.normal, ent->r.currentOrigin);
	VectorCopy( ent->r.currentOrigin, ent->s.pos.trBase );
	ent->s.pos.trTime = level.time;
}