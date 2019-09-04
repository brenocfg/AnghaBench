#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  AAS_PredictClientMovement; int /*<<< orphan*/  AAS_Swimming; int /*<<< orphan*/  AAS_AlternativeRouteGoals; int /*<<< orphan*/  AAS_PredictRoute; int /*<<< orphan*/  AAS_EnableRoutingArea; int /*<<< orphan*/  AAS_AreaTravelTimeToGoalArea; int /*<<< orphan*/  AAS_AreaReachability; int /*<<< orphan*/  AAS_IntForBSPEpairKey; int /*<<< orphan*/  AAS_FloatForBSPEpairKey; int /*<<< orphan*/  AAS_VectorForBSPEpairKey; int /*<<< orphan*/  AAS_ValueForBSPEpairKey; int /*<<< orphan*/  AAS_NextBSPEntity; int /*<<< orphan*/  AAS_PointContents; int /*<<< orphan*/  AAS_AreaInfo; int /*<<< orphan*/  AAS_BBoxAreas; int /*<<< orphan*/  AAS_TraceAreas; int /*<<< orphan*/  AAS_PointReachabilityAreaIndex; int /*<<< orphan*/  AAS_PointAreaNum; int /*<<< orphan*/  AAS_Time; int /*<<< orphan*/  AAS_PresenceTypeBoundingBox; int /*<<< orphan*/  AAS_Initialized; int /*<<< orphan*/  AAS_EntityInfo; } ;
typedef  TYPE_1__ aas_export_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_AlternativeRouteGoals ; 
 int /*<<< orphan*/  AAS_AreaInfo ; 
 int /*<<< orphan*/  AAS_AreaReachability ; 
 int /*<<< orphan*/  AAS_AreaTravelTimeToGoalArea ; 
 int /*<<< orphan*/  AAS_BBoxAreas ; 
 int /*<<< orphan*/  AAS_EnableRoutingArea ; 
 int /*<<< orphan*/  AAS_EntityInfo ; 
 int /*<<< orphan*/  AAS_FloatForBSPEpairKey ; 
 int /*<<< orphan*/  AAS_Initialized ; 
 int /*<<< orphan*/  AAS_IntForBSPEpairKey ; 
 int /*<<< orphan*/  AAS_NextBSPEntity ; 
 int /*<<< orphan*/  AAS_PointAreaNum ; 
 int /*<<< orphan*/  AAS_PointContents ; 
 int /*<<< orphan*/  AAS_PointReachabilityAreaIndex ; 
 int /*<<< orphan*/  AAS_PredictClientMovement ; 
 int /*<<< orphan*/  AAS_PredictRoute ; 
 int /*<<< orphan*/  AAS_PresenceTypeBoundingBox ; 
 int /*<<< orphan*/  AAS_Swimming ; 
 int /*<<< orphan*/  AAS_Time ; 
 int /*<<< orphan*/  AAS_TraceAreas ; 
 int /*<<< orphan*/  AAS_ValueForBSPEpairKey ; 
 int /*<<< orphan*/  AAS_VectorForBSPEpairKey ; 

__attribute__((used)) static void Init_AAS_Export( aas_export_t *aas ) {
	//--------------------------------------------
	// be_aas_entity.c
	//--------------------------------------------
	aas->AAS_EntityInfo = AAS_EntityInfo;
	//--------------------------------------------
	// be_aas_main.c
	//--------------------------------------------
	aas->AAS_Initialized = AAS_Initialized;
	aas->AAS_PresenceTypeBoundingBox = AAS_PresenceTypeBoundingBox;
	aas->AAS_Time = AAS_Time;
	//--------------------------------------------
	// be_aas_sample.c
	//--------------------------------------------
	aas->AAS_PointAreaNum = AAS_PointAreaNum;
	aas->AAS_PointReachabilityAreaIndex = AAS_PointReachabilityAreaIndex;
	aas->AAS_TraceAreas = AAS_TraceAreas;
	aas->AAS_BBoxAreas = AAS_BBoxAreas;
	aas->AAS_AreaInfo = AAS_AreaInfo;
	//--------------------------------------------
	// be_aas_bspq3.c
	//--------------------------------------------
	aas->AAS_PointContents = AAS_PointContents;
	aas->AAS_NextBSPEntity = AAS_NextBSPEntity;
	aas->AAS_ValueForBSPEpairKey = AAS_ValueForBSPEpairKey;
	aas->AAS_VectorForBSPEpairKey = AAS_VectorForBSPEpairKey;
	aas->AAS_FloatForBSPEpairKey = AAS_FloatForBSPEpairKey;
	aas->AAS_IntForBSPEpairKey = AAS_IntForBSPEpairKey;
	//--------------------------------------------
	// be_aas_reach.c
	//--------------------------------------------
	aas->AAS_AreaReachability = AAS_AreaReachability;
	//--------------------------------------------
	// be_aas_route.c
	//--------------------------------------------
	aas->AAS_AreaTravelTimeToGoalArea = AAS_AreaTravelTimeToGoalArea;
	aas->AAS_EnableRoutingArea = AAS_EnableRoutingArea;
	aas->AAS_PredictRoute = AAS_PredictRoute;
	//--------------------------------------------
	// be_aas_altroute.c
	//--------------------------------------------
	aas->AAS_AlternativeRouteGoals = AAS_AlternativeRouteGoals;
	//--------------------------------------------
	// be_aas_move.c
	//--------------------------------------------
	aas->AAS_Swimming = AAS_Swimming;
	aas->AAS_PredictClientMovement = AAS_PredictClientMovement;
}