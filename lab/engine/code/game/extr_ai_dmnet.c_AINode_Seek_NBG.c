#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_29__ {int tfl; int enemy; scalar_t__ nbg_time; double* ideal_viewangles; double thinktime; int flags; int /*<<< orphan*/  gs; int /*<<< orphan*/  ms; int /*<<< orphan*/  weaponnum; int /*<<< orphan*/  origin; scalar_t__ check_time; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_30__ {int flags; int /*<<< orphan*/  weapon; int /*<<< orphan*/  movedir; int /*<<< orphan*/  ideal_viewangles; scalar_t__ failure; } ;
typedef  TYPE_2__ bot_moveresult_t ;
typedef  int /*<<< orphan*/  bot_goal_t ;
struct TYPE_31__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIEnter_Battle_Fight (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Battle_NBG (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Intermission (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Observer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Respawn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Seek_LTG (TYPE_1__*,char*) ; 
 int BFL_IDEALVIEWSET ; 
 int /*<<< orphan*/  BotAIBlocked (TYPE_1__*,TYPE_2__*,int) ; 
 scalar_t__ BotAIPredictObstacles (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ BotCanAndWantsToRocketJump (TYPE_1__*) ; 
 int /*<<< orphan*/  BotChooseWeapon (TYPE_1__*) ; 
 int /*<<< orphan*/  BotClearPath (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ BotFindEnemy (TYPE_1__*,int) ; 
 scalar_t__ BotInLavaOrSlime (TYPE_1__*) ; 
 scalar_t__ BotIntermission (TYPE_1__*) ; 
 scalar_t__ BotIsDead (TYPE_1__*) ; 
 scalar_t__ BotIsObserver (TYPE_1__*) ; 
 int /*<<< orphan*/  BotMapScripts (TYPE_1__*) ; 
 scalar_t__ BotReachedGoal (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotRoamGoal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BotSetupForMovement (TYPE_1__*) ; 
 scalar_t__ BotWantsToRetreat (TYPE_1__*) ; 
 scalar_t__ FloatTime () ; 
 int MOVERESULT_MOVEMENTVIEW ; 
 int MOVERESULT_MOVEMENTVIEWSET ; 
 int MOVERESULT_MOVEMENTWEAPON ; 
 int MOVERESULT_SWIMVIEW ; 
 int MOVERESULT_WAITING ; 
 int TFL_DEFAULT ; 
 int TFL_GRAPPLEHOOK ; 
 int TFL_LAVA ; 
 int TFL_ROCKETJUMP ; 
 int TFL_SLIME ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ bot_grapple ; 
 int qfalse ; 
 int qtrue ; 
 double random () ; 
 int /*<<< orphan*/  trap_BotEmptyGoalStack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotGetSecondGoal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trap_BotGetTopGoal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trap_BotMoveToGoal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ trap_BotMovementViewTarget (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotPopGoal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotResetAvoidReach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotResetLastAvoidReach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vectoangles (int /*<<< orphan*/ ,double*) ; 

int AINode_Seek_NBG(bot_state_t *bs) {
	bot_goal_t goal;
	vec3_t target, dir;
	bot_moveresult_t moveresult;

	if (BotIsObserver(bs)) {
		AIEnter_Observer(bs, "seek nbg: observer");
		return qfalse;
	}
	//if in the intermission
	if (BotIntermission(bs)) {
		AIEnter_Intermission(bs, "seek nbg: intermision");
		return qfalse;
	}
	//respawn if dead
	if (BotIsDead(bs)) {
		AIEnter_Respawn(bs, "seek nbg: bot dead");
		return qfalse;
	}
	//
	bs->tfl = TFL_DEFAULT;
	if (bot_grapple.integer) bs->tfl |= TFL_GRAPPLEHOOK;
	//if in lava or slime the bot should be able to get out
	if (BotInLavaOrSlime(bs)) bs->tfl |= TFL_LAVA|TFL_SLIME;
	//
	if (BotCanAndWantsToRocketJump(bs)) {
		bs->tfl |= TFL_ROCKETJUMP;
	}
	//map specific code
	BotMapScripts(bs);
	//no enemy
	bs->enemy = -1;
	//if the bot has no goal
	if (!trap_BotGetTopGoal(bs->gs, &goal)) bs->nbg_time = 0;
	//if the bot touches the current goal
	else if (BotReachedGoal(bs, &goal)) {
		BotChooseWeapon(bs);
		bs->nbg_time = 0;
	}
	//
	if (bs->nbg_time < FloatTime()) {
		//pop the current goal from the stack
		trap_BotPopGoal(bs->gs);
		//check for new nearby items right away
		//NOTE: we canNOT reset the check_time to zero because it would create an endless loop of node switches
		bs->check_time = FloatTime() + 0.05;
		//go back to seek ltg
		AIEnter_Seek_LTG(bs, "seek nbg: time out");
		return qfalse;
	}
	//predict obstacles
	if (BotAIPredictObstacles(bs, &goal))
		return qfalse;
	//initialize the movement state
	BotSetupForMovement(bs);
	//move towards the goal
	trap_BotMoveToGoal(&moveresult, bs->ms, &goal, bs->tfl);
	//if the movement failed
	if (moveresult.failure) {
		//reset the avoid reach, otherwise bot is stuck in current area
		trap_BotResetAvoidReach(bs->ms);
		bs->nbg_time = 0;
	}
	//check if the bot is blocked
	BotAIBlocked(bs, &moveresult, qtrue);
	//
	BotClearPath(bs, &moveresult);
	//if the viewangles are used for the movement
	if (moveresult.flags & (MOVERESULT_MOVEMENTVIEWSET|MOVERESULT_MOVEMENTVIEW|MOVERESULT_SWIMVIEW)) {
		VectorCopy(moveresult.ideal_viewangles, bs->ideal_viewangles);
	}
	//if waiting for something
	else if (moveresult.flags & MOVERESULT_WAITING) {
		if (random() < bs->thinktime * 0.8) {
			BotRoamGoal(bs, target);
			VectorSubtract(target, bs->origin, dir);
			vectoangles(dir, bs->ideal_viewangles);
			bs->ideal_viewangles[2] *= 0.5;
		}
	}
	else if (!(bs->flags & BFL_IDEALVIEWSET)) {
		if (!trap_BotGetSecondGoal(bs->gs, &goal)) trap_BotGetTopGoal(bs->gs, &goal);
		if (trap_BotMovementViewTarget(bs->ms, &goal, bs->tfl, 300, target)) {
			VectorSubtract(target, bs->origin, dir);
			vectoangles(dir, bs->ideal_viewangles);
		}
		//FIXME: look at cluster portals?
		else vectoangles(moveresult.movedir, bs->ideal_viewangles);
		bs->ideal_viewangles[2] *= 0.5;
	}
	//if the weapon is used for the bot movement
	if (moveresult.flags & MOVERESULT_MOVEMENTWEAPON) bs->weaponnum = moveresult.weapon;
	//if there is an enemy
	if (BotFindEnemy(bs, -1)) {
		if (BotWantsToRetreat(bs)) {
			//keep the current long term goal and retreat
			AIEnter_Battle_NBG(bs, "seek nbg: found enemy");
		}
		else {
			trap_BotResetLastAvoidReach(bs->ms);
			//empty the goal stack
			trap_BotEmptyGoalStack(bs->gs);
			//go fight
			AIEnter_Battle_Fight(bs, "seek nbg: found enemy");
		}
	}
	return qtrue;
}