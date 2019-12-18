#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_40__ {scalar_t__ enemy; int tfl; float enemyvisible_time; int* lastenemyorigin; int lastenemyareanum; float check_time; float nbg_time; int* ideal_viewangles; int flags; int /*<<< orphan*/  weaponnum; int /*<<< orphan*/  origin; int /*<<< orphan*/  ms; int /*<<< orphan*/  character; scalar_t__ ltg_time; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  eye; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  gs; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_41__ {int flags; int* ideal_viewangles; int* movedir; int /*<<< orphan*/  weapon; scalar_t__ failure; } ;
typedef  TYPE_2__ bot_moveresult_t ;
typedef  int /*<<< orphan*/  bot_goal_t ;
struct TYPE_42__ {int* origin; } ;
typedef  TYPE_3__ aas_entityinfo_t ;
struct TYPE_45__ {scalar_t__ entitynum; } ;
struct TYPE_44__ {scalar_t__ integer; } ;
struct TYPE_43__ {scalar_t__ entitynum; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIEnter_Battle_Chase (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Battle_Fight (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Battle_NBG (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Battle_SuicidalFight (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Intermission (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Observer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Respawn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Seek_LTG (TYPE_1__*,char*) ; 
 int BFL_IDEALVIEWSET ; 
 scalar_t__ Bot1FCTFCarryingFlag (TYPE_1__*) ; 
 int /*<<< orphan*/  BotAIBlocked (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  BotAI_Print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BotAimAtEnemy (TYPE_1__*) ; 
 int /*<<< orphan*/  BotBattleUseItems (TYPE_1__*) ; 
 scalar_t__ BotCTFCarryingFlag (TYPE_1__*) ; 
 int /*<<< orphan*/  BotCheckAttack (TYPE_1__*) ; 
 int /*<<< orphan*/  BotChooseWeapon (TYPE_1__*) ; 
 int /*<<< orphan*/  BotEntityInfo (scalar_t__,TYPE_3__*) ; 
 scalar_t__ BotEntityVisible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ BotFindEnemy (TYPE_1__*,int) ; 
 scalar_t__ BotHarvesterCarryingCubes (TYPE_1__*) ; 
 scalar_t__ BotInLavaOrSlime (TYPE_1__*) ; 
 scalar_t__ BotIntermission (TYPE_1__*) ; 
 scalar_t__ BotIsDead (TYPE_1__*) ; 
 scalar_t__ BotIsObserver (TYPE_1__*) ; 
 int /*<<< orphan*/  BotLongTermGoal (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotMapScripts (TYPE_1__*) ; 
 scalar_t__ BotNearbyGoal (TYPE_1__*,int,int /*<<< orphan*/ *,float) ; 
 int BotPointAreaNum (int*) ; 
 int /*<<< orphan*/  BotSetupForMovement (TYPE_1__*) ; 
 int /*<<< orphan*/  BotTeamGoals (TYPE_1__*,int) ; 
 int /*<<< orphan*/  BotUpdateBattleInventory (TYPE_1__*,int) ; 
 scalar_t__ BotWantsToChase (TYPE_1__*) ; 
 int /*<<< orphan*/  CHARACTERISTIC_ATTACK_SKILL ; 
 scalar_t__ EntityIsDead (TYPE_3__*) ; 
 float FloatTime () ; 
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_CTF ; 
 scalar_t__ GT_HARVESTER ; 
 scalar_t__ MAX_CLIENTS ; 
 int MOVERESULT_MOVEMENTVIEW ; 
 int MOVERESULT_MOVEMENTVIEWSET ; 
 int MOVERESULT_MOVEMENTWEAPON ; 
 int MOVERESULT_SWIMVIEW ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int TFL_DEFAULT ; 
 int TFL_GRAPPLEHOOK ; 
 int TFL_LAVA ; 
 int TFL_SLIME ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int /*<<< orphan*/ ,int*) ; 
 TYPE_7__ blueobelisk ; 
 TYPE_6__ bot_grapple ; 
 scalar_t__ gametype ; 
 int qfalse ; 
 int qtrue ; 
 TYPE_5__ redobelisk ; 
 scalar_t__ trap_AAS_AreaReachability (int) ; 
 int /*<<< orphan*/  trap_BotEmptyGoalStack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotMoveToGoal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ trap_BotMovementViewTarget (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  trap_BotResetAvoidReach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotResetLastAvoidReach (int /*<<< orphan*/ ) ; 
 float trap_Characteristic_BFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vectoangles (int*,int*) ; 

int AINode_Battle_Retreat(bot_state_t *bs) {
	bot_goal_t goal;
	aas_entityinfo_t entinfo;
	bot_moveresult_t moveresult;
	vec3_t target, dir;
	float attack_skill, range;
	int areanum;

	if (BotIsObserver(bs)) {
		AIEnter_Observer(bs, "battle retreat: observer");
		return qfalse;
	}
	//if in the intermission
	if (BotIntermission(bs)) {
		AIEnter_Intermission(bs, "battle retreat: intermission");
		return qfalse;
	}
	//respawn if dead
	if (BotIsDead(bs)) {
		AIEnter_Respawn(bs, "battle retreat: bot dead");
		return qfalse;
	}
	//if no enemy
	if (bs->enemy < 0) {
		AIEnter_Seek_LTG(bs, "battle retreat: no enemy");
		return qfalse;
	}
	//
	BotEntityInfo(bs->enemy, &entinfo);
	if (EntityIsDead(&entinfo)) {
		AIEnter_Seek_LTG(bs, "battle retreat: enemy dead");
		return qfalse;
	}
	//if there is another better enemy
	if (BotFindEnemy(bs, bs->enemy)) {
#ifdef DEBUG
		BotAI_Print(PRT_MESSAGE, "found new better enemy\n");
#endif
	}
	//
	bs->tfl = TFL_DEFAULT;
	if (bot_grapple.integer) bs->tfl |= TFL_GRAPPLEHOOK;
	//if in lava or slime the bot should be able to get out
	if (BotInLavaOrSlime(bs)) bs->tfl |= TFL_LAVA|TFL_SLIME;
	//map specific code
	BotMapScripts(bs);
	//update the attack inventory values
	BotUpdateBattleInventory(bs, bs->enemy);
	//if the bot doesn't want to retreat anymore... probably picked up some nice items
	if (BotWantsToChase(bs)) {
		//empty the goal stack, when chasing, only the enemy is the goal
		trap_BotEmptyGoalStack(bs->gs);
		//go chase the enemy
		AIEnter_Battle_Chase(bs, "battle retreat: wants to chase");
		return qfalse;
	}
	//update the last time the enemy was visible
	if (BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->enemy)) {
		bs->enemyvisible_time = FloatTime();
		VectorCopy(entinfo.origin, target);
		// if not a player enemy
		if (bs->enemy >= MAX_CLIENTS) {
#ifdef MISSIONPACK
			// if attacking an obelisk
			if ( bs->enemy == redobelisk.entitynum ||
				bs->enemy == blueobelisk.entitynum ) {
				target[2] += 16;
			}
#endif
		}
		//update the reachability area and origin if possible
		areanum = BotPointAreaNum(target);
		if (areanum && trap_AAS_AreaReachability(areanum)) {
			VectorCopy(target, bs->lastenemyorigin);
			bs->lastenemyareanum = areanum;
		}
	}
	//if the enemy is NOT visible for 4 seconds
	if (bs->enemyvisible_time < FloatTime() - 4) {
		AIEnter_Seek_LTG(bs, "battle retreat: lost enemy");
		return qfalse;
	}
	//else if the enemy is NOT visible
	else if (bs->enemyvisible_time < FloatTime()) {
		//if there is another enemy
		if (BotFindEnemy(bs, -1)) {
			AIEnter_Battle_Fight(bs, "battle retreat: another enemy");
			return qfalse;
		}
	}
	//
	BotTeamGoals(bs, qtrue);
	//use holdable items
	BotBattleUseItems(bs);
	//get the current long term goal while retreating
	if (!BotLongTermGoal(bs, bs->tfl, qtrue, &goal)) {
		AIEnter_Battle_SuicidalFight(bs, "battle retreat: no way out");
		return qfalse;
	}
	//check for nearby goals periodicly
	if (bs->check_time < FloatTime()) {
		bs->check_time = FloatTime() + 1;
		range = 150;
#ifdef CTF
		if (gametype == GT_CTF) {
			//if carrying a flag the bot shouldn't be distracted too much
			if (BotCTFCarryingFlag(bs))
				range = 50;
		}
#endif //CTF
#ifdef MISSIONPACK
		else if (gametype == GT_1FCTF) {
			if (Bot1FCTFCarryingFlag(bs))
				range = 50;
		}
		else if (gametype == GT_HARVESTER) {
			if (BotHarvesterCarryingCubes(bs))
				range = 80;
		}
#endif
		//
		if (BotNearbyGoal(bs, bs->tfl, &goal, range)) {
			trap_BotResetLastAvoidReach(bs->ms);
			//time the bot gets to pick up the nearby goal item
			bs->nbg_time = FloatTime() + range / 100 + 1;
			AIEnter_Battle_NBG(bs, "battle retreat: nbg");
			return qfalse;
		}
	}
	//initialize the movement state
	BotSetupForMovement(bs);
	//move towards the goal
	trap_BotMoveToGoal(&moveresult, bs->ms, &goal, bs->tfl);
	//if the movement failed
	if (moveresult.failure) {
		//reset the avoid reach, otherwise bot is stuck in current area
		trap_BotResetAvoidReach(bs->ms);
		//BotAI_Print(PRT_MESSAGE, "movement failure %d\n", moveresult.traveltype);
		bs->ltg_time = 0;
	}
	//
	BotAIBlocked(bs, &moveresult, qfalse);
	//choose the best weapon to fight with
	BotChooseWeapon(bs);
	//if the view is fixed for the movement
	if (moveresult.flags & (MOVERESULT_MOVEMENTVIEW|MOVERESULT_SWIMVIEW)) {
		VectorCopy(moveresult.ideal_viewangles, bs->ideal_viewangles);
	}
	else if (!(moveresult.flags & MOVERESULT_MOVEMENTVIEWSET)
				&& !(bs->flags & BFL_IDEALVIEWSET) ) {
		attack_skill = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_ATTACK_SKILL, 0, 1);
		//if the bot is skilled enough
		if (attack_skill > 0.3) {
			BotAimAtEnemy(bs);
		}
		else {
			if (trap_BotMovementViewTarget(bs->ms, &goal, bs->tfl, 300, target)) {
				VectorSubtract(target, bs->origin, dir);
				vectoangles(dir, bs->ideal_viewangles);
			}
			else {
				vectoangles(moveresult.movedir, bs->ideal_viewangles);
			}
			bs->ideal_viewangles[2] *= 0.5;
		}
	}
	//if the weapon is used for the bot movement
	if (moveresult.flags & MOVERESULT_MOVEMENTWEAPON) bs->weaponnum = moveresult.weapon;
	//attack the enemy if possible
	BotCheckAttack(bs);
	//
	return qtrue;
}