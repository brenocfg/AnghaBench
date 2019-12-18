#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_17__ {int moveflags; int /*<<< orphan*/  client; scalar_t__* origin; scalar_t__ reachability_time; int /*<<< orphan*/  entitynum; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_18__ {int /*<<< orphan*/  flags; scalar_t__* movedir; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ bot_moveresult_t ;
struct TYPE_19__ {scalar_t__* start; scalar_t__* end; } ;
typedef  TYPE_3__ aas_reachability_t ;
struct TYPE_21__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_20__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotCheckBarrierJump (TYPE_1__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  BotCheckBlocked (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ BotOnMover (scalar_t__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ DotProduct (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  EA_Move (int /*<<< orphan*/ ,scalar_t__*,float) ; 
 int MFL_SWIMMING ; 
 int /*<<< orphan*/  MOVERESULT_SWIMVIEW ; 
 int /*<<< orphan*/  MOVERESULT_WAITING ; 
 int /*<<< orphan*/  MoverBottomCenter (TYPE_3__*,scalar_t__*) ; 
 int /*<<< orphan*/  MoverDown (TYPE_3__*) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  RESULTTYPE_ELEVATORUP ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 float VectorLength (scalar_t__*) ; 
 float VectorNormalize (scalar_t__*) ; 
 int /*<<< orphan*/  VectorSubtract (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  bot_moveresult_t_cleared (TYPE_2__) ; 
 TYPE_6__ botimport ; 
 scalar_t__ fabsf (scalar_t__) ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_2__ result ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* sv_maxbarrier ; 

bot_moveresult_t BotTravel_Elevator(bot_movestate_t *ms, aas_reachability_t *reach)
{
	vec3_t dir, dir1, dir2, hordir, bottomcenter;
	float dist, dist1, dist2, speed;
	bot_moveresult_t_cleared( result );

	//if standing on the plat
	if (BotOnMover(ms->origin, ms->entitynum, reach))
	{
#ifdef DEBUG_ELEVATOR
		botimport.Print(PRT_MESSAGE, "bot on elevator\n");
#endif //DEBUG_ELEVATOR
		//if vertically not too far from the end point
		if (fabsf(ms->origin[2] - reach->end[2]) < sv_maxbarrier->value)
		{
#ifdef DEBUG_ELEVATOR
			botimport.Print(PRT_MESSAGE, "bot moving to end\n");
#endif //DEBUG_ELEVATOR
			//move to the end point
			VectorSubtract(reach->end, ms->origin, hordir);
			hordir[2] = 0;
			VectorNormalize(hordir);
			if (!BotCheckBarrierJump(ms, hordir, 100))
			{
				EA_Move(ms->client, hordir, 400);
			} //end if
			VectorCopy(hordir, result.movedir);
		} //end else
		//if not really close to the center of the elevator
		else
		{
			MoverBottomCenter(reach, bottomcenter);
			VectorSubtract(bottomcenter, ms->origin, hordir);
			hordir[2] = 0;
			dist = VectorNormalize(hordir);
			//
			if (dist > 10)
			{
#ifdef DEBUG_ELEVATOR
				botimport.Print(PRT_MESSAGE, "bot moving to center\n");
#endif //DEBUG_ELEVATOR
				//move to the center of the plat
				if (dist > 100) dist = 100;
				speed = 400 - (400 - 4 * dist);
				//
				EA_Move(ms->client, hordir, speed);
				VectorCopy(hordir, result.movedir);
			} //end if
		} //end else
	} //end if
	else
	{
#ifdef DEBUG_ELEVATOR
		botimport.Print(PRT_MESSAGE, "bot not on elevator\n");
#endif //DEBUG_ELEVATOR
		//if very near the reachability end
		VectorSubtract(reach->end, ms->origin, dir);
		dist = VectorLength(dir);
		if (dist < 64)
		{
			if (dist > 60) dist = 60;
			speed = 360 - (360 - 6 * dist);
			//
			if ((ms->moveflags & MFL_SWIMMING) || !BotCheckBarrierJump(ms, dir, 50))
			{
				if (speed > 5) EA_Move(ms->client, dir, speed);
			} //end if
			VectorCopy(dir, result.movedir);
			//
			if (ms->moveflags & MFL_SWIMMING) result.flags |= MOVERESULT_SWIMVIEW;
			//stop using this reachability
			ms->reachability_time = 0;
			return result;
		} //end if
		//get direction and distance to reachability start
		VectorSubtract(reach->start, ms->origin, dir1);
		if (!(ms->moveflags & MFL_SWIMMING)) dir1[2] = 0;
		dist1 = VectorNormalize(dir1);
		//if the elevator isn't down
		if (!MoverDown(reach))
		{
#ifdef DEBUG_ELEVATOR
			botimport.Print(PRT_MESSAGE, "elevator not down\n");
#endif //DEBUG_ELEVATOR
			dist = dist1;
			VectorCopy(dir1, dir);
			//
			BotCheckBlocked(ms, dir, qfalse, &result);
			//
			if (dist > 60) dist = 60;
			speed = 360 - (360 - 6 * dist);
			//
			if (!(ms->moveflags & MFL_SWIMMING) && !BotCheckBarrierJump(ms, dir, 50))
			{
				if (speed > 5) EA_Move(ms->client, dir, speed);
			} //end if
			VectorCopy(dir, result.movedir);
			//
			if (ms->moveflags & MFL_SWIMMING) result.flags |= MOVERESULT_SWIMVIEW;
			//this isn't a failure... just wait till the elevator comes down
			result.type = RESULTTYPE_ELEVATORUP;
			result.flags |= MOVERESULT_WAITING;
			return result;
		} //end if
		//get direction and distance to elevator bottom center
		MoverBottomCenter(reach, bottomcenter);
		VectorSubtract(bottomcenter, ms->origin, dir2);
		if (!(ms->moveflags & MFL_SWIMMING)) dir2[2] = 0;
		dist2 = VectorNormalize(dir2);
		//if very close to the reachability start or
		//closer to the elevator center or
		//between reachability start and elevator center
		if (dist1 < 20 || dist2 < dist1 || DotProduct(dir1, dir2) < 0)
		{
#ifdef DEBUG_ELEVATOR
			botimport.Print(PRT_MESSAGE, "bot moving to center\n");
#endif //DEBUG_ELEVATOR
			dist = dist2;
			VectorCopy(dir2, dir);
		} //end if
		else //closer to the reachability start
		{
#ifdef DEBUG_ELEVATOR
			botimport.Print(PRT_MESSAGE, "bot moving to start\n");
#endif //DEBUG_ELEVATOR
			dist = dist1;
			VectorCopy(dir1, dir);
		} //end else
		//
		BotCheckBlocked(ms, dir, qfalse, &result);
		//
		if (dist > 60) dist = 60;
		speed = 400 - (400 - 6 * dist);
		//
		if (!(ms->moveflags & MFL_SWIMMING) && !BotCheckBarrierJump(ms, dir, 50))
		{
			EA_Move(ms->client, dir, speed);
		} //end if
		VectorCopy(dir, result.movedir);
		//
		if (ms->moveflags & MFL_SWIMMING) result.flags |= MOVERESULT_SWIMVIEW;
	} //end else
	return result;
}