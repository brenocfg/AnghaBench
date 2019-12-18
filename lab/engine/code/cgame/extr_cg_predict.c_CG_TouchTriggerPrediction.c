#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  startsolid; } ;
typedef  TYPE_1__ trace_t ;
typedef  int qboolean ;
struct TYPE_12__ {scalar_t__ eType; scalar_t__ solid; int /*<<< orphan*/  modelindex; } ;
typedef  TYPE_2__ entityState_t ;
typedef  int /*<<< orphan*/  clipHandle_t ;
struct TYPE_13__ {TYPE_2__ currentState; } ;
typedef  TYPE_3__ centity_t ;
struct TYPE_16__ {scalar_t__* stats; scalar_t__ pm_type; scalar_t__ jumppad_frame; scalar_t__ pmove_framecount; scalar_t__ jumppad_ent; int /*<<< orphan*/  origin; } ;
struct TYPE_15__ {TYPE_9__ predictedPlayerState; int /*<<< orphan*/  hyperspace; } ;
struct TYPE_14__ {int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_TouchJumpPad (TYPE_9__*,TYPE_2__*) ; 
 int /*<<< orphan*/  CG_TouchItem (TYPE_3__*) ; 
 scalar_t__ ET_ITEM ; 
 scalar_t__ ET_PUSH_TRIGGER ; 
 scalar_t__ ET_TELEPORT_TRIGGER ; 
 scalar_t__ PM_NORMAL ; 
 scalar_t__ PM_SPECTATOR ; 
 scalar_t__ SOLID_BMODEL ; 
 size_t STAT_HEALTH ; 
 TYPE_7__ cg ; 
 int cg_numTriggerEntities ; 
 TYPE_6__ cg_pmove ; 
 TYPE_3__** cg_triggerEntities ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_CM_BoxTrace (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_CM_InlineModel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CG_TouchTriggerPrediction( void ) {
	int			i;
	trace_t		trace;
	entityState_t	*ent;
	clipHandle_t cmodel;
	centity_t	*cent;
	qboolean	spectator;

	// dead clients don't activate triggers
	if ( cg.predictedPlayerState.stats[STAT_HEALTH] <= 0 ) {
		return;
	}

	spectator = ( cg.predictedPlayerState.pm_type == PM_SPECTATOR );

	if ( cg.predictedPlayerState.pm_type != PM_NORMAL && !spectator ) {
		return;
	}

	for ( i = 0 ; i < cg_numTriggerEntities ; i++ ) {
		cent = cg_triggerEntities[ i ];
		ent = &cent->currentState;

		if ( ent->eType == ET_ITEM && !spectator ) {
			CG_TouchItem( cent );
			continue;
		}

		if ( ent->solid != SOLID_BMODEL ) {
			continue;
		}

		cmodel = trap_CM_InlineModel( ent->modelindex );
		if ( !cmodel ) {
			continue;
		}

		trap_CM_BoxTrace( &trace, cg.predictedPlayerState.origin, cg.predictedPlayerState.origin, 
			cg_pmove.mins, cg_pmove.maxs, cmodel, -1 );

		if ( !trace.startsolid ) {
			continue;
		}

		if ( ent->eType == ET_TELEPORT_TRIGGER ) {
			cg.hyperspace = qtrue;
		} else if ( ent->eType == ET_PUSH_TRIGGER ) {
			BG_TouchJumpPad( &cg.predictedPlayerState, ent );
		}
	}

	// if we didn't touch a jump pad this pmove frame
	if ( cg.predictedPlayerState.jumppad_frame != cg.predictedPlayerState.pmove_framecount ) {
		cg.predictedPlayerState.jumppad_frame = 0;
		cg.predictedPlayerState.jumppad_ent = 0;
	}
}