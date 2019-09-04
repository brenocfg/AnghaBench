#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {size_t clientNum; } ;
struct TYPE_12__ {int numEntities; TYPE_2__* entities; int /*<<< orphan*/  serverCommandSequence; TYPE_10__ ps; } ;
typedef  TYPE_1__ snapshot_t ;
struct TYPE_13__ {size_t number; } ;
typedef  TYPE_2__ entityState_t ;
struct TYPE_14__ {int /*<<< orphan*/  currentValid; int /*<<< orphan*/  interpolate; int /*<<< orphan*/  currentState; } ;
typedef  TYPE_3__ centity_t ;
struct TYPE_15__ {TYPE_1__* snap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_PlayerStateToEntityState (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_BuildSolidList () ; 
 int /*<<< orphan*/  CG_CheckEvents (TYPE_3__*) ; 
 int /*<<< orphan*/  CG_ExecuteNewServerCommands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_ResetEntity (TYPE_3__*) ; 
 int /*<<< orphan*/  CG_Respawn () ; 
 TYPE_6__ cg ; 
 TYPE_3__* cg_entities ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

void CG_SetInitialSnapshot( snapshot_t *snap ) {
	int				i;
	centity_t		*cent;
	entityState_t	*state;

	cg.snap = snap;

	BG_PlayerStateToEntityState( &snap->ps, &cg_entities[ snap->ps.clientNum ].currentState, qfalse );

	// sort out solid entities
	CG_BuildSolidList();

	CG_ExecuteNewServerCommands( snap->serverCommandSequence );

	// set our local weapon selection pointer to
	// what the server has indicated the current weapon is
	CG_Respawn();

	for ( i = 0 ; i < cg.snap->numEntities ; i++ ) {
		state = &cg.snap->entities[ i ];
		cent = &cg_entities[ state->number ];

		memcpy(&cent->currentState, state, sizeof(entityState_t));
		//cent->currentState = *state;
		cent->interpolate = qfalse;
		cent->currentValid = qtrue;

		CG_ResetEntity( cent );

		// check for events
		CG_CheckEvents( cent );
	}
}