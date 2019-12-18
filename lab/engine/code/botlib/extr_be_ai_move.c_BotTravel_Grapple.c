#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_21__ {scalar_t__* endpos; } ;
typedef  TYPE_1__ bsp_trace_t ;
struct TYPE_22__ {int moveflags; float lastgrappledist; double grapplevisible_time; int reachareanum; scalar_t__ reachability_time; scalar_t__* origin; int /*<<< orphan*/  client; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  viewoffset; int /*<<< orphan*/ * viewangles; } ;
typedef  TYPE_2__ bot_movestate_t ;
struct TYPE_23__ {int /*<<< orphan*/  movedir; int /*<<< orphan*/  failure; int /*<<< orphan*/ * ideal_viewangles; int /*<<< orphan*/  flags; int /*<<< orphan*/  weapon; } ;
typedef  TYPE_3__ bot_moveresult_t ;
struct TYPE_24__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  TYPE_4__ aas_reachability_t ;
struct TYPE_28__ {int /*<<< orphan*/  string; } ;
struct TYPE_27__ {int /*<<< orphan*/  string; } ;
struct TYPE_26__ {scalar_t__ value; } ;
struct TYPE_25__ {int /*<<< orphan*/  value; } ;
struct TYPE_20__ {int (* DebugLineCreate ) () ;int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  (* DebugLineShow ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AAS_PointAreaNum (scalar_t__*) ; 
 double AAS_Time () ; 
 TYPE_1__ AAS_Trace (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AngleDiff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BotCheckBlocked (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  CONTENTS_SOLID ; 
 int /*<<< orphan*/  EA_Attack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_Command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_Move (int /*<<< orphan*/ ,scalar_t__*,float) ; 
 int GrappleState (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  LINECOLOR_BLUE ; 
 int MFL_ACTIVEGRAPPLE ; 
 int MFL_GRAPPLERESET ; 
 int MFL_SWIMMING ; 
 int /*<<< orphan*/  MOVERESULT_MOVEMENTVIEW ; 
 int /*<<< orphan*/  MOVERESULT_MOVEMENTWEAPON ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  Vector2Angles (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorAdd (scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,int /*<<< orphan*/ ) ; 
 int VectorLength (scalar_t__*) ; 
 float VectorNormalize (scalar_t__*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  bot_moveresult_t_cleared (TYPE_3__) ; 
 TYPE_10__ botimport ; 
 TYPE_9__* cmd_grappleoff ; 
 TYPE_8__* cmd_grappleon ; 
 int fabs (int /*<<< orphan*/ ) ; 
 TYPE_7__* offhandgrapple ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_3__ result ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* weapindex_grapple ; 

bot_moveresult_t BotTravel_Grapple(bot_movestate_t *ms, aas_reachability_t *reach)
{
	bot_moveresult_t_cleared( result );
	float dist, speed;
	vec3_t dir, viewdir, org;
	int state, areanum;
	bsp_trace_t trace;

#ifdef DEBUG_GRAPPLE
	static int debugline;
	if (!debugline) debugline = botimport.DebugLineCreate();
	botimport.DebugLineShow(debugline, reach->start, reach->end, LINECOLOR_BLUE);
#endif //DEBUG_GRAPPLE

	//
	if (ms->moveflags & MFL_GRAPPLERESET)
	{
		if (offhandgrapple->value)
			EA_Command(ms->client, cmd_grappleoff->string);
		ms->moveflags &= ~MFL_ACTIVEGRAPPLE;
		return result;
	} //end if
	//
	if (!(int) offhandgrapple->value)
	{
		result.weapon = weapindex_grapple->value;
		result.flags |= MOVERESULT_MOVEMENTWEAPON;
	} //end if
	//
	if (ms->moveflags & MFL_ACTIVEGRAPPLE)
	{
#ifdef DEBUG_GRAPPLE
		botimport.Print(PRT_MESSAGE, "BotTravel_Grapple: active grapple\n");
#endif //DEBUG_GRAPPLE
		//
		state = GrappleState(ms, reach);
		//
		VectorSubtract(reach->end, ms->origin, dir);
		dir[2] = 0;
		dist = VectorLength(dir);
		//if very close to the grapple end or the grappled is hooked and
		//the bot doesn't get any closer
		if (state && dist < 48)
		{
			if (ms->lastgrappledist - dist < 1)
			{
#ifdef DEBUG_GRAPPLE
				botimport.Print(PRT_ERROR, "grapple normal end\n");
#endif //DEBUG_GRAPPLE
				if (offhandgrapple->value)
					EA_Command(ms->client, cmd_grappleoff->string);
				ms->moveflags &= ~MFL_ACTIVEGRAPPLE;
				ms->moveflags |= MFL_GRAPPLERESET;
				ms->reachability_time = 0;	//end the reachability
				return result;
			} //end if
		} //end if
		//if no valid grapple at all, or the grapple hooked and the bot
		//isn't moving anymore
		else if (!state || (state == 2 && dist > ms->lastgrappledist - 2))
		{
			if (ms->grapplevisible_time < AAS_Time() - 0.4)
			{
#ifdef DEBUG_GRAPPLE
				botimport.Print(PRT_ERROR, "grapple not visible\n");
#endif //DEBUG_GRAPPLE
				if (offhandgrapple->value)
					EA_Command(ms->client, cmd_grappleoff->string);
				ms->moveflags &= ~MFL_ACTIVEGRAPPLE;
				ms->moveflags |= MFL_GRAPPLERESET;
				ms->reachability_time = 0;	//end the reachability
				return result;
			} //end if
		} //end if
		else
		{
			ms->grapplevisible_time = AAS_Time();
		} //end else
		//
		if (!(int) offhandgrapple->value)
		{
			EA_Attack(ms->client);
		} //end if
		//remember the current grapple distance
		ms->lastgrappledist = dist;
	} //end if
	else
	{
#ifdef DEBUG_GRAPPLE
		botimport.Print(PRT_MESSAGE, "BotTravel_Grapple: inactive grapple\n");
#endif //DEBUG_GRAPPLE
		//
		ms->grapplevisible_time = AAS_Time();
		//
		VectorSubtract(reach->start, ms->origin, dir);
		if (!(ms->moveflags & MFL_SWIMMING)) dir[2] = 0;
		VectorAdd(ms->origin, ms->viewoffset, org);
		VectorSubtract(reach->end, org, viewdir);
		//
		dist = VectorNormalize(dir);
		Vector2Angles(viewdir, result.ideal_viewangles);
		result.flags |= MOVERESULT_MOVEMENTVIEW;
		//
		if (dist < 5 &&
			fabs(AngleDiff(result.ideal_viewangles[0], ms->viewangles[0])) < 2 &&
			fabs(AngleDiff(result.ideal_viewangles[1], ms->viewangles[1])) < 2)
		{
#ifdef DEBUG_GRAPPLE
			botimport.Print(PRT_MESSAGE, "BotTravel_Grapple: activating grapple\n");
#endif //DEBUG_GRAPPLE
			//check if the grapple missile path is clear
			VectorAdd(ms->origin, ms->viewoffset, org);
			trace = AAS_Trace(org, NULL, NULL, reach->end, ms->entitynum, CONTENTS_SOLID);
			VectorSubtract(reach->end, trace.endpos, dir);
			if (VectorLength(dir) > 16)
			{
				result.failure = qtrue;
				return result;
			} //end if
			//activate the grapple
			if (offhandgrapple->value)
			{
				EA_Command(ms->client, cmd_grappleon->string);
			} //end if
			else
			{
				EA_Attack(ms->client);
			} //end else
			ms->moveflags |= MFL_ACTIVEGRAPPLE;
			ms->lastgrappledist = 999999;
		} //end if
		else
		{
			if (dist < 70) speed = 300 - (300 - 4 * dist);
			else speed = 400;
			//
			BotCheckBlocked(ms, dir, qtrue, &result);
			//elemantary action move in direction
			EA_Move(ms->client, dir, speed);
			VectorCopy(dir, result.movedir);
		} //end else
		//if in another area before actually grappling
		areanum = AAS_PointAreaNum(ms->origin);
		if (areanum && areanum != ms->reachareanum) ms->reachability_time = 0;
	} //end else
	return result;
}