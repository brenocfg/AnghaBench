#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_10__ {scalar_t__ weapon; } ;
struct TYPE_12__ {int enemy; int attackchase_time; int attackcrouch_time; int attackjump_time; float attackstrafe_time; int flags; int /*<<< orphan*/  ms; scalar_t__ thinktime; TYPE_1__ cur_ps; int /*<<< orphan*/  origin; int /*<<< orphan*/  character; int /*<<< orphan*/  lastenemyorigin; int /*<<< orphan*/  lastenemyareanum; } ;
typedef  TYPE_3__ bot_state_t ;
typedef  int /*<<< orphan*/  bot_moveresult_t ;
struct TYPE_13__ {int entitynum; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  origin; int /*<<< orphan*/  areanum; } ;
typedef  TYPE_4__ bot_goal_t ;
struct TYPE_14__ {int /*<<< orphan*/  origin; } ;
typedef  TYPE_5__ aas_entityinfo_t ;
struct TYPE_11__ {int member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int BFL_STRAFERIGHT ; 
 int /*<<< orphan*/  BotEntityInfo (int,TYPE_5__*) ; 
 int /*<<< orphan*/  BotSetupForMovement (TYPE_3__*) ; 
 int /*<<< orphan*/  CHARACTERISTIC_ATTACK_SKILL ; 
 int /*<<< orphan*/  CHARACTERISTIC_CROUCHER ; 
 int /*<<< orphan*/  CHARACTERISTIC_JUMPER ; 
 int /*<<< orphan*/  CrossProduct (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int FloatTime () ; 
 float IDEAL_ATTACKDIST ; 
 int MOVE_CROUCH ; 
 int MOVE_JUMP ; 
 int MOVE_WALK ; 
 int /*<<< orphan*/  VectorAdd (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNegate (scalar_t__*,scalar_t__*) ; 
 float VectorNormalize (scalar_t__*) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ WP_GAUNTLET ; 
 double crandom () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 double random () ; 
 scalar_t__ trap_BotMoveInDirection (int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  trap_BotMoveToGoal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 float trap_Characteristic_BFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

bot_moveresult_t BotAttackMove(bot_state_t *bs, int tfl) {
	int movetype, i, attackentity;
	float attack_skill, jumper, croucher, dist, strafechange_time;
	float attack_dist, attack_range;
	vec3_t forward, backward, sideward, hordir, up = {0, 0, 1};
	aas_entityinfo_t entinfo;
	bot_moveresult_t moveresult;
	bot_goal_t goal;

	attackentity = bs->enemy;
	//
	if (bs->attackchase_time > FloatTime()) {
		//create the chase goal
		goal.entitynum = attackentity;
		goal.areanum = bs->lastenemyareanum;
		VectorCopy(bs->lastenemyorigin, goal.origin);
		VectorSet(goal.mins, -8, -8, -8);
		VectorSet(goal.maxs, 8, 8, 8);
		//initialize the movement state
		BotSetupForMovement(bs);
		//move towards the goal
		trap_BotMoveToGoal(&moveresult, bs->ms, &goal, tfl);
		return moveresult;
	}
	//
	memset(&moveresult, 0, sizeof(bot_moveresult_t));
	//
	attack_skill = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_ATTACK_SKILL, 0, 1);
	jumper = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_JUMPER, 0, 1);
	croucher = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CROUCHER, 0, 1);
	//if the bot is really stupid
	if (attack_skill < 0.2) return moveresult;
	//initialize the movement state
	BotSetupForMovement(bs);
	//get the enemy entity info
	BotEntityInfo(attackentity, &entinfo);
	//direction towards the enemy
	VectorSubtract(entinfo.origin, bs->origin, forward);
	//the distance towards the enemy
	dist = VectorNormalize(forward);
	VectorNegate(forward, backward);
	//walk, crouch or jump
	movetype = MOVE_WALK;
	//
	if (bs->attackcrouch_time < FloatTime() - 1) {
		if (random() < jumper) {
			movetype = MOVE_JUMP;
		}
		//wait at least one second before crouching again
		else if (bs->attackcrouch_time < FloatTime() - 1 && random() < croucher) {
			bs->attackcrouch_time = FloatTime() + croucher * 5;
		}
	}
	if (bs->attackcrouch_time > FloatTime()) movetype = MOVE_CROUCH;
	//if the bot should jump
	if (movetype == MOVE_JUMP) {
		//if jumped last frame
		if (bs->attackjump_time > FloatTime()) {
			movetype = MOVE_WALK;
		}
		else {
			bs->attackjump_time = FloatTime() + 1;
		}
	}
	if (bs->cur_ps.weapon == WP_GAUNTLET) {
		attack_dist = 0;
		attack_range = 0;
	}
	else {
		attack_dist = IDEAL_ATTACKDIST;
		attack_range = 40;
	}
	//if the bot is stupid
	if (attack_skill <= 0.4) {
		//just walk to or away from the enemy
		if (dist > attack_dist + attack_range) {
			if (trap_BotMoveInDirection(bs->ms, forward, 400, movetype)) return moveresult;
		}
		if (dist < attack_dist - attack_range) {
			if (trap_BotMoveInDirection(bs->ms, backward, 400, movetype)) return moveresult;
		}
		return moveresult;
	}
	//increase the strafe time
	bs->attackstrafe_time += bs->thinktime;
	//get the strafe change time
	strafechange_time = 0.4 + (1 - attack_skill) * 0.2;
	if (attack_skill > 0.7) strafechange_time += crandom() * 0.2;
	//if the strafe direction should be changed
	if (bs->attackstrafe_time > strafechange_time) {
		//some magic number :)
		if (random() > 0.935) {
			//flip the strafe direction
			bs->flags ^= BFL_STRAFERIGHT;
			bs->attackstrafe_time = 0;
		}
	}
	//
	for (i = 0; i < 2; i++) {
		hordir[0] = forward[0];
		hordir[1] = forward[1];
		hordir[2] = 0;
		VectorNormalize(hordir);
		//get the sideward vector
		CrossProduct(hordir, up, sideward);
		//reverse the vector depending on the strafe direction
		if (bs->flags & BFL_STRAFERIGHT) VectorNegate(sideward, sideward);
		//randomly go back a little
		if (random() > 0.9) {
			VectorAdd(sideward, backward, sideward);
		}
		else {
			//walk forward or backward to get at the ideal attack distance
			if (dist > attack_dist + attack_range) {
				VectorAdd(sideward, forward, sideward);
			}
			else if (dist < attack_dist - attack_range) {
				VectorAdd(sideward, backward, sideward);
			}
		}
		//perform the movement
		if (trap_BotMoveInDirection(bs->ms, sideward, 400, movetype))
			return moveresult;
		//movement failed, flip the strafe direction
		bs->flags ^= BFL_STRAFERIGHT;
		bs->attackstrafe_time = 0;
	}
	//bot couldn't do any useful movement
//	bs->attackchase_time = AAS_Time() + 6;
	return moveresult;
}