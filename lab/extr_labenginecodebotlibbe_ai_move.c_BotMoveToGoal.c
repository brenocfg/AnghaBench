#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_91__   TYPE_5__ ;
typedef  struct TYPE_90__   TYPE_4__ ;
typedef  struct TYPE_89__   TYPE_3__ ;
typedef  struct TYPE_88__   TYPE_2__ ;
typedef  struct TYPE_87__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_87__ {int moveflags; int lastreachnum; scalar_t__ reachability_time; int client; scalar_t__ areanum; scalar_t__ lastgoalareanum; scalar_t__ lastareanum; int reachareanum; int thinktime; int /*<<< orphan*/  lastorigin; int /*<<< orphan*/  origin; int /*<<< orphan*/  numavoidspots; int /*<<< orphan*/  avoidspots; int /*<<< orphan*/  avoidreachtries; int /*<<< orphan*/  avoidreachtimes; int /*<<< orphan*/  avoidreach; int /*<<< orphan*/  velocity; scalar_t__ jumpreach; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  presencetype; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_88__ {int blockentity; int traveltype; int flags; void* blocked; void* failure; scalar_t__ type; } ;
typedef  TYPE_2__ bot_moveresult_t ;
struct TYPE_89__ {scalar_t__ areanum; } ;
typedef  TYPE_3__ bot_goal_t ;
struct TYPE_90__ {int traveltype; int facenum; scalar_t__ areanum; } ;
typedef  TYPE_4__ aas_reachability_t ;
struct TYPE_91__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 scalar_t__ AAS_AgainstLadder (int /*<<< orphan*/ ) ; 
 scalar_t__ AAS_AreaJumpPad (int) ; 
 int /*<<< orphan*/  AAS_AreaReachability (scalar_t__) ; 
 int AAS_EntityModelindex (int) ; 
 int AAS_NextAreaReachability (int,int) ; 
 int AAS_NextModelReachability (int /*<<< orphan*/ ,int) ; 
 scalar_t__ AAS_OnGround (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAS_ReachabilityFromNum (int,TYPE_4__*) ; 
 scalar_t__ AAS_Swimming (int /*<<< orphan*/ ) ; 
 scalar_t__ AAS_Time () ; 
 int AAS_TraceAreas (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int) ; 
 int AAS_TravelFlagForType (int) ; 
 TYPE_2__ BotFinishTravel_BarrierJump (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotFinishTravel_Elevator (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotFinishTravel_FuncBobbing (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotFinishTravel_Jump (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotFinishTravel_JumpPad (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotFinishTravel_WalkOffLedge (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotFinishTravel_WaterJump (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotFinishTravel_WeaponJump (TYPE_1__*,TYPE_4__*) ; 
 void* BotFuzzyPointReachabilityArea (int /*<<< orphan*/ ) ; 
 int BotGetReachabilityToGoal (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_2__ BotMoveInGoalArea (TYPE_1__*,TYPE_3__*) ; 
 TYPE_1__* BotMoveStateFromHandle (int) ; 
 int BotOnTopOfEntity (TYPE_1__*) ; 
 scalar_t__ BotReachabilityTime (TYPE_4__*) ; 
 int /*<<< orphan*/  BotResetGrapple (TYPE_1__*) ; 
 TYPE_2__ BotTravel_BFGJump (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_BarrierJump (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_Crouch (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_Elevator (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_FuncBobbing (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_Grapple (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_Jump (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_JumpPad (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_Ladder (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_RocketJump (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_Swim (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_Teleport (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_Walk (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_WalkOffLedge (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__ BotTravel_WaterJump (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int MAX_MODELS ; 
 int MFL_AGAINSTLADDER ; 
 int MFL_GRAPPLERESET ; 
 int MFL_ONGROUND ; 
 int MFL_SWIMMING ; 
 int MODELTYPE_FUNC_BOB ; 
 int MODELTYPE_FUNC_DOOR ; 
 int MODELTYPE_FUNC_PLAT ; 
 int MODELTYPE_FUNC_STATIC ; 
 int MOVERESULT_ONTOPOFOBSTACLE ; 
 int MOVERESULT_ONTOPOF_ELEVATOR ; 
 int MOVERESULT_ONTOPOF_FUNCBOB ; 
 int /*<<< orphan*/  PRT_FATAL ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 scalar_t__ RESULTTYPE_INSOLIDAREA ; 
 int TFL_JUMPPAD ; 
 int TRAVELTYPE_MASK ; 
#define  TRAVEL_BARRIERJUMP 142 
#define  TRAVEL_BFGJUMP 141 
#define  TRAVEL_CROUCH 140 
#define  TRAVEL_ELEVATOR 139 
#define  TRAVEL_FUNCBOB 138 
#define  TRAVEL_GRAPPLEHOOK 137 
#define  TRAVEL_JUMP 136 
#define  TRAVEL_JUMPPAD 135 
#define  TRAVEL_LADDER 134 
#define  TRAVEL_ROCKETJUMP 133 
#define  TRAVEL_SWIM 132 
#define  TRAVEL_TELEPORT 131 
#define  TRAVEL_WALK 130 
#define  TRAVEL_WALKOFFLEDGE 129 
#define  TRAVEL_WATERJUMP 128 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ botDeveloper ; 
 TYPE_5__ botimport ; 
 int* modeltypes ; 
 void* qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,char*,int) ; 

void BotMoveToGoal(bot_moveresult_t *result, int movestate, bot_goal_t *goal, int travelflags)
{
	int reachnum, lastreachnum, foundjumppad, ent, resultflags;
	aas_reachability_t reach, lastreach;
	bot_movestate_t *ms;
	//vec3_t mins, maxs, up = {0, 0, 1};
	//bsp_trace_t trace;
	//static int debugline;

	result->failure = qfalse;
	result->type = 0;
	result->blocked = qfalse;
	result->blockentity = 0;
	result->traveltype = 0;
	result->flags = 0;

	//
	ms = BotMoveStateFromHandle(movestate);
	if (!ms) return;
	//reset the grapple before testing if the bot has a valid goal
	//because the bot could lose all its goals when stuck to a wall
	BotResetGrapple(ms);
	//
	if (!goal)
	{
#ifdef DEBUG
		botimport.Print(PRT_MESSAGE, "client %d: movetogoal -> no goal\n", ms->client);
#endif //DEBUG
		result->failure = qtrue;
		return;
	} //end if
	//botimport.Print(PRT_MESSAGE, "numavoidreach = %d\n", ms->numavoidreach);
	//remove some of the move flags
	ms->moveflags &= ~(MFL_SWIMMING|MFL_AGAINSTLADDER);
	//set some of the move flags
	//NOTE: the MFL_ONGROUND flag is also set in the higher AI
	if (AAS_OnGround(ms->origin, ms->presencetype, ms->entitynum)) ms->moveflags |= MFL_ONGROUND;
	//
	if (ms->moveflags & MFL_ONGROUND)
	{
		int modeltype, modelnum;

		ent = BotOnTopOfEntity(ms);

		if (ent != -1)
		{
			modelnum = AAS_EntityModelindex(ent);
			if (modelnum >= 0 && modelnum < MAX_MODELS)
			{
				modeltype = modeltypes[modelnum];

				if (modeltype == MODELTYPE_FUNC_PLAT)
				{
					AAS_ReachabilityFromNum(ms->lastreachnum, &reach);
					//if the bot is Not using the elevator
					if ((reach.traveltype & TRAVELTYPE_MASK) != TRAVEL_ELEVATOR ||
						//NOTE: the face number is the plat model number
						(reach.facenum & 0x0000FFFF) != modelnum)
					{
						reachnum = AAS_NextModelReachability(0, modelnum);
						if (reachnum)
						{
							//botimport.Print(PRT_MESSAGE, "client %d: accidentally ended up on func_plat\n", ms->client);
							AAS_ReachabilityFromNum(reachnum, &reach);
							ms->lastreachnum = reachnum;
							ms->reachability_time = AAS_Time() + BotReachabilityTime(&reach);
						} //end if
						else
						{
							if (botDeveloper)
							{
								botimport.Print(PRT_MESSAGE, "client %d: on func_plat without reachability\n", ms->client);
							} //end if
							result->blocked = qtrue;
							result->blockentity = ent;
							result->flags |= MOVERESULT_ONTOPOFOBSTACLE;
							return;
						} //end else
					} //end if
					result->flags |= MOVERESULT_ONTOPOF_ELEVATOR;
				} //end if
				else if (modeltype == MODELTYPE_FUNC_BOB)
				{
					AAS_ReachabilityFromNum(ms->lastreachnum, &reach);
					//if the bot is Not using the func bobbing
					if ((reach.traveltype & TRAVELTYPE_MASK) != TRAVEL_FUNCBOB ||
						//NOTE: the face number is the func_bobbing model number
						(reach.facenum & 0x0000FFFF) != modelnum)
					{
						reachnum = AAS_NextModelReachability(0, modelnum);
						if (reachnum)
						{
							//botimport.Print(PRT_MESSAGE, "client %d: accidentally ended up on func_bobbing\n", ms->client);
							AAS_ReachabilityFromNum(reachnum, &reach);
							ms->lastreachnum = reachnum;
							ms->reachability_time = AAS_Time() + BotReachabilityTime(&reach);
						} //end if
						else
						{
							if (botDeveloper)
							{
								botimport.Print(PRT_MESSAGE, "client %d: on func_bobbing without reachability\n", ms->client);
							} //end if
							result->blocked = qtrue;
							result->blockentity = ent;
							result->flags |= MOVERESULT_ONTOPOFOBSTACLE;
							return;
						} //end else
					} //end if
					result->flags |= MOVERESULT_ONTOPOF_FUNCBOB;
				} //end if
				else if (modeltype == MODELTYPE_FUNC_STATIC || modeltype == MODELTYPE_FUNC_DOOR)
				{
					// check if ontop of a door bridge ?
					ms->areanum = BotFuzzyPointReachabilityArea(ms->origin);
					// if not in a reachability area
					if (!AAS_AreaReachability(ms->areanum))
					{
						result->blocked = qtrue;
						result->blockentity = ent;
						result->flags |= MOVERESULT_ONTOPOFOBSTACLE;
						return;
					} //end if
				} //end else if
				else
				{
					result->blocked = qtrue;
					result->blockentity = ent;
					result->flags |= MOVERESULT_ONTOPOFOBSTACLE;
					return;
				} //end else
			} //end if
		} //end if
	} //end if
	//if swimming
	if (AAS_Swimming(ms->origin)) ms->moveflags |= MFL_SWIMMING;
	//if against a ladder
	if (AAS_AgainstLadder(ms->origin)) ms->moveflags |= MFL_AGAINSTLADDER;
	//if the bot is on the ground, swimming or against a ladder
	if (ms->moveflags & (MFL_ONGROUND|MFL_SWIMMING|MFL_AGAINSTLADDER))
	{
		//botimport.Print(PRT_MESSAGE, "%s: onground, swimming or against ladder\n", ClientName(ms->entitynum-1));
		//
		AAS_ReachabilityFromNum(ms->lastreachnum, &lastreach);
		//reachability area the bot is in
		//ms->areanum = BotReachabilityArea(ms->origin, ((lastreach.traveltype & TRAVELTYPE_MASK) != TRAVEL_ELEVATOR));
		ms->areanum = BotFuzzyPointReachabilityArea(ms->origin);
		//
		if ( !ms->areanum )
		{
			result->failure = qtrue;
			result->blocked = qtrue;
			result->blockentity = 0;
			result->type = RESULTTYPE_INSOLIDAREA;
			return;
		} //end if
		//if the bot is in the goal area
		if (ms->areanum == goal->areanum)
		{
			*result = BotMoveInGoalArea(ms, goal);
			return;
		} //end if
		//assume we can use the reachability from the last frame
		reachnum = ms->lastreachnum;
		//if there is a last reachability
		if (reachnum)
		{
			AAS_ReachabilityFromNum(reachnum, &reach);
			//check if the reachability is still valid
			if (!(AAS_TravelFlagForType(reach.traveltype) & travelflags))
			{
				reachnum = 0;
			} //end if
			//special grapple hook case
			else if ((reach.traveltype & TRAVELTYPE_MASK) == TRAVEL_GRAPPLEHOOK)
			{
				if (ms->reachability_time < AAS_Time() ||
					(ms->moveflags & MFL_GRAPPLERESET))
				{
					reachnum = 0;
				} //end if
			} //end if
			//special elevator case
			else if ((reach.traveltype & TRAVELTYPE_MASK) == TRAVEL_ELEVATOR ||
				(reach.traveltype & TRAVELTYPE_MASK) == TRAVEL_FUNCBOB)
			{
				if ((result->flags & MOVERESULT_ONTOPOF_ELEVATOR) ||
					(result->flags & MOVERESULT_ONTOPOF_FUNCBOB))
				{
					ms->reachability_time = AAS_Time() + 5;
				} //end if
				//if the bot was going for an elevator and reached the reachability area
				if (ms->areanum == reach.areanum ||
					ms->reachability_time < AAS_Time())
				{
					reachnum = 0;
				} //end if
			} //end if
			else
			{
#ifdef DEBUG
				if (botDeveloper)
				{
					if (ms->reachability_time < AAS_Time())
					{
						botimport.Print(PRT_MESSAGE, "client %d: reachability timeout in ", ms->client);
						AAS_PrintTravelType(reach.traveltype & TRAVELTYPE_MASK);
						botimport.Print(PRT_MESSAGE, "\n");
					} //end if
					/*
					if (ms->lastareanum != ms->areanum)
					{
						botimport.Print(PRT_MESSAGE, "changed from area %d to %d\n", ms->lastareanum, ms->areanum);
					} //end if*/
				} //end if
#endif //DEBUG
				//if the goal area changed or the reachability timed out
				//or the area changed
				if (ms->lastgoalareanum != goal->areanum ||
						ms->reachability_time < AAS_Time() ||
						ms->lastareanum != ms->areanum)
				{
					reachnum = 0;
					//botimport.Print(PRT_MESSAGE, "area change or timeout\n");
				} //end else if
			} //end else
		} //end if
		resultflags = 0;
		//if the bot needs a new reachability
		if (!reachnum)
		{
			//if the area has no reachability links
			if (!AAS_AreaReachability(ms->areanum))
			{
#ifdef DEBUG
				if (botDeveloper)
				{
					botimport.Print(PRT_MESSAGE, "area %d no reachability\n", ms->areanum);
				} //end if
#endif //DEBUG
			} //end if
			//get a new reachability leading towards the goal
			reachnum = BotGetReachabilityToGoal(ms->origin, ms->areanum,
								ms->lastgoalareanum, ms->lastareanum,
											ms->avoidreach, ms->avoidreachtimes, ms->avoidreachtries,
														goal, travelflags,
																ms->avoidspots, ms->numavoidspots, &resultflags);
			//the area number the reachability starts in
			ms->reachareanum = ms->areanum;
			//reset some state variables
			ms->jumpreach = 0;						//for TRAVEL_JUMP
			ms->moveflags &= ~MFL_GRAPPLERESET;	//for TRAVEL_GRAPPLEHOOK
			//if there is a reachability to the goal
			if (reachnum)
			{
				AAS_ReachabilityFromNum(reachnum, &reach);
				//set a timeout for this reachability
				ms->reachability_time = AAS_Time() + BotReachabilityTime(&reach);
				//
#ifdef AVOIDREACH
				//add the reachability to the reachabilities to avoid for a while
				BotAddToAvoidReach(ms, reachnum, AVOIDREACH_TIME);
#endif //AVOIDREACH
			} //end if
#ifdef DEBUG
			
			else if (botDeveloper)
			{
				botimport.Print(PRT_MESSAGE, "goal not reachable\n");
				Com_Memset(&reach, 0, sizeof(aas_reachability_t)); //make compiler happy
			} //end else
			if (botDeveloper)
			{
				//if still going for the same goal
				if (ms->lastgoalareanum == goal->areanum)
				{
					if (ms->lastareanum == reach.areanum)
					{
						botimport.Print(PRT_MESSAGE, "same goal, going back to previous area\n");
					} //end if
				} //end if
			} //end if
#endif //DEBUG
		} //end else
		//
		ms->lastreachnum = reachnum;
		ms->lastgoalareanum = goal->areanum;
		ms->lastareanum = ms->areanum;
		//if the bot has a reachability
		if (reachnum)
		{
			//get the reachability from the number
			AAS_ReachabilityFromNum(reachnum, &reach);
			result->traveltype = reach.traveltype;
			//
#ifdef DEBUG_AI_MOVE
			AAS_ClearShownDebugLines();
			AAS_PrintTravelType(reach.traveltype & TRAVELTYPE_MASK);
			AAS_ShowReachability(&reach);
#endif //DEBUG_AI_MOVE
			//
#ifdef DEBUG
			//botimport.Print(PRT_MESSAGE, "client %d: ", ms->client);
			//AAS_PrintTravelType(reach.traveltype);
			//botimport.Print(PRT_MESSAGE, "\n");
#endif //DEBUG
			switch(reach.traveltype & TRAVELTYPE_MASK)
			{
				case TRAVEL_WALK: *result = BotTravel_Walk(ms, &reach); break;
				case TRAVEL_CROUCH: *result = BotTravel_Crouch(ms, &reach); break;
				case TRAVEL_BARRIERJUMP: *result = BotTravel_BarrierJump(ms, &reach); break;
				case TRAVEL_LADDER: *result = BotTravel_Ladder(ms, &reach); break;
				case TRAVEL_WALKOFFLEDGE: *result = BotTravel_WalkOffLedge(ms, &reach); break;
				case TRAVEL_JUMP: *result = BotTravel_Jump(ms, &reach); break;
				case TRAVEL_SWIM: *result = BotTravel_Swim(ms, &reach); break;
				case TRAVEL_WATERJUMP: *result = BotTravel_WaterJump(ms, &reach); break;
				case TRAVEL_TELEPORT: *result = BotTravel_Teleport(ms, &reach); break;
				case TRAVEL_ELEVATOR: *result = BotTravel_Elevator(ms, &reach); break;
				case TRAVEL_GRAPPLEHOOK: *result = BotTravel_Grapple(ms, &reach); break;
				case TRAVEL_ROCKETJUMP: *result = BotTravel_RocketJump(ms, &reach); break;
				case TRAVEL_BFGJUMP: *result = BotTravel_BFGJump(ms, &reach); break;
				case TRAVEL_JUMPPAD: *result = BotTravel_JumpPad(ms, &reach); break;
				case TRAVEL_FUNCBOB: *result = BotTravel_FuncBobbing(ms, &reach); break;
				default:
				{
					botimport.Print(PRT_FATAL, "travel type %d not implemented yet\n", (reach.traveltype & TRAVELTYPE_MASK));
					break;
				} //end case
			} //end switch
			result->traveltype = reach.traveltype;
			result->flags |= resultflags;
		} //end if
		else
		{
			result->failure = qtrue;
			result->flags |= resultflags;
			Com_Memset(&reach, 0, sizeof(aas_reachability_t));
		} //end else
#ifdef DEBUG
		if (botDeveloper)
		{
			if (result->failure)
			{
				botimport.Print(PRT_MESSAGE, "client %d: movement failure in ", ms->client);
				AAS_PrintTravelType(reach.traveltype & TRAVELTYPE_MASK);
				botimport.Print(PRT_MESSAGE, "\n");
			} //end if
		} //end if
#endif //DEBUG
	} //end if
	else
	{
		int i, numareas, areas[16];
		vec3_t end;

		//special handling of jump pads when the bot uses a jump pad without knowing it
		foundjumppad = qfalse;
		VectorMA(ms->origin, -2 * ms->thinktime, ms->velocity, end);
		numareas = AAS_TraceAreas(ms->origin, end, areas, NULL, 16);
		for (i = numareas-1; i >= 0; i--)
		{
			if (AAS_AreaJumpPad(areas[i]))
			{
				//botimport.Print(PRT_MESSAGE, "client %d used a jumppad without knowing, area %d\n", ms->client, areas[i]);
				foundjumppad = qtrue;
				lastreachnum = BotGetReachabilityToGoal(end, areas[i],
							ms->lastgoalareanum, ms->lastareanum,
							ms->avoidreach, ms->avoidreachtimes, ms->avoidreachtries,
							goal, TFL_JUMPPAD, ms->avoidspots, ms->numavoidspots, NULL);
				if (lastreachnum)
				{
					ms->lastreachnum = lastreachnum;
					ms->lastareanum = areas[i];
					//botimport.Print(PRT_MESSAGE, "found jumppad reachability\n");
					break;
				} //end if
				else
				{
					for (lastreachnum = AAS_NextAreaReachability(areas[i], 0); lastreachnum;
						lastreachnum = AAS_NextAreaReachability(areas[i], lastreachnum))
					{
						//get the reachability from the number
						AAS_ReachabilityFromNum(lastreachnum, &reach);
						if ((reach.traveltype & TRAVELTYPE_MASK) == TRAVEL_JUMPPAD)
						{
							ms->lastreachnum = lastreachnum;
							ms->lastareanum = areas[i];
							//botimport.Print(PRT_MESSAGE, "found jumppad reachability hard!!\n");
						} //end if
					} //end for
					if (lastreachnum) break;
				} //end else
			} //end if
		} //end for
		if (botDeveloper)
		{
			//if a jumppad is found with the trace but no reachability is found
			if (foundjumppad && !ms->lastreachnum)
			{
				botimport.Print(PRT_MESSAGE, "client %d didn't find jumppad reachability\n", ms->client);
			} //end if
		} //end if
		//
		if (ms->lastreachnum)
		{
			//botimport.Print(PRT_MESSAGE, "%s: NOT onground, swimming or against ladder\n", ClientName(ms->entitynum-1));
			AAS_ReachabilityFromNum(ms->lastreachnum, &reach);
			result->traveltype = reach.traveltype;
#ifdef DEBUG
			//botimport.Print(PRT_MESSAGE, "client %d finish: ", ms->client);
			//AAS_PrintTravelType(reach.traveltype & TRAVELTYPE_MASK);
			//botimport.Print(PRT_MESSAGE, "\n");
#endif //DEBUG
			//
			switch(reach.traveltype & TRAVELTYPE_MASK)
			{
				case TRAVEL_WALK: *result = BotTravel_Walk(ms, &reach); break;//BotFinishTravel_Walk(ms, &reach); break;
				case TRAVEL_CROUCH: /*do nothing*/ break;
				case TRAVEL_BARRIERJUMP: *result = BotFinishTravel_BarrierJump(ms, &reach); break;
				case TRAVEL_LADDER: *result = BotTravel_Ladder(ms, &reach); break;
				case TRAVEL_WALKOFFLEDGE: *result = BotFinishTravel_WalkOffLedge(ms, &reach); break;
				case TRAVEL_JUMP: *result = BotFinishTravel_Jump(ms, &reach); break;
				case TRAVEL_SWIM: *result = BotTravel_Swim(ms, &reach); break;
				case TRAVEL_WATERJUMP: *result = BotFinishTravel_WaterJump(ms, &reach); break;
				case TRAVEL_TELEPORT: /*do nothing*/ break;
				case TRAVEL_ELEVATOR: *result = BotFinishTravel_Elevator(ms, &reach); break;
				case TRAVEL_GRAPPLEHOOK: *result = BotTravel_Grapple(ms, &reach); break;
				case TRAVEL_ROCKETJUMP:
				case TRAVEL_BFGJUMP: *result = BotFinishTravel_WeaponJump(ms, &reach); break;
				case TRAVEL_JUMPPAD: *result = BotFinishTravel_JumpPad(ms, &reach); break;
				case TRAVEL_FUNCBOB: *result = BotFinishTravel_FuncBobbing(ms, &reach); break;
				default:
				{
					botimport.Print(PRT_FATAL, "(last) travel type %d not implemented yet\n", (reach.traveltype & TRAVELTYPE_MASK));
					break;
				} //end case
			} //end switch
			result->traveltype = reach.traveltype;
#ifdef DEBUG
			if (botDeveloper)
			{
				if (result->failure)
				{
					botimport.Print(PRT_MESSAGE, "client %d: movement failure in finish ", ms->client);
					AAS_PrintTravelType(reach.traveltype & TRAVELTYPE_MASK);
					botimport.Print(PRT_MESSAGE, "\n");
				} //end if
			} //end if
#endif //DEBUG
		} //end if
	} //end else
	//FIXME: is it right to do this here?
	if (result->blocked) ms->reachability_time -= 10 * ms->thinktime;
	//copy the last origin
	VectorCopy(ms->origin, ms->lastorigin);
}