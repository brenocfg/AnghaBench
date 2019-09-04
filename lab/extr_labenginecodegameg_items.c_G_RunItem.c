#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_20__ {int fraction; scalar_t__ startsolid; int /*<<< orphan*/  endpos; } ;
typedef  TYPE_4__ trace_t ;
struct TYPE_18__ {int /*<<< orphan*/  currentOrigin; int /*<<< orphan*/  ownerNum; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
struct TYPE_16__ {scalar_t__ trType; int /*<<< orphan*/  trTime; } ;
struct TYPE_17__ {scalar_t__ groundEntityNum; TYPE_15__ pos; } ;
struct TYPE_21__ {int clipmask; TYPE_3__* item; TYPE_2__ r; TYPE_1__ s; } ;
typedef  TYPE_5__ gentity_t ;
struct TYPE_22__ {int /*<<< orphan*/  time; } ;
struct TYPE_19__ {scalar_t__ giType; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_EvaluateTrajectory (TYPE_15__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CONTENTS_BODY ; 
 int CONTENTS_NODROP ; 
 scalar_t__ ENTITYNUM_NONE ; 
 int /*<<< orphan*/  G_BounceItem (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  G_FreeEntity (TYPE_5__*) ; 
 int /*<<< orphan*/  G_RunThink (TYPE_5__*) ; 
 scalar_t__ IT_TEAM ; 
 int MASK_PLAYERSOLID ; 
 scalar_t__ TR_GRAVITY ; 
 scalar_t__ TR_STATIONARY ; 
 int /*<<< orphan*/  Team_FreeEntity (TYPE_5__*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__ level ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_5__*) ; 
 int trap_PointContents (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_Trace (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void G_RunItem( gentity_t *ent ) {
	vec3_t		origin;
	trace_t		tr;
	int			contents;
	int			mask;

	// if its groundentity has been set to none, it may have been pushed off an edge
	if ( ent->s.groundEntityNum == ENTITYNUM_NONE ) {
		if ( ent->s.pos.trType != TR_GRAVITY ) {
			ent->s.pos.trType = TR_GRAVITY;
			ent->s.pos.trTime = level.time;
		}
	}

	if ( ent->s.pos.trType == TR_STATIONARY ) {
		// check think function
		G_RunThink( ent );
		return;
	}

	// get current position
	BG_EvaluateTrajectory( &ent->s.pos, level.time, origin );

	// trace a line from the previous position to the current position
	if ( ent->clipmask ) {
		mask = ent->clipmask;
	} else {
		mask = MASK_PLAYERSOLID & ~CONTENTS_BODY;//MASK_SOLID;
	}
	trap_Trace( &tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, origin, 
		ent->r.ownerNum, mask );

	VectorCopy( tr.endpos, ent->r.currentOrigin );

	if ( tr.startsolid ) {
		tr.fraction = 0;
	}

	trap_LinkEntity( ent );	// FIXME: avoid this for stationary?

	// check think function
	G_RunThink( ent );

	if ( tr.fraction == 1 ) {
		return;
	}

	// if it is in a nodrop volume, remove it
	contents = trap_PointContents( ent->r.currentOrigin, -1 );
	if ( contents & CONTENTS_NODROP ) {
		if (ent->item && ent->item->giType == IT_TEAM) {
			Team_FreeEntity(ent);
		} else {
			G_FreeEntity( ent );
		}
		return;
	}

	G_BounceItem( ent, &tr );
}