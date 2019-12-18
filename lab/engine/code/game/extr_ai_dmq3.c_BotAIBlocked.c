#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
typedef  int /*<<< orphan*/  netname ;
struct TYPE_22__ {double notblocked_time; int flags; scalar_t__ ainode; scalar_t__ ltg_time; scalar_t__ nbg_time; int /*<<< orphan*/  ms; int /*<<< orphan*/  areanum; TYPE_1__* activatestack; int /*<<< orphan*/  client; } ;
typedef  TYPE_4__ bot_state_t ;
struct TYPE_23__ {scalar_t__ type; int flags; scalar_t__* movedir; int /*<<< orphan*/  blockentity; int /*<<< orphan*/  blocked; } ;
typedef  TYPE_5__ bot_moveresult_t ;
struct TYPE_20__ {int /*<<< orphan*/  entitynum; } ;
struct TYPE_24__ {TYPE_2__ goal; } ;
typedef  TYPE_6__ bot_activategoal_t ;
struct TYPE_25__ {scalar_t__ modelindex; int /*<<< orphan*/  number; } ;
typedef  TYPE_7__ aas_entityinfo_t ;
struct TYPE_21__ {int member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {int /*<<< orphan*/  inuse; } ;

/* Variables and functions */
 scalar_t__ AINode_Seek_LTG ; 
 scalar_t__ AINode_Seek_NBG ; 
 int /*<<< orphan*/  AngleVectors (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BFL_AVOIDRIGHT ; 
 int /*<<< orphan*/  BotAI_Print (int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  BotEnableActivateGoalAreas (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BotEntityInfo (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int BotGetActivateGoal (TYPE_4__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  BotGoForActivateGoal (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  BotIsGoingToActivateEntity (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BotRandomMove (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ClientName (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  CrossProduct (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 double FloatTime () ; 
 int MAX_NETNAME ; 
 int MOVERESULT_ONTOPOFOBSTACLE ; 
 int MOVE_CROUCH ; 
 int MOVE_WALK ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 scalar_t__ RESULTTYPE_INSOLIDAREA ; 
 int /*<<< orphan*/  VectorMA (scalar_t__*,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorNegate (scalar_t__*,scalar_t__*) ; 
 double VectorNormalize (scalar_t__*) ; 
 int /*<<< orphan*/  VectorSet (scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ max_bspmodelindex ; 
 int /*<<< orphan*/  qtrue ; 
 int random () ; 
 scalar_t__ trap_AAS_AreaReachability (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotMoveInDirection (int /*<<< orphan*/ ,scalar_t__*,int,int) ; 

void BotAIBlocked(bot_state_t *bs, bot_moveresult_t *moveresult, int activate) {
#ifdef OBSTACLEDEBUG
	char netname[MAX_NETNAME];
#endif
	int movetype, bspent;
	vec3_t hordir, sideward, angles, up = {0, 0, 1};
	//vec3_t start, end, mins, maxs;
	aas_entityinfo_t entinfo;
	bot_activategoal_t activategoal;

	// if the bot is not blocked by anything
	if (!moveresult->blocked) {
		bs->notblocked_time = FloatTime();
		return;
	}
	// if stuck in a solid area
	if ( moveresult->type == RESULTTYPE_INSOLIDAREA ) {
		// move in a random direction in the hope to get out
		BotRandomMove(bs, moveresult);
		//
		return;
	}
	// get info for the entity that is blocking the bot
	BotEntityInfo(moveresult->blockentity, &entinfo);
#ifdef OBSTACLEDEBUG
	ClientName(bs->client, netname, sizeof(netname));
	BotAI_Print(PRT_MESSAGE, "%s: I'm blocked by model %d\n", netname, entinfo.modelindex);
#endif // OBSTACLEDEBUG
	// if blocked by a bsp model and the bot wants to activate it
	if (activate && entinfo.modelindex > 0 && entinfo.modelindex <= max_bspmodelindex) {
		// find the bsp entity which should be activated in order to get the blocking entity out of the way
		bspent = BotGetActivateGoal(bs, entinfo.number, &activategoal);
		if (bspent) {
			//
			if (bs->activatestack && !bs->activatestack->inuse)
				bs->activatestack = NULL;
			// if not already trying to activate this entity
			if (!BotIsGoingToActivateEntity(bs, activategoal.goal.entitynum)) {
				//
				BotGoForActivateGoal(bs, &activategoal);
			}
			// if ontop of an obstacle or
			// if the bot is not in a reachability area it'll still
			// need some dynamic obstacle avoidance, otherwise return
			if (!(moveresult->flags & MOVERESULT_ONTOPOFOBSTACLE) &&
				trap_AAS_AreaReachability(bs->areanum))
				return;
		}
		else {
			// enable any routing areas that were disabled
			BotEnableActivateGoalAreas(&activategoal, qtrue);
		}
	}
	// just some basic dynamic obstacle avoidance code
	hordir[0] = moveresult->movedir[0];
	hordir[1] = moveresult->movedir[1];
	hordir[2] = 0;
	// if no direction just take a random direction
	if (VectorNormalize(hordir) < 0.1) {
		VectorSet(angles, 0, 360 * random(), 0);
		AngleVectors(angles, hordir, NULL, NULL);
	}
	//
	//if (moveresult->flags & MOVERESULT_ONTOPOFOBSTACLE) movetype = MOVE_JUMP;
	//else
	movetype = MOVE_WALK;
	// if there's an obstacle at the bot's feet and head then
	// the bot might be able to crouch through
	//VectorCopy(bs->origin, start);
	//start[2] += 18;
	//VectorMA(start, 5, hordir, end);
	//VectorSet(mins, -16, -16, -24);
	//VectorSet(maxs, 16, 16, 4);
	//
	//bsptrace = AAS_Trace(start, mins, maxs, end, bs->entitynum, MASK_PLAYERSOLID);
	//if (bsptrace.fraction >= 1) movetype = MOVE_CROUCH;
	// get the sideward vector
	CrossProduct(hordir, up, sideward);
	//
	if (bs->flags & BFL_AVOIDRIGHT) VectorNegate(sideward, sideward);
	// try to crouch straight forward?
	if (movetype != MOVE_CROUCH || !trap_BotMoveInDirection(bs->ms, hordir, 400, movetype)) {
		// perform the movement
		if (!trap_BotMoveInDirection(bs->ms, sideward, 400, movetype)) {
			// flip the avoid direction flag
			bs->flags ^= BFL_AVOIDRIGHT;
			// flip the direction
			// VectorNegate(sideward, sideward);
			VectorMA(sideward, -1, hordir, sideward);
			// move in the other direction
			trap_BotMoveInDirection(bs->ms, sideward, 400, movetype);
		}
	}
	//
	if (bs->notblocked_time < FloatTime() - 0.4) {
		// just reset goals and hope the bot will go into another direction?
		// is this still needed??
		if (bs->ainode == AINode_Seek_NBG) bs->nbg_time = 0;
		else if (bs->ainode == AINode_Seek_LTG) bs->ltg_time = 0;
	}
}