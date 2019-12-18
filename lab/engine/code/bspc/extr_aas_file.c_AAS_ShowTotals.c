#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  numclusters; int /*<<< orphan*/  portalindexsize; int /*<<< orphan*/  numportals; int /*<<< orphan*/  numnodes; int /*<<< orphan*/  reachabilitysize; int /*<<< orphan*/  numareasettings; int /*<<< orphan*/  numareas; int /*<<< orphan*/  faceindexsize; int /*<<< orphan*/  numfaces; int /*<<< orphan*/  edgeindexsize; int /*<<< orphan*/  numedges; int /*<<< orphan*/  numplanes; int /*<<< orphan*/  numvertexes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_ShowNumReachabilities (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Log_Print (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRAVEL_BARRIERJUMP ; 
 int /*<<< orphan*/  TRAVEL_BFGJUMP ; 
 int /*<<< orphan*/  TRAVEL_CROUCH ; 
 int /*<<< orphan*/  TRAVEL_DOUBLEJUMP ; 
 int /*<<< orphan*/  TRAVEL_ELEVATOR ; 
 int /*<<< orphan*/  TRAVEL_FUNCBOB ; 
 int /*<<< orphan*/  TRAVEL_GRAPPLEHOOK ; 
 int /*<<< orphan*/  TRAVEL_JUMP ; 
 int /*<<< orphan*/  TRAVEL_JUMPPAD ; 
 int /*<<< orphan*/  TRAVEL_LADDER ; 
 int /*<<< orphan*/  TRAVEL_RAMPJUMP ; 
 int /*<<< orphan*/  TRAVEL_ROCKETJUMP ; 
 int /*<<< orphan*/  TRAVEL_STRAFEJUMP ; 
 int /*<<< orphan*/  TRAVEL_SWIM ; 
 int /*<<< orphan*/  TRAVEL_TELEPORT ; 
 int /*<<< orphan*/  TRAVEL_WALK ; 
 int /*<<< orphan*/  TRAVEL_WALKOFFLEDGE ; 
 int /*<<< orphan*/  TRAVEL_WATERJUMP ; 
 TYPE_1__ aasworld ; 

void AAS_ShowTotals(void)
{
	Log_Print("numvertexes = %d\r\n", aasworld.numvertexes);
	Log_Print("numplanes = %d\r\n", aasworld.numplanes);
	Log_Print("numedges = %d\r\n", aasworld.numedges);
	Log_Print("edgeindexsize = %d\r\n", aasworld.edgeindexsize);
	Log_Print("numfaces = %d\r\n", aasworld.numfaces);
	Log_Print("faceindexsize = %d\r\n", aasworld.faceindexsize);
	Log_Print("numareas = %d\r\n", aasworld.numareas);
	Log_Print("numareasettings = %d\r\n", aasworld.numareasettings);
	Log_Print("reachabilitysize = %d\r\n", aasworld.reachabilitysize);
	Log_Print("numnodes = %d\r\n", aasworld.numnodes);
	Log_Print("numportals = %d\r\n", aasworld.numportals);
	Log_Print("portalindexsize = %d\r\n", aasworld.portalindexsize);
	Log_Print("numclusters = %d\r\n", aasworld.numclusters);
	AAS_ShowNumReachabilities(TRAVEL_WALK, "walk");
	AAS_ShowNumReachabilities(TRAVEL_CROUCH, "crouch");
	AAS_ShowNumReachabilities(TRAVEL_BARRIERJUMP, "barrier jump");
	AAS_ShowNumReachabilities(TRAVEL_JUMP, "jump");
	AAS_ShowNumReachabilities(TRAVEL_LADDER, "ladder");
	AAS_ShowNumReachabilities(TRAVEL_WALKOFFLEDGE, "walk off ledge");
	AAS_ShowNumReachabilities(TRAVEL_SWIM, "swim");
	AAS_ShowNumReachabilities(TRAVEL_WATERJUMP, "water jump");
	AAS_ShowNumReachabilities(TRAVEL_TELEPORT, "teleport");
	AAS_ShowNumReachabilities(TRAVEL_ELEVATOR, "elevator");
	AAS_ShowNumReachabilities(TRAVEL_ROCKETJUMP, "rocket jump");
	AAS_ShowNumReachabilities(TRAVEL_BFGJUMP, "bfg jump");
	AAS_ShowNumReachabilities(TRAVEL_GRAPPLEHOOK, "grapple hook");
	AAS_ShowNumReachabilities(TRAVEL_DOUBLEJUMP, "double jump");
	AAS_ShowNumReachabilities(TRAVEL_RAMPJUMP, "ramp jump");
	AAS_ShowNumReachabilities(TRAVEL_STRAFEJUMP, "strafe jump");
	AAS_ShowNumReachabilities(TRAVEL_JUMPPAD, "jump pad");
	AAS_ShowNumReachabilities(TRAVEL_FUNCBOB, "func bob");
}