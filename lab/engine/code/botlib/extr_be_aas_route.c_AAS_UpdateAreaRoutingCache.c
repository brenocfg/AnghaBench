#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  startareatraveltimes ;
struct TYPE_12__ {int areanum; unsigned short* areatraveltimes; unsigned short tmptraveltime; scalar_t__ inlist; struct TYPE_12__* next; struct TYPE_12__* prev; } ;
typedef  TYPE_3__ aas_routingupdate_t ;
struct TYPE_13__ {size_t cluster; int travelflags; int areanum; unsigned short starttraveltime; unsigned short* traveltimes; int* reachabilities; } ;
typedef  TYPE_4__ aas_routingcache_t ;
struct TYPE_14__ {TYPE_6__* first; } ;
typedef  TYPE_5__ aas_reversedreachability_t ;
struct TYPE_15__ {int linknum; int areanum; struct TYPE_15__* next; } ;
typedef  TYPE_6__ aas_reversedlink_t ;
struct TYPE_16__ {size_t areanum; unsigned short traveltime; int /*<<< orphan*/  traveltype; } ;
typedef  TYPE_7__ aas_reachability_t ;
struct TYPE_17__ {unsigned short*** areatraveltimes; TYPE_2__* areasettings; TYPE_3__* areaupdate; TYPE_7__* reachability; TYPE_5__* reversedreachability; int /*<<< orphan*/  frameroutingupdates; TYPE_1__* clusters; } ;
struct TYPE_11__ {int areaflags; int cluster; int firstreachablearea; } ;
struct TYPE_10__ {int numreachabilityareas; } ;

/* Variables and functions */
 int AAS_AreaContentsTravelFlags_inline (size_t) ; 
 int AAS_ClusterAreaNum (size_t,int) ; 
 int AAS_TravelFlagForType_inline (int /*<<< orphan*/ ) ; 
 int AREA_DISABLED ; 
 int /*<<< orphan*/  Com_Memset (unsigned short*,int /*<<< orphan*/ ,int) ; 
 TYPE_8__ aasworld ; 
 int /*<<< orphan*/  numareacacheupdates ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

void AAS_UpdateAreaRoutingCache(aas_routingcache_t *areacache)
{
	int i, nextareanum, cluster, badtravelflags, clusterareanum, linknum;
	int numreachabilityareas;
	unsigned short int t, startareatraveltimes[128]; //NOTE: not more than 128 reachabilities per area allowed
	aas_routingupdate_t *updateliststart, *updatelistend, *curupdate, *nextupdate;
	aas_reachability_t *reach;
	aas_reversedreachability_t *revreach;
	aas_reversedlink_t *revlink;

#ifdef ROUTING_DEBUG
	numareacacheupdates++;
#endif //ROUTING_DEBUG
	//number of reachability areas within this cluster
	numreachabilityareas = aasworld.clusters[areacache->cluster].numreachabilityareas;
	//
	aasworld.frameroutingupdates++;
	//clear the routing update fields
//	Com_Memset(aasworld.areaupdate, 0, aasworld.numareas * sizeof(aas_routingupdate_t));
	//
	badtravelflags = ~areacache->travelflags;
	//
	clusterareanum = AAS_ClusterAreaNum(areacache->cluster, areacache->areanum);
	if (clusterareanum >= numreachabilityareas) return;
	//
	Com_Memset(startareatraveltimes, 0, sizeof(startareatraveltimes));
	//
	curupdate = &aasworld.areaupdate[clusterareanum];
	curupdate->areanum = areacache->areanum;
	//VectorCopy(areacache->origin, curupdate->start);
	curupdate->areatraveltimes = startareatraveltimes;
	curupdate->tmptraveltime = areacache->starttraveltime;
	//
	areacache->traveltimes[clusterareanum] = areacache->starttraveltime;
	//put the area to start with in the current read list
	curupdate->next = NULL;
	curupdate->prev = NULL;
	updateliststart = curupdate;
	updatelistend = curupdate;
	//while there are updates in the current list
	while (updateliststart)
	{
		curupdate = updateliststart;
		//
		if (curupdate->next) curupdate->next->prev = NULL;
		else updatelistend = NULL;
		updateliststart = curupdate->next;
		//
		curupdate->inlist = qfalse;
		//check all reversed reachability links
		revreach = &aasworld.reversedreachability[curupdate->areanum];
		//
		for (i = 0, revlink = revreach->first; revlink; revlink = revlink->next, i++)
		{
			linknum = revlink->linknum;
			reach = &aasworld.reachability[linknum];
			//if there is used an undesired travel type
			if (AAS_TravelFlagForType_inline(reach->traveltype) & badtravelflags) continue;
			//if not allowed to enter the next area
			if (aasworld.areasettings[reach->areanum].areaflags & AREA_DISABLED) continue;
			//if the next area has a not allowed travel flag
			if (AAS_AreaContentsTravelFlags_inline(reach->areanum) & badtravelflags) continue;
			//number of the area the reversed reachability leads to
			nextareanum = revlink->areanum;
			//get the cluster number of the area
			cluster = aasworld.areasettings[nextareanum].cluster;
			//don't leave the cluster
			if (cluster > 0 && cluster != areacache->cluster) continue;
			//get the number of the area in the cluster
			clusterareanum = AAS_ClusterAreaNum(areacache->cluster, nextareanum);
			if (clusterareanum >= numreachabilityareas) continue;
			//time already travelled plus the traveltime through
			//the current area plus the travel time from the reachability
			t = curupdate->tmptraveltime +
						//AAS_AreaTravelTime(curupdate->areanum, curupdate->start, reach->end) +
						curupdate->areatraveltimes[i] +
							reach->traveltime;
			//
			if (!areacache->traveltimes[clusterareanum] ||
					areacache->traveltimes[clusterareanum] > t)
			{
				areacache->traveltimes[clusterareanum] = t;
				areacache->reachabilities[clusterareanum] = linknum - aasworld.areasettings[nextareanum].firstreachablearea;
				nextupdate = &aasworld.areaupdate[clusterareanum];
				nextupdate->areanum = nextareanum;
				nextupdate->tmptraveltime = t;
				//VectorCopy(reach->start, nextupdate->start);
				nextupdate->areatraveltimes = aasworld.areatraveltimes[nextareanum][linknum -
													aasworld.areasettings[nextareanum].firstreachablearea];
				if (!nextupdate->inlist)
				{
					// we add the update to the end of the list
					// we could also use a B+ tree to have a real sorted list
					// on travel time which makes for faster routing updates
					nextupdate->next = NULL;
					nextupdate->prev = updatelistend;
					if (updatelistend) updatelistend->next = nextupdate;
					else updateliststart = nextupdate;
					updatelistend = nextupdate;
					nextupdate->inlist = qtrue;
				} //end if
			} //end if
		} //end for
	} //end while
}