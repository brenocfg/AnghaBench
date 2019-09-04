#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
typedef  int /*<<< orphan*/  netname ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_26__ {char* name; struct TYPE_26__* next; } ;
typedef  TYPE_2__ bot_waypoint_t ;
struct TYPE_30__ {int entitynum; int areanum; int /*<<< orphan*/  number; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  origin; } ;
struct TYPE_27__ {scalar_t__ ltgtype; int teammessage_time; int teammate; int decisionmaker; int teamgoal_time; int teammatevisible_time; int entitynum; scalar_t__* origin; int formation_dist; int attackcrouch_time; float thinktime; int arrive_time; double* ideal_viewangles; int nbg_time; int defendaway_range; int defendaway_time; scalar_t__ killedenemy_time; scalar_t__ lastkilledplayer; scalar_t__ lastgoal_ltgtype; int patrolflags; TYPE_1__* curpatrolpoint; int /*<<< orphan*/  cs; int /*<<< orphan*/  client; TYPE_2__* patrolpoints; int /*<<< orphan*/  ms; int /*<<< orphan*/  eye; int /*<<< orphan*/  character; TYPE_6__ teamgoal; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  areanum; int /*<<< orphan*/  tfl; } ;
typedef  TYPE_3__ bot_state_t ;
struct TYPE_28__ {int* origin; } ;
typedef  TYPE_4__ bot_goal_t ;
struct TYPE_29__ {int* origin; int* maxs; int* mins; scalar_t__ valid; int /*<<< orphan*/  angles; } ;
typedef  TYPE_5__ aas_entityinfo_t ;
struct TYPE_25__ {TYPE_6__ goal; struct TYPE_25__* prev; struct TYPE_25__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_AFFIRMATIVE ; 
 int /*<<< orphan*/  AIEnter_Seek_NBG (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  AngleVectors (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_3__*,char*,char*,...) ; 
 int /*<<< orphan*/  BotEntityInfo (int,TYPE_5__*) ; 
 scalar_t__ BotEntityVisible (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int BotGetItemLongTermGoal (TYPE_3__*,int,TYPE_4__*) ; 
 scalar_t__ BotGoForAir (TYPE_3__*,int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 scalar_t__ BotHasPersistantPowerupAndWeapon (TYPE_3__*) ; 
 int BotPointAreaNum (int*) ; 
 scalar_t__ BotReachedGoal (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  BotRoamGoal (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  BotSetupForMovement (TYPE_3__*) ; 
 int /*<<< orphan*/  BotVoiceChatOnly (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHARACTERISTIC_CROUCHER ; 
 int /*<<< orphan*/  CHAT_TEAM ; 
 int /*<<< orphan*/  CHAT_TELL ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_WATER ; 
 double DotProduct (int*,int*) ; 
 int /*<<< orphan*/  EasyClientName (int,char*,int) ; 
 int FloatTime () ; 
 scalar_t__ LTG_CAMP ; 
 scalar_t__ LTG_CAMPORDER ; 
 scalar_t__ LTG_DEFENDKEYAREA ; 
 scalar_t__ LTG_GETITEM ; 
 scalar_t__ LTG_KILL ; 
 scalar_t__ LTG_PATROL ; 
 scalar_t__ LTG_TEAMACCOMPANY ; 
 scalar_t__ LTG_TEAMHELP ; 
 int MAX_MESSAGE_SIZE ; 
 int MAX_NETNAME ; 
 int /*<<< orphan*/  MOVE_WALK ; 
 int PATROL_BACK ; 
 scalar_t__ Square (int) ; 
 scalar_t__ TEAM_KILL_SOMEONE ; 
 int /*<<< orphan*/  TFL_DEFAULT ; 
 int /*<<< orphan*/  VOICECHAT_INPOSITION ; 
 int /*<<< orphan*/  VOICECHAT_ONDEFENSE ; 
 int /*<<< orphan*/  VOICECHAT_YES ; 
 int /*<<< orphan*/  VectorCopy (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ VectorLengthSquared (int*) ; 
 int /*<<< orphan*/  VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  VectorSubtract (int*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_6__*,int) ; 
 int qfalse ; 
 int qtrue ; 
 float random () ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ trap_AAS_AreaReachability (int) ; 
 int trap_AAS_AreaTravelTimeToGoalArea (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ trap_AAS_Swimming (int*) ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotGoalName (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ trap_BotItemGoalInVisButNotVisible (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  trap_BotMoveInDirection (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotResetAvoidReach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotResetLastAvoidReach (int /*<<< orphan*/ ) ; 
 scalar_t__ trap_BotTouchingGoal (int*,TYPE_6__*) ; 
 float trap_Characteristic_BFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_EA_Action (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_EA_Crouch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_EA_Gesture (int /*<<< orphan*/ ) ; 
 int trap_PointContents (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vectoangles (int*,double*) ; 

int BotGetLongTermGoal(bot_state_t *bs, int tfl, int retreat, bot_goal_t *goal) {
	vec3_t target, dir, dir2;
	char netname[MAX_NETNAME];
	char buf[MAX_MESSAGE_SIZE];
	int areanum;
	float croucher;
	aas_entityinfo_t entinfo, botinfo;
	bot_waypoint_t *wp;

	if (bs->ltgtype == LTG_TEAMHELP && !retreat) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			BotAI_BotInitialChat(bs, "help_start", EasyClientName(bs->teammate, netname, sizeof(netname)), NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			BotVoiceChatOnly(bs, bs->decisionmaker, VOICECHAT_YES);
			trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
			bs->teammessage_time = 0;
		}
		//if trying to help the team mate for more than a minute
		if (bs->teamgoal_time < FloatTime())
			bs->ltgtype = 0;
		//if the team mate IS visible for quite some time
		if (bs->teammatevisible_time < FloatTime() - 10) bs->ltgtype = 0;
		//get entity information of the companion
		BotEntityInfo(bs->teammate, &entinfo);
		//if the team mate is visible
		if (BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->teammate)) {
			//if close just stand still there
			VectorSubtract(entinfo.origin, bs->origin, dir);
			if (VectorLengthSquared(dir) < Square(100)) {
				trap_BotResetAvoidReach(bs->ms);
				return qfalse;
			}
		}
		else {
			//last time the bot was NOT visible
			bs->teammatevisible_time = FloatTime();
		}
		//if the entity information is valid (entity in PVS)
		if (entinfo.valid) {
			areanum = BotPointAreaNum(entinfo.origin);
			if (areanum && trap_AAS_AreaReachability(areanum)) {
				//update team goal
				bs->teamgoal.entitynum = bs->teammate;
				bs->teamgoal.areanum = areanum;
				VectorCopy(entinfo.origin, bs->teamgoal.origin);
				VectorSet(bs->teamgoal.mins, -8, -8, -8);
				VectorSet(bs->teamgoal.maxs, 8, 8, 8);
			}
		}
		memcpy(goal, &bs->teamgoal, sizeof(bot_goal_t));
		return qtrue;
	}
	//if the bot accompanies someone
	if (bs->ltgtype == LTG_TEAMACCOMPANY && !retreat) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			BotAI_BotInitialChat(bs, "accompany_start", EasyClientName(bs->teammate, netname, sizeof(netname)), NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			BotVoiceChatOnly(bs, bs->decisionmaker, VOICECHAT_YES);
			trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
			bs->teammessage_time = 0;
		}
		//if accompanying the companion for 3 minutes
		if (bs->teamgoal_time < FloatTime()) {
			BotAI_BotInitialChat(bs, "accompany_stop", EasyClientName(bs->teammate, netname, sizeof(netname)), NULL);
			trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
			bs->ltgtype = 0;
		}
		//get entity information of the companion
		BotEntityInfo(bs->teammate, &entinfo);
		//if the companion is visible
		if (BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->teammate)) {
			//update visible time
			bs->teammatevisible_time = FloatTime();
			VectorSubtract(entinfo.origin, bs->origin, dir);
			if (VectorLengthSquared(dir) < Square(bs->formation_dist)) {
				//
				// if the client being followed bumps into this bot then
				// the bot should back up
				BotEntityInfo(bs->entitynum, &botinfo);
				// if the followed client is not standing ontop of the bot
				if (botinfo.origin[2] + botinfo.maxs[2] > entinfo.origin[2] + entinfo.mins[2]) {
					// if the bounding boxes touch each other
					if (botinfo.origin[0] + botinfo.maxs[0] > entinfo.origin[0] + entinfo.mins[0] - 4&&
						botinfo.origin[0] + botinfo.mins[0] < entinfo.origin[0] + entinfo.maxs[0] + 4) {
						if (botinfo.origin[1] + botinfo.maxs[1] > entinfo.origin[1] + entinfo.mins[1] - 4 &&
							botinfo.origin[1] + botinfo.mins[1] < entinfo.origin[1] + entinfo.maxs[1] + 4) {
							if (botinfo.origin[2] + botinfo.maxs[2] > entinfo.origin[2] + entinfo.mins[2] - 4 &&
								botinfo.origin[2] + botinfo.mins[2] < entinfo.origin[2] + entinfo.maxs[2] + 4) {
								// if the followed client looks in the direction of this bot
								AngleVectors(entinfo.angles, dir, NULL, NULL);
								dir[2] = 0;
								VectorNormalize(dir);
								//VectorSubtract(entinfo.origin, entinfo.lastvisorigin, dir);
								VectorSubtract(bs->origin, entinfo.origin, dir2);
								VectorNormalize(dir2);
								if (DotProduct(dir, dir2) > 0.7) {
									// back up
									BotSetupForMovement(bs);
									trap_BotMoveInDirection(bs->ms, dir2, 400, MOVE_WALK);
								}
							}
						}
					}
				}
				//check if the bot wants to crouch
				//don't crouch if crouched less than 5 seconds ago
				if (bs->attackcrouch_time < FloatTime() - 5) {
					croucher = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CROUCHER, 0, 1);
					if (random() < bs->thinktime * croucher) {
						bs->attackcrouch_time = FloatTime() + 5 + croucher * 15;
					}
				}
				//don't crouch when swimming
				if (trap_AAS_Swimming(bs->origin)) bs->attackcrouch_time = FloatTime() - 1;
				//if not arrived yet or arived some time ago
				if (bs->arrive_time < FloatTime() - 2) {
					//if not arrived yet
					if (!bs->arrive_time) {
						trap_EA_Gesture(bs->client);
						BotAI_BotInitialChat(bs, "accompany_arrive", EasyClientName(bs->teammate, netname, sizeof(netname)), NULL);
						trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
						bs->arrive_time = FloatTime();
					}
					//if the bot wants to crouch
					else if (bs->attackcrouch_time > FloatTime()) {
						trap_EA_Crouch(bs->client);
					}
					//else do some model taunts
					else if (random() < bs->thinktime * 0.05) {
						//do a gesture :)
						trap_EA_Gesture(bs->client);
					}
				}
				//if just arrived look at the companion
				if (bs->arrive_time > FloatTime() - 2) {
					VectorSubtract(entinfo.origin, bs->origin, dir);
					vectoangles(dir, bs->ideal_viewangles);
					bs->ideal_viewangles[2] *= 0.5;
				}
				//else look strategically around for enemies
				else if (random() < bs->thinktime * 0.8) {
					BotRoamGoal(bs, target);
					VectorSubtract(target, bs->origin, dir);
					vectoangles(dir, bs->ideal_viewangles);
					bs->ideal_viewangles[2] *= 0.5;
				}
				//check if the bot wants to go for air
				if (BotGoForAir(bs, bs->tfl, &bs->teamgoal, 400)) {
					trap_BotResetLastAvoidReach(bs->ms);
					//get the goal at the top of the stack
					//trap_BotGetTopGoal(bs->gs, &tmpgoal);
					//trap_BotGoalName(tmpgoal.number, buf, 144);
					//BotAI_Print(PRT_MESSAGE, "new nearby goal %s\n", buf);
					//time the bot gets to pick up the nearby goal item
					bs->nbg_time = FloatTime() + 8;
					AIEnter_Seek_NBG(bs, "BotLongTermGoal: go for air");
					return qfalse;
				}
				//
				trap_BotResetAvoidReach(bs->ms);
				return qfalse;
			}
		}
		//if the entity information is valid (entity in PVS)
		if (entinfo.valid) {
			areanum = BotPointAreaNum(entinfo.origin);
			if (areanum && trap_AAS_AreaReachability(areanum)) {
				//update team goal
				bs->teamgoal.entitynum = bs->teammate;
				bs->teamgoal.areanum = areanum;
				VectorCopy(entinfo.origin, bs->teamgoal.origin);
				VectorSet(bs->teamgoal.mins, -8, -8, -8);
				VectorSet(bs->teamgoal.maxs, 8, 8, 8);
			}
		}
		//the goal the bot should go for
		memcpy(goal, &bs->teamgoal, sizeof(bot_goal_t));
		//if the companion is NOT visible for too long
		if (bs->teammatevisible_time < FloatTime() - 60) {
			BotAI_BotInitialChat(bs, "accompany_cannotfind", EasyClientName(bs->teammate, netname, sizeof(netname)), NULL);
			trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
			bs->ltgtype = 0;
			// just to make sure the bot won't spam this message
			bs->teammatevisible_time = FloatTime();
		}
		return qtrue;
	}
	//
	if (bs->ltgtype == LTG_DEFENDKEYAREA) {
		if (trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin,
				bs->teamgoal.areanum, TFL_DEFAULT) > bs->defendaway_range) {
			bs->defendaway_time = 0;
		}
	}
	//if defending a key area
	if (bs->ltgtype == LTG_DEFENDKEYAREA && !retreat &&
				bs->defendaway_time < FloatTime()) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			trap_BotGoalName(bs->teamgoal.number, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "defend_start", buf, NULL);
			trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
			BotVoiceChatOnly(bs, -1, VOICECHAT_ONDEFENSE);
			bs->teammessage_time = 0;
		}
		//set the bot goal
		memcpy(goal, &bs->teamgoal, sizeof(bot_goal_t));
		//stop after 2 minutes
		if (bs->teamgoal_time < FloatTime()) {
			trap_BotGoalName(bs->teamgoal.number, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "defend_stop", buf, NULL);
			trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
			bs->ltgtype = 0;
		}
		//if very close... go away for some time
		VectorSubtract(goal->origin, bs->origin, dir);
		if (VectorLengthSquared(dir) < Square(70)) {
			trap_BotResetAvoidReach(bs->ms);
			bs->defendaway_time = FloatTime() + 3 + 3 * random();
			if (BotHasPersistantPowerupAndWeapon(bs)) {
				bs->defendaway_range = 100;
			}
			else {
				bs->defendaway_range = 350;
			}
		}
		return qtrue;
	}
	//going to kill someone
	if (bs->ltgtype == LTG_KILL && !retreat) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			EasyClientName(bs->teamgoal.entitynum, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "kill_start", buf, NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			bs->teammessage_time = 0;
		}
		//
		if (bs->killedenemy_time > bs->teamgoal_time - TEAM_KILL_SOMEONE && bs->lastkilledplayer == bs->teamgoal.entitynum) {
			EasyClientName(bs->teamgoal.entitynum, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "kill_done", buf, NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			bs->ltgtype = 0;
		}
		//
		if (bs->teamgoal_time < FloatTime()) {
			bs->ltgtype = 0;
		}
		//just roam around
		return BotGetItemLongTermGoal(bs, tfl, goal);
	}
	//get an item
	if (bs->ltgtype == LTG_GETITEM && !retreat) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			trap_BotGoalName(bs->teamgoal.number, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "getitem_start", buf, NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			BotVoiceChatOnly(bs, bs->decisionmaker, VOICECHAT_YES);
			trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
			bs->teammessage_time = 0;
		}
		//set the bot goal
		memcpy(goal, &bs->teamgoal, sizeof(bot_goal_t));
		//stop after some time
		if (bs->teamgoal_time < FloatTime()) {
			bs->ltgtype = 0;
		}
		//
		if (trap_BotItemGoalInVisButNotVisible(bs->entitynum, bs->eye, bs->viewangles, goal)) {
			trap_BotGoalName(bs->teamgoal.number, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "getitem_notthere", buf, NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			bs->ltgtype = 0;
		}
		else if (BotReachedGoal(bs, goal)) {
			trap_BotGoalName(bs->teamgoal.number, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "getitem_gotit", buf, NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			bs->ltgtype = 0;
		}
		return qtrue;
	}
	//if camping somewhere
	if ((bs->ltgtype == LTG_CAMP || bs->ltgtype == LTG_CAMPORDER) && !retreat) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			if (bs->ltgtype == LTG_CAMPORDER) {
				BotAI_BotInitialChat(bs, "camp_start", EasyClientName(bs->teammate, netname, sizeof(netname)), NULL);
				trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
				BotVoiceChatOnly(bs, bs->decisionmaker, VOICECHAT_YES);
				trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
			}
			bs->teammessage_time = 0;
		}
		//set the bot goal
		memcpy(goal, &bs->teamgoal, sizeof(bot_goal_t));
		//
		if (bs->teamgoal_time < FloatTime()) {
			if (bs->ltgtype == LTG_CAMPORDER) {
				BotAI_BotInitialChat(bs, "camp_stop", NULL);
				trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			}
			bs->ltgtype = 0;
		}
		//if really near the camp spot
		VectorSubtract(goal->origin, bs->origin, dir);
		if (VectorLengthSquared(dir) < Square(60))
		{
			//if not arrived yet
			if (!bs->arrive_time) {
				if (bs->ltgtype == LTG_CAMPORDER) {
					BotAI_BotInitialChat(bs, "camp_arrive", EasyClientName(bs->teammate, netname, sizeof(netname)), NULL);
					trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
					BotVoiceChatOnly(bs, bs->decisionmaker, VOICECHAT_INPOSITION);
				}
				bs->arrive_time = FloatTime();
			}
			//look strategically around for enemies
			if (random() < bs->thinktime * 0.8) {
				BotRoamGoal(bs, target);
				VectorSubtract(target, bs->origin, dir);
				vectoangles(dir, bs->ideal_viewangles);
				bs->ideal_viewangles[2] *= 0.5;
			}
			//check if the bot wants to crouch
			//don't crouch if crouched less than 5 seconds ago
			if (bs->attackcrouch_time < FloatTime() - 5) {
				croucher = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CROUCHER, 0, 1);
				if (random() < bs->thinktime * croucher) {
					bs->attackcrouch_time = FloatTime() + 5 + croucher * 15;
				}
			}
			//if the bot wants to crouch
			if (bs->attackcrouch_time > FloatTime()) {
				trap_EA_Crouch(bs->client);
			}
			//don't crouch when swimming
			if (trap_AAS_Swimming(bs->origin)) bs->attackcrouch_time = FloatTime() - 1;
			//make sure the bot is not gonna drown
			if (trap_PointContents(bs->eye,bs->entitynum) & (CONTENTS_WATER|CONTENTS_SLIME|CONTENTS_LAVA)) {
				if (bs->ltgtype == LTG_CAMPORDER) {
					BotAI_BotInitialChat(bs, "camp_stop", NULL);
					trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
					//
					if (bs->lastgoal_ltgtype == LTG_CAMPORDER) {
						bs->lastgoal_ltgtype = 0;
					}
				}
				bs->ltgtype = 0;
			}
			//
			//FIXME: move around a bit
			//
			trap_BotResetAvoidReach(bs->ms);
			return qfalse;
		}
		return qtrue;
	}
	//patrolling along several waypoints
	if (bs->ltgtype == LTG_PATROL && !retreat) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			strcpy(buf, "");
			for (wp = bs->patrolpoints; wp; wp = wp->next) {
				strcat(buf, wp->name);
				if (wp->next) strcat(buf, " to ");
			}
			BotAI_BotInitialChat(bs, "patrol_start", buf, NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			BotVoiceChatOnly(bs, bs->decisionmaker, VOICECHAT_YES);
			trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
			bs->teammessage_time = 0;
		}
		//
		if (!bs->curpatrolpoint) {
			bs->ltgtype = 0;
			return qfalse;
		}
		//if the bot touches the current goal
		if (trap_BotTouchingGoal(bs->origin, &bs->curpatrolpoint->goal)) {
			if (bs->patrolflags & PATROL_BACK) {
				if (bs->curpatrolpoint->prev) {
					bs->curpatrolpoint = bs->curpatrolpoint->prev;
				}
				else {
					bs->curpatrolpoint = bs->curpatrolpoint->next;
					bs->patrolflags &= ~PATROL_BACK;
				}
			}
			else {
				if (bs->curpatrolpoint->next) {
					bs->curpatrolpoint = bs->curpatrolpoint->next;
				}
				else {
					bs->curpatrolpoint = bs->curpatrolpoint->prev;
					bs->patrolflags |= PATROL_BACK;
				}
			}
		}
		//stop after 5 minutes
		if (bs->teamgoal_time < FloatTime()) {
			BotAI_BotInitialChat(bs, "patrol_stop", NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			bs->ltgtype = 0;
		}
		if (!bs->curpatrolpoint) {
			bs->ltgtype = 0;
			return qfalse;
		}
		memcpy(goal, &bs->curpatrolpoint->goal, sizeof(bot_goal_t));
		return qtrue;
	}
#ifdef CTF
	if (gametype == GT_CTF) {
		//if going for enemy flag
		if (bs->ltgtype == LTG_GETFLAG) {
			//check for bot typing status message
			if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
				BotAI_BotInitialChat(bs, "captureflag_start", NULL);
				trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
				BotVoiceChatOnly(bs, -1, VOICECHAT_ONGETFLAG);
				bs->teammessage_time = 0;
			}
			//
			switch(BotTeam(bs)) {
				case TEAM_RED: memcpy(goal, &ctf_blueflag, sizeof(bot_goal_t)); break;
				case TEAM_BLUE: memcpy(goal, &ctf_redflag, sizeof(bot_goal_t)); break;
				default: bs->ltgtype = 0; return qfalse;
			}
			//if touching the flag
			if (trap_BotTouchingGoal(bs->origin, goal)) {
				// make sure the bot knows the flag isn't there anymore
				switch(BotTeam(bs)) {
					case TEAM_RED: bs->blueflagstatus = 1; break;
					case TEAM_BLUE: bs->redflagstatus = 1; break;
				}
				bs->ltgtype = 0;
			}
			//stop after 3 minutes
			if (bs->teamgoal_time < FloatTime()) {
				bs->ltgtype = 0;
			}
			BotAlternateRoute(bs, goal);
			return qtrue;
		}
		//if rushing to the base
		if (bs->ltgtype == LTG_RUSHBASE && bs->rushbaseaway_time < FloatTime()) {
			switch(BotTeam(bs)) {
				case TEAM_RED: memcpy(goal, &ctf_redflag, sizeof(bot_goal_t)); break;
				case TEAM_BLUE: memcpy(goal, &ctf_blueflag, sizeof(bot_goal_t)); break;
				default: bs->ltgtype = 0; return qfalse;
			}
			//if not carrying the flag anymore
			if (!BotCTFCarryingFlag(bs)) bs->ltgtype = 0;
			//quit rushing after 2 minutes
			if (bs->teamgoal_time < FloatTime()) bs->ltgtype = 0;
			//if touching the base flag the bot should loose the enemy flag
			if (trap_BotTouchingGoal(bs->origin, goal)) {
				//if the bot is still carrying the enemy flag then the
				//base flag is gone, now just walk near the base a bit
				if (BotCTFCarryingFlag(bs)) {
					trap_BotResetAvoidReach(bs->ms);
					bs->rushbaseaway_time = FloatTime() + 5 + 10 * random();
					//FIXME: add chat to tell the others to get back the flag
				}
				else {
					bs->ltgtype = 0;
				}
			}
			BotAlternateRoute(bs, goal);
			return qtrue;
		}
		//returning flag
		if (bs->ltgtype == LTG_RETURNFLAG) {
			//check for bot typing status message
			if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
				BotAI_BotInitialChat(bs, "returnflag_start", NULL);
				trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
				BotVoiceChatOnly(bs, -1, VOICECHAT_ONRETURNFLAG);
				bs->teammessage_time = 0;
			}
			//
			switch(BotTeam(bs)) {
				case TEAM_RED: memcpy(goal, &ctf_blueflag, sizeof(bot_goal_t)); break;
				case TEAM_BLUE: memcpy(goal, &ctf_redflag, sizeof(bot_goal_t)); break;
				default: bs->ltgtype = 0; return qfalse;
			}
			//if touching the flag
			if (trap_BotTouchingGoal(bs->origin, goal)) bs->ltgtype = 0;
			//stop after 3 minutes
			if (bs->teamgoal_time < FloatTime()) {
				bs->ltgtype = 0;
			}
			BotAlternateRoute(bs, goal);
			return qtrue;
		}
	}
#endif //CTF
#ifdef MISSIONPACK
	else if (gametype == GT_1FCTF) {
		if (bs->ltgtype == LTG_GETFLAG) {
			//check for bot typing status message
			if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
				BotAI_BotInitialChat(bs, "captureflag_start", NULL);
				trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
				BotVoiceChatOnly(bs, -1, VOICECHAT_ONGETFLAG);
				bs->teammessage_time = 0;
			}
			memcpy(goal, &ctf_neutralflag, sizeof(bot_goal_t));
			//if touching the flag
			if (trap_BotTouchingGoal(bs->origin, goal)) {
				bs->ltgtype = 0;
			}
			//stop after 3 minutes
			if (bs->teamgoal_time < FloatTime()) {
				bs->ltgtype = 0;
			}
			return qtrue;
		}
		//if rushing to the base
		if (bs->ltgtype == LTG_RUSHBASE) {
			switch(BotTeam(bs)) {
				case TEAM_RED: memcpy(goal, &ctf_blueflag, sizeof(bot_goal_t)); break;
				case TEAM_BLUE: memcpy(goal, &ctf_redflag, sizeof(bot_goal_t)); break;
				default: bs->ltgtype = 0; return qfalse;
			}
			//if not carrying the flag anymore
			if (!Bot1FCTFCarryingFlag(bs)) {
				bs->ltgtype = 0;
			}
			//quit rushing after 2 minutes
			if (bs->teamgoal_time < FloatTime()) {
				bs->ltgtype = 0;
			}
			//if touching the base flag the bot should loose the enemy flag
			if (trap_BotTouchingGoal(bs->origin, goal)) {
				bs->ltgtype = 0;
			}
			BotAlternateRoute(bs, goal);
			return qtrue;
		}
		//attack the enemy base
		if (bs->ltgtype == LTG_ATTACKENEMYBASE &&
				bs->attackaway_time < FloatTime()) {
			//check for bot typing status message
			if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
				BotAI_BotInitialChat(bs, "attackenemybase_start", NULL);
				trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
				BotVoiceChatOnly(bs, -1, VOICECHAT_ONOFFENSE);
				bs->teammessage_time = 0;
			}
			switch(BotTeam(bs)) {
				case TEAM_RED: memcpy(goal, &ctf_blueflag, sizeof(bot_goal_t)); break;
				case TEAM_BLUE: memcpy(goal, &ctf_redflag, sizeof(bot_goal_t)); break;
				default: bs->ltgtype = 0; return qfalse;
			}
			//quit rushing after 2 minutes
			if (bs->teamgoal_time < FloatTime()) {
				bs->ltgtype = 0;
			}
			//if touching the base flag the bot should loose the enemy flag
			if (trap_BotTouchingGoal(bs->origin, goal)) {
				bs->attackaway_time = FloatTime() + 2 + 5 * random();
			}
			return qtrue;
		}
		//returning flag
		if (bs->ltgtype == LTG_RETURNFLAG) {
			//check for bot typing status message
			if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
				BotAI_BotInitialChat(bs, "returnflag_start", NULL);
				trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
				BotVoiceChatOnly(bs, -1, VOICECHAT_ONRETURNFLAG);
				bs->teammessage_time = 0;
			}
			//
			if (bs->teamgoal_time < FloatTime()) {
				bs->ltgtype = 0;
			}
			//just roam around
			return BotGetItemLongTermGoal(bs, tfl, goal);
		}
	}
	else if (gametype == GT_OBELISK) {
		if (bs->ltgtype == LTG_ATTACKENEMYBASE &&
				bs->attackaway_time < FloatTime()) {

			//check for bot typing status message
			if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
				BotAI_BotInitialChat(bs, "attackenemybase_start", NULL);
				trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
				BotVoiceChatOnly(bs, -1, VOICECHAT_ONOFFENSE);
				bs->teammessage_time = 0;
			}
			switch(BotTeam(bs)) {
				case TEAM_RED: memcpy(goal, &blueobelisk, sizeof(bot_goal_t)); break;
				case TEAM_BLUE: memcpy(goal, &redobelisk, sizeof(bot_goal_t)); break;
				default: bs->ltgtype = 0; return qfalse;
			}
			//if the bot no longer wants to attack the obelisk
			if (BotFeelingBad(bs) > 50) {
				return BotGetItemLongTermGoal(bs, tfl, goal);
			}
			//if touching the obelisk
			if (trap_BotTouchingGoal(bs->origin, goal)) {
				bs->attackaway_time = FloatTime() + 3 + 5 * random();
			}
			// or very close to the obelisk
			VectorSubtract(bs->origin, goal->origin, dir);
			if (VectorLengthSquared(dir) < Square(60)) {
				bs->attackaway_time = FloatTime() + 3 + 5 * random();
			}
			//quit rushing after 2 minutes
			if (bs->teamgoal_time < FloatTime()) {
				bs->ltgtype = 0;
			}
			BotAlternateRoute(bs, goal);
			//just move towards the obelisk
			return qtrue;
		}
	}
	else if (gametype == GT_HARVESTER) {
		//if rushing to the base
		if (bs->ltgtype == LTG_RUSHBASE) {
			switch(BotTeam(bs)) {
				case TEAM_RED: memcpy(goal, &blueobelisk, sizeof(bot_goal_t)); break;
				case TEAM_BLUE: memcpy(goal, &redobelisk, sizeof(bot_goal_t)); break;
				default: BotGoHarvest(bs); return qfalse;
			}
			//if not carrying any cubes
			if (!BotHarvesterCarryingCubes(bs)) {
				BotGoHarvest(bs);
				return qfalse;
			}
			//quit rushing after 2 minutes
			if (bs->teamgoal_time < FloatTime()) {
				BotGoHarvest(bs);
				return qfalse;
			}
			//if touching the base flag the bot should loose the enemy flag
			if (trap_BotTouchingGoal(bs->origin, goal)) {
				BotGoHarvest(bs);
				return qfalse;
			}
			BotAlternateRoute(bs, goal);
			return qtrue;
		}
		//attack the enemy base
		if (bs->ltgtype == LTG_ATTACKENEMYBASE &&
				bs->attackaway_time < FloatTime()) {
			//check for bot typing status message
			if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
				BotAI_BotInitialChat(bs, "attackenemybase_start", NULL);
				trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
				BotVoiceChatOnly(bs, -1, VOICECHAT_ONOFFENSE);
				bs->teammessage_time = 0;
			}
			switch(BotTeam(bs)) {
				case TEAM_RED: memcpy(goal, &blueobelisk, sizeof(bot_goal_t)); break;
				case TEAM_BLUE: memcpy(goal, &redobelisk, sizeof(bot_goal_t)); break;
				default: bs->ltgtype = 0; return qfalse;
			}
			//quit rushing after 2 minutes
			if (bs->teamgoal_time < FloatTime()) {
				bs->ltgtype = 0;
			}
			//if touching the base flag the bot should loose the enemy flag
			if (trap_BotTouchingGoal(bs->origin, goal)) {
				bs->attackaway_time = FloatTime() + 2 + 5 * random();
			}
			return qtrue;
		}
		//harvest cubes
		if (bs->ltgtype == LTG_HARVEST &&
			bs->harvestaway_time < FloatTime()) {
			//check for bot typing status message
			if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
				BotAI_BotInitialChat(bs, "harvest_start", NULL);
				trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
				BotVoiceChatOnly(bs, -1, VOICECHAT_ONOFFENSE);
				bs->teammessage_time = 0;
			}
			memcpy(goal, &neutralobelisk, sizeof(bot_goal_t));
			//
			if (bs->teamgoal_time < FloatTime()) {
				bs->ltgtype = 0;
			}
			//
			if (trap_BotTouchingGoal(bs->origin, goal)) {
				bs->harvestaway_time = FloatTime() + 4 + 3 * random();
			}
			return qtrue;
		}
	}
#endif
	//normal goal stuff
	return BotGetItemLongTermGoal(bs, tfl, goal);
}