#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vec3_t ;
struct TYPE_11__ {int* traveltimes; int* reachabilities; } ;
typedef  TYPE_2__ aas_routingcache_t ;
struct TYPE_12__ {int /*<<< orphan*/  start; } ;
typedef  TYPE_3__ aas_reachability_t ;
struct TYPE_13__ {int frontcluster; int backcluster; int areanum; } ;
typedef  TYPE_4__ aas_portal_t ;
struct TYPE_14__ {int numreachabilityareas; int numportals; int firstportal; } ;
typedef  TYPE_5__ aas_cluster_t ;
struct TYPE_16__ {int numareas; int* portalindex; TYPE_3__* reachability; TYPE_1__* areasettings; scalar_t__* portalmaxtraveltimes; TYPE_4__* portals; TYPE_5__* clusters; int /*<<< orphan*/  initialized; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_10__ {int cluster; int firstreachablearea; int /*<<< orphan*/  numreachableareas; } ;

/* Variables and functions */
 scalar_t__ AAS_AreaDoNotEnter (int) ; 
 unsigned short AAS_AreaTravelTime (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int AAS_ClusterAreaNum (int,int) ; 
 int /*<<< orphan*/  AAS_FreeOldestCache () ; 
 TYPE_2__* AAS_GetAreaRoutingCache (int,int,int) ; 
 TYPE_2__* AAS_GetPortalRoutingCache (int,int,int) ; 
 int AvailableMemory () ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int TFL_DONOTENTER ; 
 TYPE_7__ aasworld ; 
 scalar_t__ botDeveloper ; 
 TYPE_6__ botimport ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int) ; 

int AAS_AreaRouteToGoalArea(int areanum, vec3_t origin, int goalareanum, int travelflags, int *traveltime, int *reachnum)
{
	int clusternum, goalclusternum, portalnum, i, clusterareanum, bestreachnum;
	unsigned short int t, besttime;
	aas_portal_t *portal;
	aas_cluster_t *cluster;
	aas_routingcache_t *areacache, *portalcache;
	aas_reachability_t *reach;

	if (!aasworld.initialized) return qfalse;

	if (areanum == goalareanum)
	{
		*traveltime = 1;
		*reachnum = 0;
		return qtrue;
	}
	//check !AAS_AreaReachability(areanum) with custom developer-only debug message
	if (areanum <= 0 || areanum >= aasworld.numareas)
	{
		if (botDeveloper)
		{
			botimport.Print(PRT_ERROR, "AAS_AreaTravelTimeToGoalArea: areanum %d out of range\n", areanum);
		} //end if
		return qfalse;
	} //end if
	if (goalareanum <= 0 || goalareanum >= aasworld.numareas)
	{
		if (botDeveloper)
		{
			botimport.Print(PRT_ERROR, "AAS_AreaTravelTimeToGoalArea: goalareanum %d out of range\n", goalareanum);
		} //end if
		return qfalse;
	} //end if
	if (!aasworld.areasettings[areanum].numreachableareas || !aasworld.areasettings[goalareanum].numreachableareas)
	{
		return qfalse;
	} //end if
	// make sure the routing cache doesn't grow to large
	while(AvailableMemory() < 1 * 1024 * 1024) {
		if (!AAS_FreeOldestCache()) break;
	}
	//
	if (AAS_AreaDoNotEnter(areanum) || AAS_AreaDoNotEnter(goalareanum))
	{
		travelflags |= TFL_DONOTENTER;
	} //end if
	//NOTE: the number of routing updates is limited per frame
	/*
	if (aasworld.frameroutingupdates > MAX_FRAMEROUTINGUPDATES)
	{
#ifdef DEBUG
		//Log_Write("WARNING: AAS_AreaTravelTimeToGoalArea: frame routing updates overflowed");
#endif
		return 0;
	} //end if
	*/
	//
	clusternum = aasworld.areasettings[areanum].cluster;
	goalclusternum = aasworld.areasettings[goalareanum].cluster;
	//check if the area is a portal of the goal area cluster
	if (clusternum < 0 && goalclusternum > 0)
	{
		portal = &aasworld.portals[-clusternum];
		if (portal->frontcluster == goalclusternum ||
				portal->backcluster == goalclusternum)
		{
			clusternum = goalclusternum;
		} //end if
	} //end if
	//check if the goalarea is a portal of the area cluster
	else if (clusternum > 0 && goalclusternum < 0)
	{
		portal = &aasworld.portals[-goalclusternum];
		if (portal->frontcluster == clusternum ||
				portal->backcluster == clusternum)
		{
			goalclusternum = clusternum;
		} //end if
	} //end if
	//if both areas are in the same cluster
	//NOTE: there might be a shorter route via another cluster!!! but we don't care
	if (clusternum > 0 && goalclusternum > 0 && clusternum == goalclusternum)
	{
		//
		areacache = AAS_GetAreaRoutingCache(clusternum, goalareanum, travelflags);
		//the number of the area in the cluster
		clusterareanum = AAS_ClusterAreaNum(clusternum, areanum);
		//the cluster the area is in
		cluster = &aasworld.clusters[clusternum];
		//if the area is NOT a reachability area
		if (clusterareanum >= cluster->numreachabilityareas) return 0;
		//if it is possible to travel to the goal area through this cluster
		if (areacache->traveltimes[clusterareanum] != 0)
		{
			*reachnum = aasworld.areasettings[areanum].firstreachablearea +
							areacache->reachabilities[clusterareanum];
			if (!origin) {
				*traveltime = areacache->traveltimes[clusterareanum];
				return qtrue;
			}
			reach = &aasworld.reachability[*reachnum];
			*traveltime = areacache->traveltimes[clusterareanum] +
							AAS_AreaTravelTime(areanum, origin, reach->start);
			//
			return qtrue;
		} //end if
	} //end if
	//
	clusternum = aasworld.areasettings[areanum].cluster;
	goalclusternum = aasworld.areasettings[goalareanum].cluster;
	//if the goal area is a portal
	if (goalclusternum < 0)
	{
		//just assume the goal area is part of the front cluster
		portal = &aasworld.portals[-goalclusternum];
		goalclusternum = portal->frontcluster;
	} //end if
	//get the portal routing cache
	portalcache = AAS_GetPortalRoutingCache(goalclusternum, goalareanum, travelflags);
	//if the area is a cluster portal, read directly from the portal cache
	if (clusternum < 0)
	{
		*traveltime = portalcache->traveltimes[-clusternum];
		*reachnum = aasworld.areasettings[areanum].firstreachablearea +
						portalcache->reachabilities[-clusternum];
		return qtrue;
	} //end if
	//
	besttime = 0;
	bestreachnum = -1;
	//the cluster the area is in
	cluster = &aasworld.clusters[clusternum];
	//find the portal of the area cluster leading towards the goal area
	for (i = 0; i < cluster->numportals; i++)
	{
		portalnum = aasworld.portalindex[cluster->firstportal + i];
		//if the goal area isn't reachable from the portal
		if (!portalcache->traveltimes[portalnum]) continue;
		//
		portal = &aasworld.portals[portalnum];
		//get the cache of the portal area
		areacache = AAS_GetAreaRoutingCache(clusternum, portal->areanum, travelflags);
		//current area inside the current cluster
		clusterareanum = AAS_ClusterAreaNum(clusternum, areanum);
		//if the area is NOT a reachability area
		if (clusterareanum >= cluster->numreachabilityareas) continue;
		//if the portal is NOT reachable from this area
		if (!areacache->traveltimes[clusterareanum]) continue;
		//total travel time is the travel time the portal area is from
		//the goal area plus the travel time towards the portal area
		t = portalcache->traveltimes[portalnum] + areacache->traveltimes[clusterareanum];
		//FIXME: add the exact travel time through the actual portal area
		//NOTE: for now we just add the largest travel time through the portal area
		//		because we can't directly calculate the exact travel time
		//		to be more specific we don't know which reachability was used to travel
		//		into the portal area
		t += aasworld.portalmaxtraveltimes[portalnum];
		//
		if (origin)
		{
			*reachnum = aasworld.areasettings[areanum].firstreachablearea +
							areacache->reachabilities[clusterareanum];
			reach = aasworld.reachability + *reachnum;
			t += AAS_AreaTravelTime(areanum, origin, reach->start);
		} //end if
		//if the time is better than the one already found
		if (!besttime || t < besttime)
		{
			bestreachnum = *reachnum;
			besttime = t;
		} //end if
	} //end for
	if (bestreachnum < 0) {
		return qfalse;
	}
	*reachnum = bestreachnum;
	*traveltime = besttime;
	return qtrue;
}