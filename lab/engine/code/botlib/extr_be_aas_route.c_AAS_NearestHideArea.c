#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
typedef  void* qboolean ;
struct TYPE_6__ {int areanum; scalar_t__* start; unsigned short tmptraveltime; void* inlist; struct TYPE_6__* next; struct TYPE_6__* prev; int /*<<< orphan*/  areatraveltimes; } ;
typedef  TYPE_2__ aas_routingupdate_t ;
struct TYPE_7__ {int areanum; unsigned short traveltime; scalar_t__* end; int /*<<< orphan*/  start; int /*<<< orphan*/  traveltype; } ;
typedef  TYPE_3__ aas_reachability_t ;
struct TYPE_8__ {int numareas; TYPE_2__* areaupdate; TYPE_1__* areasettings; TYPE_3__* reachability; int /*<<< orphan*/ ** areatraveltimes; } ;
struct TYPE_5__ {int numreachableareas; size_t firstreachablearea; } ;

/* Variables and functions */
 int AAS_AreaContentsTravelFlags_inline (int) ; 
 unsigned short AAS_AreaTravelTime (size_t,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ AAS_AreaVisible (int,int) ; 
 int /*<<< orphan*/  AAS_ProjectPointOntoVector (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int AAS_TravelFlagForType_inline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Memset (unsigned short*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GetClearedMemory (int) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 float VectorLength (scalar_t__*) ; 
 int /*<<< orphan*/  VectorSubtract (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 TYPE_4__ aasworld ; 
 void* qfalse ; 
 void* qtrue ; 

int AAS_NearestHideArea(int srcnum, vec3_t origin, int areanum, int enemynum, vec3_t enemyorigin, int enemyareanum, int travelflags)
{
	int i, j, nextareanum, badtravelflags, numreach, bestarea;
	unsigned short int t, besttraveltime;
	static unsigned short int *hidetraveltimes;
	aas_routingupdate_t *updateliststart, *updatelistend, *curupdate, *nextupdate;
	aas_reachability_t *reach;
	float dist1, dist2;
	vec3_t v1, v2, p;
	qboolean startVisible;

	//
	if (!hidetraveltimes)
	{
		hidetraveltimes = (unsigned short int *) GetClearedMemory(aasworld.numareas * sizeof(unsigned short int));
	} //end if
	else
	{
		Com_Memset(hidetraveltimes, 0, aasworld.numareas * sizeof(unsigned short int));
	} //end else
	besttraveltime = 0;
	bestarea = 0;
	//assume visible
	startVisible = qtrue;
	//
	badtravelflags = ~travelflags;
	//
	curupdate = &aasworld.areaupdate[areanum];
	curupdate->areanum = areanum;
	VectorCopy(origin, curupdate->start);
	curupdate->areatraveltimes = aasworld.areatraveltimes[areanum][0];
	curupdate->tmptraveltime = 0;
	//put the area to start with in the current read list
	curupdate->next = NULL;
	curupdate->prev = NULL;
	updateliststart = curupdate;
	updatelistend = curupdate;
	//while there are updates in the list
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
		numreach = aasworld.areasettings[curupdate->areanum].numreachableareas;
		reach = &aasworld.reachability[aasworld.areasettings[curupdate->areanum].firstreachablearea];
		//
		for (i = 0; i < numreach; i++, reach++)
		{
			//if an undesired travel type is used
			if (AAS_TravelFlagForType_inline(reach->traveltype) & badtravelflags) continue;
			//
			if (AAS_AreaContentsTravelFlags_inline(reach->areanum) & badtravelflags) continue;
			//number of the area the reachability leads to
			nextareanum = reach->areanum;
			// if this moves us into the enemies area, skip it
			if (nextareanum == enemyareanum) continue;
			//time already travelled plus the traveltime through
			//the current area plus the travel time from the reachability
			t = curupdate->tmptraveltime +
						AAS_AreaTravelTime(curupdate->areanum, curupdate->start, reach->start) +
							reach->traveltime;

			//avoid going near the enemy
			AAS_ProjectPointOntoVector(enemyorigin, curupdate->start, reach->end, p);
			for (j = 0; j < 3; j++)
				if ((p[j] > curupdate->start[j] && p[j] > reach->end[j]) ||
					(p[j] < curupdate->start[j] && p[j] < reach->end[j]))
					break;
			if (j < 3)
			{
				VectorSubtract(enemyorigin, reach->end, v2);
			} //end if
			else
			{
				VectorSubtract(enemyorigin, p, v2);
			} //end else
			dist2 = VectorLength(v2);
			//never go through the enemy
			if (dist2 < 40) continue;
			//
			VectorSubtract(enemyorigin, curupdate->start, v1);
			dist1 = VectorLength(v1);
			//
			if (dist2 < dist1)
			{
				t += (dist1 - dist2) * 10;
			}
			// if we weren't visible when starting, make sure we don't move into their view
			if (!startVisible && AAS_AreaVisible(enemyareanum, nextareanum)) {
				continue;
			}
			//
			if (besttraveltime && t >= besttraveltime) continue;
			//
			if (!hidetraveltimes[nextareanum] ||
					hidetraveltimes[nextareanum] > t)
			{
				//if the nextarea is not visible from the enemy area
				if (!AAS_AreaVisible(enemyareanum, nextareanum))
				{
					besttraveltime = t;
					bestarea = nextareanum;
				} //end if
				hidetraveltimes[nextareanum] = t;
				nextupdate = &aasworld.areaupdate[nextareanum];
				nextupdate->areanum = nextareanum;
				nextupdate->tmptraveltime = t;
				//remember where we entered this area
				VectorCopy(reach->end, nextupdate->start);
				//if this update is not in the list yet
				if (!nextupdate->inlist)
				{
					//add the new update to the end of the list
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
	return bestarea;
}