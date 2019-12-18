#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  traveltime; int /*<<< orphan*/  traveltype; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  edgenum; int /*<<< orphan*/  facenum; int /*<<< orphan*/  areanum; } ;
typedef  TYPE_1__ aas_reachability_t ;
struct TYPE_8__ {int /*<<< orphan*/  traveltime; int /*<<< orphan*/  traveltype; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  edgenum; int /*<<< orphan*/  facenum; int /*<<< orphan*/  areanum; struct TYPE_8__* next; } ;
typedef  TYPE_2__ aas_lreachability_t ;
struct TYPE_9__ {size_t firstreachablearea; size_t numreachableareas; } ;
typedef  TYPE_3__ aas_areasettings_t ;
struct TYPE_10__ {int reachabilitysize; int numareas; TYPE_1__* reachability; TYPE_3__* areasettings; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 
 scalar_t__ GetClearedMemory (int) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ aasworld ; 
 TYPE_2__** areareachability ; 
 int numlreachabilities ; 

void AAS_StoreReachability(void)
{
	int i;
	aas_areasettings_t *areasettings;
	aas_lreachability_t *lreach;
	aas_reachability_t *reach;

	if (aasworld.reachability) FreeMemory(aasworld.reachability);
	aasworld.reachability = (aas_reachability_t *) GetClearedMemory((numlreachabilities + 10) * sizeof(aas_reachability_t));
	aasworld.reachabilitysize = 1;
	for (i = 0; i < aasworld.numareas; i++)
	{
		areasettings = &aasworld.areasettings[i];
		areasettings->firstreachablearea = aasworld.reachabilitysize;
		areasettings->numreachableareas = 0;
		for (lreach = areareachability[i]; lreach; lreach = lreach->next)
		{
			reach = &aasworld.reachability[areasettings->firstreachablearea +
													areasettings->numreachableareas];
			reach->areanum = lreach->areanum;
			reach->facenum = lreach->facenum;
			reach->edgenum = lreach->edgenum;
			VectorCopy(lreach->start, reach->start);
			VectorCopy(lreach->end, reach->end);
			reach->traveltype = lreach->traveltype;
			reach->traveltime = lreach->traveltime;
			//
			areasettings->numreachableareas++;
		} //end for
		aasworld.reachabilitysize += areasettings->numreachableareas;
	} //end for
}