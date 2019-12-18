#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ trType; } ;
struct TYPE_14__ {scalar_t__ number; int /*<<< orphan*/  groundEntityNum; TYPE_10__ apos; TYPE_10__ pos; } ;
struct TYPE_12__ {scalar_t__ trType; } ;
struct TYPE_13__ {TYPE_1__ pos; } ;
struct TYPE_16__ {int /*<<< orphan*/  lerpAngles; int /*<<< orphan*/  lerpOrigin; TYPE_3__ currentState; scalar_t__ interpolate; TYPE_2__ nextState; } ;
typedef  TYPE_5__ centity_t ;
struct TYPE_18__ {int /*<<< orphan*/  time; TYPE_4__* snap; TYPE_5__ predictedPlayerEntity; } ;
struct TYPE_17__ {int /*<<< orphan*/  integer; } ;
struct TYPE_15__ {int /*<<< orphan*/  serverTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_EvaluateTrajectory (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_AdjustPositionForMover (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_InterpolateEntityPosition (TYPE_5__*) ; 
 scalar_t__ MAX_CLIENTS ; 
 scalar_t__ TR_INTERPOLATE ; 
 scalar_t__ TR_LINEAR_STOP ; 
 TYPE_7__ cg ; 
 TYPE_6__ cg_smoothClients ; 

__attribute__((used)) static void CG_CalcEntityLerpPositions( centity_t *cent ) {

	// if this player does not want to see extrapolated players
	if ( !cg_smoothClients.integer ) {
		// make sure the clients use TR_INTERPOLATE
		if ( cent->currentState.number < MAX_CLIENTS ) {
			cent->currentState.pos.trType = TR_INTERPOLATE;
			cent->nextState.pos.trType = TR_INTERPOLATE;
		}
	}

	if ( cent->interpolate && cent->currentState.pos.trType == TR_INTERPOLATE ) {
		CG_InterpolateEntityPosition( cent );
		return;
	}

	// first see if we can interpolate between two snaps for
	// linear extrapolated clients
	if ( cent->interpolate && cent->currentState.pos.trType == TR_LINEAR_STOP &&
											cent->currentState.number < MAX_CLIENTS) {
		CG_InterpolateEntityPosition( cent );
		return;
	}

	// just use the current frame and evaluate as best we can
	BG_EvaluateTrajectory( &cent->currentState.pos, cg.time, cent->lerpOrigin );
	BG_EvaluateTrajectory( &cent->currentState.apos, cg.time, cent->lerpAngles );

	// adjust for riding a mover if it wasn't rolled into the predicted
	// player state
	if ( cent != &cg.predictedPlayerEntity ) {
		CG_AdjustPositionForMover( cent->lerpOrigin, cent->currentState.groundEntityNum, 
		cg.snap->serverTime, cg.time, cent->lerpOrigin, cent->lerpAngles, cent->lerpAngles);
	}
}