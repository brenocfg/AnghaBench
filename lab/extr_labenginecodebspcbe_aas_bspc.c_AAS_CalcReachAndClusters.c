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
struct quakefile_s {int /*<<< orphan*/  filename; int /*<<< orphan*/ * pakfile; } ;
struct TYPE_2__ {scalar_t__ numclusters; scalar_t__ reachabilitysize; int /*<<< orphan*/  bspchecksum; } ;

/* Variables and functions */
 scalar_t__ AAS_ContinueInitReachability (float) ; 
 int /*<<< orphan*/  AAS_InitAASLinkHeap () ; 
 int /*<<< orphan*/  AAS_InitAASLinkedEntities () ; 
 int /*<<< orphan*/  AAS_InitBotImport () ; 
 int /*<<< orphan*/  AAS_InitClustering () ; 
 int /*<<< orphan*/  AAS_InitReachability () ; 
 int /*<<< orphan*/  AAS_InitSettings () ; 
 int /*<<< orphan*/  AAS_LoadBSPFile () ; 
 int /*<<< orphan*/  AAS_SetViewPortalsAsClusterPortals () ; 
 int /*<<< orphan*/  CM_InlineModel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CM_LoadMap (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 TYPE_1__ aasworld ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  worldmodel ; 

void AAS_CalcReachAndClusters(struct quakefile_s *qf)
{
	float time;

	Log_Print("loading collision map...\n");
	//
	if (!qf->pakfile[0]) strcpy(qf->pakfile, qf->filename);
	//load the map
	CM_LoadMap((char *) qf, qfalse, &aasworld.bspchecksum);
	//get a handle to the world model
	worldmodel = CM_InlineModel(0);		// 0 = world, 1 + are bmodels
	//initialize bot import structure
	AAS_InitBotImport();
	//load the BSP entity string
	AAS_LoadBSPFile();
	//init physics settings
	AAS_InitSettings();
	//initialize AAS link heap
	AAS_InitAASLinkHeap();
	//initialize the AAS linked entities for the new map
	AAS_InitAASLinkedEntities();
	//reset all reachabilities and clusters
	aasworld.reachabilitysize = 0;
	aasworld.numclusters = 0;
	//set all view portals as cluster portals in case we re-calculate the reachabilities and clusters (with -reach)
	AAS_SetViewPortalsAsClusterPortals();
	//calculate reachabilities
	AAS_InitReachability();
	time = 0;
	while(AAS_ContinueInitReachability(time)) time++;
	//calculate clusters
	AAS_InitClustering();
}