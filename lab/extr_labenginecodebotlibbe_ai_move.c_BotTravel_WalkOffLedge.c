#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_11__ {int /*<<< orphan*/  client; scalar_t__* origin; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_12__ {int /*<<< orphan*/  movedir; } ;
typedef  TYPE_2__ bot_moveresult_t ;
struct TYPE_13__ {scalar_t__* end; scalar_t__* start; } ;
typedef  TYPE_3__ aas_reachability_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_HorizontalVelocityForJump (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,float*) ; 
 int /*<<< orphan*/  BotCheckBlocked (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  EA_Move (int /*<<< orphan*/ ,scalar_t__*,float) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,int /*<<< orphan*/ ) ; 
 float VectorLength (scalar_t__*) ; 
 float VectorNormalize (scalar_t__*) ; 
 int /*<<< orphan*/  VectorSubtract (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  bot_moveresult_t_cleared (TYPE_2__) ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_2__ result ; 

bot_moveresult_t BotTravel_WalkOffLedge(bot_movestate_t *ms, aas_reachability_t *reach)
{
	vec3_t hordir, dir;
	float dist, speed, reachhordist;
	bot_moveresult_t_cleared( result );

	//check if the bot is blocked by anything
	VectorSubtract(reach->start, ms->origin, dir);
	VectorNormalize(dir);
	BotCheckBlocked(ms, dir, qtrue, &result);
	//if the reachability start and end are practically above each other
	VectorSubtract(reach->end, reach->start, dir);
	dir[2] = 0;
	reachhordist = VectorLength(dir);
	//walk straight to the reachability start
	hordir[0] = reach->start[0] - ms->origin[0];
	hordir[1] = reach->start[1] - ms->origin[1];
	hordir[2] = 0;
	dist = VectorNormalize(hordir);
	//if pretty close to the start focus on the reachability end
	if (dist < 48)
	{
		hordir[0] = reach->end[0] - ms->origin[0];
		hordir[1] = reach->end[1] - ms->origin[1];
		hordir[2] = 0;
		VectorNormalize(hordir);
		//
		if (reachhordist < 20)
		{
			speed = 100;
		} //end if
		else if (!AAS_HorizontalVelocityForJump(0, reach->start, reach->end, &speed))
		{
			speed = 400;
		} //end if
	} //end if
	else
	{
		if (reachhordist < 20)
		{
			if (dist > 64) dist = 64;
			speed = 400 - (256 - 4 * dist);
		} //end if
		else
		{
			speed = 400;
		} //end else
	} //end else
	//
	BotCheckBlocked(ms, hordir, qtrue, &result);
	//elemantary action
	EA_Move(ms->client, hordir, speed);
	VectorCopy(hordir, result.movedir);
	//
	return result;
}