#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  playerState_t ;
struct TYPE_14__ {int /*<<< orphan*/  currentState; } ;
typedef  TYPE_5__ centity_t ;
struct TYPE_15__ {float frameInterpolation; int time; int* autoAngles; int* autoAnglesFast; TYPE_4__* snap; TYPE_5__ predictedPlayerEntity; int /*<<< orphan*/  predictedPlayerState; int /*<<< orphan*/  autoAxisFast; int /*<<< orphan*/  autoAxis; TYPE_1__* nextSnap; } ;
struct TYPE_11__ {size_t clientNum; } ;
struct TYPE_13__ {int serverTime; int numEntities; TYPE_3__* entities; TYPE_2__ ps; } ;
struct TYPE_12__ {size_t number; } ;
struct TYPE_10__ {int serverTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  AnglesToAxis (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BG_PlayerStateToEntityState (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_AddCEntity (TYPE_5__*) ; 
 int /*<<< orphan*/  CG_CalcEntityLerpPositions (TYPE_5__*) ; 
 TYPE_7__ cg ; 
 TYPE_5__* cg_entities ; 
 int /*<<< orphan*/  qfalse ; 

void CG_AddPacketEntities( void ) {
	int					num;
	centity_t			*cent;
	playerState_t		*ps;

	// set cg.frameInterpolation
	if ( cg.nextSnap ) {
		int		delta;

		delta = (cg.nextSnap->serverTime - cg.snap->serverTime);
		if ( delta == 0 ) {
			cg.frameInterpolation = 0;
		} else {
			cg.frameInterpolation = (float)( cg.time - cg.snap->serverTime ) / delta;
		}
	} else {
		cg.frameInterpolation = 0;	// actually, it should never be used, because 
									// no entities should be marked as interpolating
	}

	// the auto-rotating items will all have the same axis
	cg.autoAngles[0] = 0;
	cg.autoAngles[1] = ( cg.time & 2047 ) * 360 / 2048.0;
	cg.autoAngles[2] = 0;

	cg.autoAnglesFast[0] = 0;
	cg.autoAnglesFast[1] = ( cg.time & 1023 ) * 360 / 1024.0f;
	cg.autoAnglesFast[2] = 0;

	AnglesToAxis( cg.autoAngles, cg.autoAxis );
	AnglesToAxis( cg.autoAnglesFast, cg.autoAxisFast );

	// generate and add the entity from the playerstate
	ps = &cg.predictedPlayerState;
	BG_PlayerStateToEntityState( ps, &cg.predictedPlayerEntity.currentState, qfalse );
	CG_AddCEntity( &cg.predictedPlayerEntity );

	// lerp the non-predicted value for lightning gun origins
	CG_CalcEntityLerpPositions( &cg_entities[ cg.snap->ps.clientNum ] );

	// add each entity sent over by the server
	for ( num = 0 ; num < cg.snap->numEntities ; num++ ) {
		cent = &cg_entities[ cg.snap->entities[ num ].number ];
		CG_AddCEntity( cent );
	}
}