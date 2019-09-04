#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_15__ {scalar_t__ lasthealth; scalar_t__* inventory; int client; scalar_t__ entitynum; scalar_t__ enemy; int enemysight_time; int enemysuicide; int enemyvisible_time; scalar_t__ enemydeath_time; int /*<<< orphan*/  origin; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  eye; int /*<<< orphan*/  character; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_16__ {scalar_t__ number; int /*<<< orphan*/  angles; int /*<<< orphan*/  origin; int /*<<< orphan*/  valid; } ;
typedef  TYPE_2__ aas_entityinfo_t ;
struct TYPE_18__ {int flags; } ;
struct TYPE_17__ {int maxclients; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotEntityInfo (int,TYPE_2__*) ; 
 float BotEntityVisible (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int) ; 
 scalar_t__ BotSameTeam (TYPE_1__*,int) ; 
 int /*<<< orphan*/  BotUpdateBattleInventory (TYPE_1__*,int) ; 
 scalar_t__ BotWantsToRetreat (TYPE_1__*) ; 
 int /*<<< orphan*/  CHARACTERISTIC_ALERTNESS ; 
 int /*<<< orphan*/  CHARACTERISTIC_EASY_FRAGGER ; 
 scalar_t__ EntityCarriesFlag (TYPE_2__*) ; 
 scalar_t__ EntityIsChatting (TYPE_2__*) ; 
 scalar_t__ EntityIsDead (TYPE_2__*) ; 
 scalar_t__ EntityIsInvisible (TYPE_2__*) ; 
 scalar_t__ EntityIsShooting (TYPE_2__*) ; 
 int FL_NOTARGET ; 
 int FloatTime () ; 
 size_t INVENTORY_HEALTH ; 
 int /*<<< orphan*/  InFieldOfVision (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 float Square (int) ; 
 float VectorLengthSquared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* g_entities ; 
 int /*<<< orphan*/  lastteleport_origin ; 
 int lastteleport_time ; 
 TYPE_3__ level ; 
 int qfalse ; 
 int qtrue ; 
 float trap_Characteristic_BFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vectoangles (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int BotFindEnemy(bot_state_t *bs, int curenemy) {
	int i, healthdecrease;
	float f, alertness, easyfragger, vis;
	float squaredist, cursquaredist;
	aas_entityinfo_t entinfo, curenemyinfo;
	vec3_t dir, angles;

	alertness = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_ALERTNESS, 0, 1);
	easyfragger = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_EASY_FRAGGER, 0, 1);
	//check if the health decreased
	healthdecrease = bs->lasthealth > bs->inventory[INVENTORY_HEALTH];
	//remember the current health value
	bs->lasthealth = bs->inventory[INVENTORY_HEALTH];
	//
	if (curenemy >= 0) {
		BotEntityInfo(curenemy, &curenemyinfo);
		if (EntityCarriesFlag(&curenemyinfo)) return qfalse;
		VectorSubtract(curenemyinfo.origin, bs->origin, dir);
		cursquaredist = VectorLengthSquared(dir);
	}
	else {
		cursquaredist = 0;
	}
#ifdef MISSIONPACK
	if (gametype == GT_OBELISK) {
		vec3_t target;
		bot_goal_t *goal;
		bsp_trace_t trace;

		if (BotTeam(bs) == TEAM_RED)
			goal = &blueobelisk;
		else
			goal = &redobelisk;
		//if the obelisk is visible
		VectorCopy(goal->origin, target);
		target[2] += 1;
		BotAI_Trace(&trace, bs->eye, NULL, NULL, target, bs->client, CONTENTS_SOLID);
		if (trace.fraction >= 1 || trace.ent == goal->entitynum) {
			if (goal->entitynum == bs->enemy) {
				return qfalse;
			}
			bs->enemy = goal->entitynum;
			bs->enemysight_time = FloatTime();
			bs->enemysuicide = qfalse;
			bs->enemydeath_time = 0;
			bs->enemyvisible_time = FloatTime();
			return qtrue;
		}
	}
#endif
	//
	for (i = 0; i < level.maxclients; i++) {

		if (i == bs->client) continue;
		//if it's the current enemy
		if (i == curenemy) continue;
		//if the enemy has targeting disabled
		if (g_entities[i].flags & FL_NOTARGET) {
			continue;
		}
		//
		BotEntityInfo(i, &entinfo);
		//
		if (!entinfo.valid) continue;
		//if the enemy isn't dead and the enemy isn't the bot self
		if (EntityIsDead(&entinfo) || entinfo.number == bs->entitynum) continue;
		//if the enemy is invisible and not shooting
		if (EntityIsInvisible(&entinfo) && !EntityIsShooting(&entinfo)) {
			continue;
		}
		//if not an easy fragger don't shoot at chatting players
		if (easyfragger < 0.5 && EntityIsChatting(&entinfo)) continue;
		//
		if (lastteleport_time > FloatTime() - 3) {
			VectorSubtract(entinfo.origin, lastteleport_origin, dir);
			if (VectorLengthSquared(dir) < Square(70)) continue;
		}
		//calculate the distance towards the enemy
		VectorSubtract(entinfo.origin, bs->origin, dir);
		squaredist = VectorLengthSquared(dir);
		//if this entity is not carrying a flag
		if (!EntityCarriesFlag(&entinfo))
		{
			//if this enemy is further away than the current one
			if (curenemy >= 0 && squaredist > cursquaredist) continue;
		} //end if
		//if the bot has no
		if (squaredist > Square(900.0 + alertness * 4000.0)) continue;
		//if on the same team
		if (BotSameTeam(bs, i)) continue;
		//if the bot's health decreased or the enemy is shooting
		if (curenemy < 0 && (healthdecrease || EntityIsShooting(&entinfo)))
			f = 360;
		else
			f = 90 + 90 - (90 - (squaredist > Square(810) ? Square(810) : squaredist) / (810 * 9));
		//check if the enemy is visible
		vis = BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, f, i);
		if (vis <= 0) continue;
		//if the enemy is quite far away, not shooting and the bot is not damaged
		if (curenemy < 0 && squaredist > Square(100) && !healthdecrease && !EntityIsShooting(&entinfo))
		{
			//check if we can avoid this enemy
			VectorSubtract(bs->origin, entinfo.origin, dir);
			vectoangles(dir, angles);
			//if the bot isn't in the fov of the enemy
			if (!InFieldOfVision(entinfo.angles, 90, angles)) {
				//update some stuff for this enemy
				BotUpdateBattleInventory(bs, i);
				//if the bot doesn't really want to fight
				if (BotWantsToRetreat(bs)) continue;
			}
		}
		//found an enemy
		bs->enemy = entinfo.number;
		if (curenemy >= 0) bs->enemysight_time = FloatTime() - 2;
		else bs->enemysight_time = FloatTime();
		bs->enemysuicide = qfalse;
		bs->enemydeath_time = 0;
		bs->enemyvisible_time = FloatTime();
		return qtrue;
	}
	return qfalse;
}