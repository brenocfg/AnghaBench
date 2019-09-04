#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_12__ {size_t clientNum; int eFlags; } ;
struct TYPE_16__ {int numEntities; int snapFlags; TYPE_11__ ps; TYPE_5__* entities; } ;
typedef  TYPE_4__ snapshot_t ;
struct TYPE_17__ {size_t number; int eFlags; } ;
typedef  TYPE_5__ entityState_t ;
struct TYPE_13__ {int eFlags; } ;
struct TYPE_18__ {void* interpolate; TYPE_1__ currentState; int /*<<< orphan*/  currentValid; int /*<<< orphan*/  nextState; } ;
typedef  TYPE_6__ centity_t ;
struct TYPE_19__ {void* nextFrameTeleport; TYPE_3__* snap; TYPE_4__* nextSnap; } ;
struct TYPE_14__ {size_t clientNum; int eFlags; } ;
struct TYPE_15__ {int snapFlags; TYPE_2__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_PlayerStateToEntityState (TYPE_11__*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  CG_BuildSolidList () ; 
 int EF_TELEPORT_BIT ; 
 int SNAPFLAG_SERVERCOUNT ; 
 TYPE_9__ cg ; 
 TYPE_6__* cg_entities ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 void* qfalse ; 
 void* qtrue ; 

__attribute__((used)) static void CG_SetNextSnap( snapshot_t *snap ) {
	int					num;
	entityState_t		*es;
	centity_t			*cent;

	cg.nextSnap = snap;

	BG_PlayerStateToEntityState( &snap->ps, &cg_entities[ snap->ps.clientNum ].nextState, qfalse );
	cg_entities[ cg.snap->ps.clientNum ].interpolate = qtrue;

	// check for extrapolation errors
	for ( num = 0 ; num < snap->numEntities ; num++ ) {
		es = &snap->entities[num];
		cent = &cg_entities[ es->number ];

		memcpy(&cent->nextState, es, sizeof(entityState_t));
		//cent->nextState = *es;

		// if this frame is a teleport, or the entity wasn't in the
		// previous frame, don't interpolate
		if ( !cent->currentValid || ( ( cent->currentState.eFlags ^ es->eFlags ) & EF_TELEPORT_BIT )  ) {
			cent->interpolate = qfalse;
		} else {
			cent->interpolate = qtrue;
		}
	}

	// if the next frame is a teleport for the playerstate, we
	// can't interpolate during demos
	if ( cg.snap && ( ( snap->ps.eFlags ^ cg.snap->ps.eFlags ) & EF_TELEPORT_BIT ) ) {
		cg.nextFrameTeleport = qtrue;
	} else {
		cg.nextFrameTeleport = qfalse;
	}

	// if changing follow mode, don't interpolate
	if ( cg.nextSnap->ps.clientNum != cg.snap->ps.clientNum ) {
		cg.nextFrameTeleport = qtrue;
	}

	// if changing server restarts, don't interpolate
	if ( ( cg.nextSnap->snapFlags ^ cg.snap->snapFlags ) & SNAPFLAG_SERVERCOUNT ) {
		cg.nextFrameTeleport = qtrue;
	}

	// sort out solid entities
	CG_BuildSolidList();
}