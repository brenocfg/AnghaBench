#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bot_state_t ;
struct TYPE_8__ {int /*<<< orphan*/  entitynum; } ;
struct TYPE_9__ {int inuse; int /*<<< orphan*/  origin; TYPE_1__ goal; void* start_time; void* time; } ;
typedef  TYPE_2__ bot_activategoal_t ;
struct TYPE_10__ {int /*<<< orphan*/  origin; } ;
typedef  TYPE_3__ aas_entityinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  AIEnter_Seek_ActivateEntity (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BotEnableActivateGoalAreas (TYPE_2__*,int) ; 
 int /*<<< orphan*/  BotEntityInfo (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ BotPushOntoActivateGoalStack (int /*<<< orphan*/ *,TYPE_2__*) ; 
 void* FloatTime () ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int qtrue ; 

int BotGoForActivateGoal(bot_state_t *bs, bot_activategoal_t *activategoal) {
	aas_entityinfo_t activateinfo;

	activategoal->inuse = qtrue;
	if (!activategoal->time)
		activategoal->time = FloatTime() + 10;
	activategoal->start_time = FloatTime();
	BotEntityInfo(activategoal->goal.entitynum, &activateinfo);
	VectorCopy(activateinfo.origin, activategoal->origin);
	//
	if (BotPushOntoActivateGoalStack(bs, activategoal)) {
		// enter the activate entity AI node
		AIEnter_Seek_ActivateEntity(bs, "BotGoForActivateGoal");
		return qtrue;
	}
	else {
		// enable any routing areas that were disabled
		BotEnableActivateGoalAreas(activategoal, qtrue);
		return qfalse;
	}
}