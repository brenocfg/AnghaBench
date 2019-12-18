#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int lastair_time; int /*<<< orphan*/  gs; int /*<<< orphan*/  inventory; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_11__ {int /*<<< orphan*/  origin; } ;
typedef  TYPE_2__ bot_goal_t ;

/* Variables and functions */
 scalar_t__ BotGetAirGoal (TYPE_1__*,TYPE_2__*) ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_WATER ; 
 int FloatTime () ; 
 int qfalse ; 
 int qtrue ; 
 int trap_AAS_PointContents (int /*<<< orphan*/ ) ; 
 scalar_t__ trap_BotChooseNBGItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*,float) ; 
 int /*<<< orphan*/  trap_BotGetTopGoal (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  trap_BotPopGoal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotPushGoal (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  trap_BotResetAvoidGoals (int /*<<< orphan*/ ) ; 

int BotGoForAir(bot_state_t *bs, int tfl, bot_goal_t *ltg, float range) {
	bot_goal_t goal;

	//if the bot needs air
	if (bs->lastair_time < FloatTime() - 6) {
		//
#ifdef DEBUG
		//BotAI_Print(PRT_MESSAGE, "going for air\n");
#endif //DEBUG
		//if we can find an air goal
		if (BotGetAirGoal(bs, &goal)) {
			trap_BotPushGoal(bs->gs, &goal);
			return qtrue;
		}
		else {
			//get a nearby goal outside the water
			while(trap_BotChooseNBGItem(bs->gs, bs->origin, bs->inventory, tfl, ltg, range)) {
				trap_BotGetTopGoal(bs->gs, &goal);
				//if the goal is not in water
				if (!(trap_AAS_PointContents(goal.origin) & (CONTENTS_WATER|CONTENTS_SLIME|CONTENTS_LAVA))) {
					return qtrue;
				}
				trap_BotPopGoal(bs->gs);
			}
			trap_BotResetAvoidGoals(bs->gs);
		}
	}
	return qfalse;
}