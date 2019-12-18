#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ areanum; } ;
struct TYPE_8__ {TYPE_2__ altroutegoal; scalar_t__ reachedaltroutegoal_time; int /*<<< orphan*/  tfl; int /*<<< orphan*/  origin; int /*<<< orphan*/  areanum; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  TYPE_2__ bot_goal_t ;

/* Variables and functions */
 scalar_t__ FloatTime () ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int trap_AAS_AreaTravelTimeToGoalArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

bot_goal_t *BotAlternateRoute(bot_state_t *bs, bot_goal_t *goal) {
	int t;

	// if the bot has an alternative route goal
	if (bs->altroutegoal.areanum) {
		//
		if (bs->reachedaltroutegoal_time)
			return goal;
		// travel time towards alternative route goal
		t = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin, bs->altroutegoal.areanum, bs->tfl);
		if (t && t < 20) {
			//BotAI_Print(PRT_MESSAGE, "reached alternate route goal\n");
			bs->reachedaltroutegoal_time = FloatTime();
		}
		memcpy(goal, &bs->altroutegoal, sizeof(bot_goal_t));
		return &bs->altroutegoal;
	}
	return goal;
}