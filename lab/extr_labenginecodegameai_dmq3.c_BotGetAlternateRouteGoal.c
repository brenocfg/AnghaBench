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
struct TYPE_8__ {scalar_t__ flags; scalar_t__ number; scalar_t__ iteminfo; scalar_t__ entitynum; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  origin; int /*<<< orphan*/  areanum; } ;
struct TYPE_7__ {scalar_t__ reachedaltroutegoal_time; TYPE_2__ altroutegoal; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  TYPE_2__ bot_goal_t ;
struct TYPE_9__ {int /*<<< orphan*/  origin; int /*<<< orphan*/  areanum; } ;
typedef  TYPE_3__ aas_altroutegoal_t ;

/* Variables and functions */
 int TEAM_RED ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_3__* blue_altroutegoals ; 
 int blue_numaltroutegoals ; 
 int qfalse ; 
 int qtrue ; 
 scalar_t__ random () ; 
 TYPE_3__* red_altroutegoals ; 
 int red_numaltroutegoals ; 

int BotGetAlternateRouteGoal(bot_state_t *bs, int base) {
	aas_altroutegoal_t *altroutegoals;
	bot_goal_t *goal;
	int numaltroutegoals, rnd;

	if (base == TEAM_RED) {
		altroutegoals = red_altroutegoals;
		numaltroutegoals = red_numaltroutegoals;
	}
	else {
		altroutegoals = blue_altroutegoals;
		numaltroutegoals = blue_numaltroutegoals;
	}
	if (!numaltroutegoals)
		return qfalse;
	rnd = (float) random() * numaltroutegoals;
	if (rnd >= numaltroutegoals)
		rnd = numaltroutegoals-1;
	goal = &bs->altroutegoal;
	goal->areanum = altroutegoals[rnd].areanum;
	VectorCopy(altroutegoals[rnd].origin, goal->origin);
	VectorSet(goal->mins, -8, -8, -8);
	VectorSet(goal->maxs, 8, 8, 8);
	goal->entitynum = 0;
	goal->iteminfo = 0;
	goal->number = 0;
	goal->flags = 0;
	//
	bs->reachedaltroutegoal_time = 0;
	return qtrue;
}