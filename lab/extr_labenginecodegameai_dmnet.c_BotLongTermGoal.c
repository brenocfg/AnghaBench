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
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  teammate ;
struct TYPE_10__ {int areanum; int /*<<< orphan*/  origin; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  entitynum; } ;
struct TYPE_8__ {scalar_t__ lead_time; int leadmessage_time; int leadvisible_time; int leadbackup_time; double* ideal_viewangles; int /*<<< orphan*/  origin; int /*<<< orphan*/  teammate; int /*<<< orphan*/  cs; int /*<<< orphan*/  lead_teammate; TYPE_3__ lead_teamgoal; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  eye; int /*<<< orphan*/  entitynum; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  int /*<<< orphan*/  bot_goal_t ;
struct TYPE_9__ {int /*<<< orphan*/  origin; scalar_t__ valid; } ;
typedef  TYPE_2__ aas_entityinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotEntityInfo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ BotEntityVisible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int BotGetLongTermGoal (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int BotPointAreaNum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHAT_TELL ; 
 int /*<<< orphan*/  EasyClientName (int /*<<< orphan*/ ,char*,int) ; 
 int FloatTime () ; 
 int MAX_MESSAGE_SIZE ; 
 float Square (int) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLengthSquared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int qfalse ; 
 int qtrue ; 
 scalar_t__ trap_AAS_AreaReachability (int) ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vectoangles (int /*<<< orphan*/ ,double*) ; 

int BotLongTermGoal(bot_state_t *bs, int tfl, int retreat, bot_goal_t *goal) {
	aas_entityinfo_t entinfo;
	char teammate[MAX_MESSAGE_SIZE];
	float squaredist;
	int areanum;
	vec3_t dir;

	//FIXME: also have air long term goals?
	//
	//if the bot is leading someone and not retreating
	if (bs->lead_time > 0 && !retreat) {
		if (bs->lead_time < FloatTime()) {
			BotAI_BotInitialChat(bs, "lead_stop", EasyClientName(bs->lead_teammate, teammate, sizeof(teammate)), NULL);
			trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
			bs->lead_time = 0;
			return BotGetLongTermGoal(bs, tfl, retreat, goal);
		}
		//
		if (bs->leadmessage_time < 0 && -bs->leadmessage_time < FloatTime()) {
			BotAI_BotInitialChat(bs, "followme", EasyClientName(bs->lead_teammate, teammate, sizeof(teammate)), NULL);
			trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
			bs->leadmessage_time = FloatTime();
		}
		//get entity information of the companion
		BotEntityInfo(bs->lead_teammate, &entinfo);
		//
		if (entinfo.valid) {
			areanum = BotPointAreaNum(entinfo.origin);
			if (areanum && trap_AAS_AreaReachability(areanum)) {
				//update team goal
				bs->lead_teamgoal.entitynum = bs->lead_teammate;
				bs->lead_teamgoal.areanum = areanum;
				VectorCopy(entinfo.origin, bs->lead_teamgoal.origin);
				VectorSet(bs->lead_teamgoal.mins, -8, -8, -8);
				VectorSet(bs->lead_teamgoal.maxs, 8, 8, 8);
			}
		}
		//if the team mate is visible
		if (BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->lead_teammate)) {
			bs->leadvisible_time = FloatTime();
		}
		//if the team mate is not visible for 1 seconds
		if (bs->leadvisible_time < FloatTime() - 1) {
			bs->leadbackup_time = FloatTime() + 2;
		}
		//distance towards the team mate
		VectorSubtract(bs->origin, bs->lead_teamgoal.origin, dir);
		squaredist = VectorLengthSquared(dir);
		//if backing up towards the team mate
		if (bs->leadbackup_time > FloatTime()) {
			if (bs->leadmessage_time < FloatTime() - 20) {
				BotAI_BotInitialChat(bs, "followme", EasyClientName(bs->lead_teammate, teammate, sizeof(teammate)), NULL);
				trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
				bs->leadmessage_time = FloatTime();
			}
			//if very close to the team mate
			if (squaredist < Square(100)) {
				bs->leadbackup_time = 0;
			}
			//the bot should go back to the team mate
			memcpy(goal, &bs->lead_teamgoal, sizeof(bot_goal_t));
			return qtrue;
		}
		else {
			//if quite distant from the team mate
			if (squaredist > Square(500)) {
				if (bs->leadmessage_time < FloatTime() - 20) {
					BotAI_BotInitialChat(bs, "followme", EasyClientName(bs->lead_teammate, teammate, sizeof(teammate)), NULL);
					trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
					bs->leadmessage_time = FloatTime();
				}
				//look at the team mate
				VectorSubtract(entinfo.origin, bs->origin, dir);
				vectoangles(dir, bs->ideal_viewangles);
				bs->ideal_viewangles[2] *= 0.5;
				//just wait for the team mate
				return qfalse;
			}
		}
	}
	return BotGetLongTermGoal(bs, tfl, retreat, goal);
}