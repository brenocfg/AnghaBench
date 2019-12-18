#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int goalstacktop; int /*<<< orphan*/ * goalstack; } ;
typedef  TYPE_1__ bot_goalstate_t ;
typedef  int /*<<< orphan*/  bot_goal_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BotDumpGoalStack (int) ; 
 TYPE_1__* BotGoalStateFromHandle (int) ; 
 int /*<<< orphan*/  Com_Memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int MAX_GOALSTACK ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_2__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void BotPushGoal(int goalstate, bot_goal_t *goal)
{
	bot_goalstate_t *gs;

	gs = BotGoalStateFromHandle(goalstate);
	if (!gs) return;
	if (gs->goalstacktop >= MAX_GOALSTACK-1)
	{
		botimport.Print(PRT_ERROR, "goal heap overflow\n");
		BotDumpGoalStack(goalstate);
		return;
	} //end if
	gs->goalstacktop++;
	Com_Memcpy(&gs->goalstack[gs->goalstacktop], goal, sizeof(bot_goal_t));
}