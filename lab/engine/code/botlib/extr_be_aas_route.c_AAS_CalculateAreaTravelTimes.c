#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_7__ {TYPE_2__* first; int /*<<< orphan*/  numlinks; } ;
typedef  TYPE_1__ aas_reversedreachability_t ;
struct TYPE_8__ {size_t linknum; struct TYPE_8__* next; } ;
typedef  TYPE_2__ aas_reversedlink_t ;
struct TYPE_9__ {int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;
typedef  TYPE_3__ aas_reachability_t ;
struct TYPE_10__ {int numreachableareas; int firstreachablearea; } ;
typedef  TYPE_4__ aas_areasettings_t ;
struct TYPE_12__ {unsigned short*** areatraveltimes; int numareas; TYPE_3__* reachability; TYPE_4__* areasettings; TYPE_1__* reversedreachability; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 unsigned short AAS_AreaTravelTime (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeMemory (unsigned short***) ; 
 scalar_t__ GetClearedMemory (int) ; 
 int PAD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int Sys_MilliSeconds () ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ aasworld ; 
 TYPE_5__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

void AAS_CalculateAreaTravelTimes(void)
{
	int i, l, n, size;
	char *ptr;
	vec3_t end;
	aas_reversedreachability_t *revreach;
	aas_reversedlink_t *revlink;
	aas_reachability_t *reach;
	aas_areasettings_t *settings;
#ifdef DEBUG
	int starttime;

	starttime = Sys_MilliSeconds();
#endif
	//if there are still area travel times, free the memory
	if (aasworld.areatraveltimes) FreeMemory(aasworld.areatraveltimes);
	//get the total size of all the area travel times
	size = aasworld.numareas * sizeof(unsigned short **);
	for (i = 0; i < aasworld.numareas; i++)
	{
		revreach = &aasworld.reversedreachability[i];
		//settings of the area
		settings = &aasworld.areasettings[i];
		//
		size += settings->numreachableareas * sizeof(unsigned short *);
		//
		size += settings->numreachableareas *
			PAD(revreach->numlinks, sizeof(long)) * sizeof(unsigned short);
	} //end for
	//allocate memory for the area travel times
	ptr = (char *) GetClearedMemory(size);
	aasworld.areatraveltimes = (unsigned short ***) ptr;
	ptr += aasworld.numareas * sizeof(unsigned short **);
	//calcluate the travel times for all the areas
	for (i = 0; i < aasworld.numareas; i++)
	{
		//reversed reachabilities of this area
		revreach = &aasworld.reversedreachability[i];
		//settings of the area
		settings = &aasworld.areasettings[i];
		//
		aasworld.areatraveltimes[i] = (unsigned short **) ptr;
		ptr += settings->numreachableareas * sizeof(unsigned short *);
		//
		for (l = 0; l < settings->numreachableareas; l++)
		{
			aasworld.areatraveltimes[i][l] = (unsigned short *) ptr;
			ptr += PAD(revreach->numlinks, sizeof(long)) * sizeof(unsigned short);
			//reachability link
			reach = &aasworld.reachability[settings->firstreachablearea + l];
			//
			for (n = 0, revlink = revreach->first; revlink; revlink = revlink->next, n++)
			{
				VectorCopy(aasworld.reachability[revlink->linknum].end, end);
				//
				aasworld.areatraveltimes[i][l][n] = AAS_AreaTravelTime(i, end, reach->start);
			} //end for
		} //end for
	} //end for
#ifdef DEBUG
	botimport.Print(PRT_MESSAGE, "area travel times %d msec\n", Sys_MilliSeconds() - starttime);
#endif
}