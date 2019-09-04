#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int member_0; int member_1; int member_2; } ;
typedef  TYPE_1__ vec3_t ;
struct TYPE_8__ {TYPE_1__ origin; int /*<<< orphan*/  areanum; struct TYPE_8__* next; } ;
typedef  TYPE_2__ campspot_t ;
struct TYPE_9__ {scalar_t__ iteminfo; scalar_t__ flags; scalar_t__ number; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; scalar_t__ entitynum; int /*<<< orphan*/  origin; int /*<<< orphan*/  areanum; } ;
typedef  TYPE_3__ bot_goal_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorCopy (TYPE_1__,int /*<<< orphan*/ ) ; 
 TYPE_2__* campspots ; 

int BotGetNextCampSpotGoal(int num, bot_goal_t *goal)
{
	int i;
	campspot_t *cs;
	vec3_t mins = {-8, -8, -8}, maxs = {8, 8, 8};

	if (num < 0) num = 0;
	i = num;
	for (cs = campspots; cs; cs = cs->next)
	{
		if (--i < 0)
		{
			goal->areanum = cs->areanum;
			VectorCopy(cs->origin, goal->origin);
			goal->entitynum = 0;
			VectorCopy(mins, goal->mins);
			VectorCopy(maxs, goal->maxs);
			goal->number = 0;
			goal->flags = 0;
			goal->iteminfo = 0;
			return num+1;
		} //end if
	} //end for
	return 0;
}