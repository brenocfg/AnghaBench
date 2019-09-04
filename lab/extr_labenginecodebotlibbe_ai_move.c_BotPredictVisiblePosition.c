#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_6__ {int areanum; int /*<<< orphan*/  origin; int /*<<< orphan*/  entitynum; } ;
typedef  TYPE_1__ bot_goal_t ;
struct TYPE_7__ {int areanum; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  TYPE_2__ aas_reachability_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_ReachabilityFromNum (int,TYPE_2__*) ; 
 int BotGetReachabilityToGoal (int /*<<< orphan*/ ,int,int,int,int*,float*,int*,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BotVisible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Memset (int*,int /*<<< orphan*/ ,int) ; 
 int MAX_AVOIDREACH ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int qtrue ; 

int BotPredictVisiblePosition(vec3_t origin, int areanum, bot_goal_t *goal, int travelflags, vec3_t target)
{
	aas_reachability_t reach;
	int reachnum, lastgoalareanum, lastareanum, i;
	int avoidreach[MAX_AVOIDREACH];
	float avoidreachtimes[MAX_AVOIDREACH];
	int avoidreachtries[MAX_AVOIDREACH];
	vec3_t end;

	//if the bot has no goal or no last reachability
	if (!goal) return qfalse;
	//if the areanum is not valid
	if (!areanum) return qfalse;
	//if the goal areanum is not valid
	if (!goal->areanum) return qfalse;

	Com_Memset(avoidreach, 0, MAX_AVOIDREACH * sizeof(int));
	lastgoalareanum = goal->areanum;
	lastareanum = areanum;
	VectorCopy(origin, end);
	//only do 20 hops
	for (i = 0; i < 20 && (areanum != goal->areanum); i++)
	{
		//
		reachnum = BotGetReachabilityToGoal(end, areanum,
						lastgoalareanum, lastareanum,
							avoidreach, avoidreachtimes, avoidreachtries,
									goal, travelflags, NULL, 0, NULL);
		if (!reachnum) return qfalse;
		AAS_ReachabilityFromNum(reachnum, &reach);
		//
		if (BotVisible(goal->entitynum, goal->origin, reach.start))
		{
			VectorCopy(reach.start, target);
			return qtrue;
		} //end if
		//
		if (BotVisible(goal->entitynum, goal->origin, reach.end))
		{
			VectorCopy(reach.end, target);
			return qtrue;
		} //end if
		//
		if (reach.areanum == goal->areanum)
		{
			VectorCopy(reach.end, target);
			return qtrue;
		} //end if
		//
		lastareanum = areanum;
		areanum = reach.areanum;
		VectorCopy(reach.end, end);
		//
	} //end while
	//
	return qfalse;
}