#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {size_t clientNum; int eFlags; int pm_flags; } ;
struct TYPE_14__ {int numEntities; TYPE_3__ ps; int /*<<< orphan*/  serverTime; TYPE_1__* entities; int /*<<< orphan*/  serverCommandSequence; } ;
typedef  TYPE_2__ snapshot_t ;
typedef  TYPE_3__ playerState_t ;
struct TYPE_16__ {int /*<<< orphan*/  snapShotTime; void* interpolate; int /*<<< orphan*/  currentState; void* currentValid; } ;
typedef  TYPE_4__ centity_t ;
struct TYPE_19__ {TYPE_2__* snap; scalar_t__ demoPlayback; int /*<<< orphan*/  thisFrameTeleport; TYPE_2__* nextSnap; scalar_t__ mapRestart; } ;
struct TYPE_18__ {scalar_t__ integer; } ;
struct TYPE_17__ {scalar_t__ integer; } ;
struct TYPE_13__ {size_t number; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_PlayerStateToEntityState (TYPE_3__*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  CG_Error (char*) ; 
 int /*<<< orphan*/  CG_ExecuteNewServerCommands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_TransitionEntity (TYPE_4__*) ; 
 int /*<<< orphan*/  CG_TransitionPlayerState (TYPE_3__*,TYPE_3__*) ; 
 int EF_TELEPORT_BIT ; 
 int PMF_FOLLOW ; 
 TYPE_8__ cg ; 
 TYPE_4__* cg_entities ; 
 TYPE_6__ cg_nopredict ; 
 TYPE_5__ cg_synchronousClients ; 
 void* qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static void CG_TransitionSnapshot( void ) {
	centity_t			*cent;
	snapshot_t			*oldFrame;
	int					i;

	if ( !cg.snap ) {
		CG_Error( "CG_TransitionSnapshot: NULL cg.snap" );
	}
	if ( !cg.nextSnap ) {
		CG_Error( "CG_TransitionSnapshot: NULL cg.nextSnap" );
	}

	// execute any server string commands before transitioning entities
	CG_ExecuteNewServerCommands( cg.nextSnap->serverCommandSequence );

	// if we had a map_restart, set everything with initial
	if ( cg.mapRestart ) {
	}

	// clear the currentValid flag for all entities in the existing snapshot
	for ( i = 0 ; i < cg.snap->numEntities ; i++ ) {
		cent = &cg_entities[ cg.snap->entities[ i ].number ];
		cent->currentValid = qfalse;
	}

	// move nextSnap to snap and do the transitions
	oldFrame = cg.snap;
	cg.snap = cg.nextSnap;

	BG_PlayerStateToEntityState( &cg.snap->ps, &cg_entities[ cg.snap->ps.clientNum ].currentState, qfalse );
	cg_entities[ cg.snap->ps.clientNum ].interpolate = qfalse;

	for ( i = 0 ; i < cg.snap->numEntities ; i++ ) {
		cent = &cg_entities[ cg.snap->entities[ i ].number ];
		CG_TransitionEntity( cent );

		// remember time of snapshot this entity was last updated in
		cent->snapShotTime = cg.snap->serverTime;
	}

	cg.nextSnap = NULL;

	// check for playerstate transition events
	if ( oldFrame ) {
		playerState_t	*ops, *ps;

		ops = &oldFrame->ps;
		ps = &cg.snap->ps;
		// teleporting checks are irrespective of prediction
		if ( ( ps->eFlags ^ ops->eFlags ) & EF_TELEPORT_BIT ) {
			cg.thisFrameTeleport = qtrue;	// will be cleared by prediction code
		}

		// if we are not doing client side movement prediction for any
		// reason, then the client events and view changes will be issued now
		if ( cg.demoPlayback || (cg.snap->ps.pm_flags & PMF_FOLLOW)
			|| cg_nopredict.integer || cg_synchronousClients.integer ) {
			CG_TransitionPlayerState( ps, ops );
		}
	}

}