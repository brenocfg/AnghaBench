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
struct TYPE_11__ {int moveflags; int /*<<< orphan*/  client; scalar_t__* origin; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_12__ {int /*<<< orphan*/  movedir; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ bot_moveresult_t ;
struct TYPE_13__ {scalar_t__* end; } ;
typedef  TYPE_3__ aas_reachability_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotFuncBobStartEnd (TYPE_3__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  EA_Move (int /*<<< orphan*/ ,scalar_t__*,float) ; 
 int MFL_SWIMMING ; 
 int /*<<< orphan*/  MOVERESULT_SWIMVIEW ; 
 int /*<<< orphan*/  MoverBottomCenter (TYPE_3__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,int /*<<< orphan*/ ) ; 
 float VectorLength (scalar_t__*) ; 
 float VectorNormalize (scalar_t__*) ; 
 int /*<<< orphan*/  VectorSubtract (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  bot_moveresult_t_cleared (TYPE_2__) ; 
 TYPE_2__ result ; 

bot_moveresult_t BotFinishTravel_FuncBobbing(bot_movestate_t *ms, aas_reachability_t *reach)
{
	vec3_t bob_origin, bob_start, bob_end, dir, hordir, bottomcenter;
	bot_moveresult_t_cleared( result );
	float dist, speed;

	//
	BotFuncBobStartEnd(reach, bob_start, bob_end, bob_origin);
	//
	VectorSubtract(bob_origin, bob_end, dir);
	dist = VectorLength(dir);
	//if the func_bobbing is near the end
	if (dist < 16)
	{
		VectorSubtract(reach->end, ms->origin, hordir);
		if (!(ms->moveflags & MFL_SWIMMING)) hordir[2] = 0;
		dist = VectorNormalize(hordir);
		//
		if (dist > 60) dist = 60;
		speed = 360 - (360 - 6 * dist);
		//
		if (speed > 5) EA_Move(ms->client, dir, speed);
		VectorCopy(dir, result.movedir);
		//
		if (ms->moveflags & MFL_SWIMMING) result.flags |= MOVERESULT_SWIMVIEW;
	} //end if
	else
	{
		MoverBottomCenter(reach, bottomcenter);
		VectorSubtract(bottomcenter, ms->origin, hordir);
		if (!(ms->moveflags & MFL_SWIMMING)) hordir[2] = 0;
		dist = VectorNormalize(hordir);
		//
		if (dist > 5)
		{
			//move to the center of the plat
			if (dist > 100) dist = 100;
			speed = 400 - (400 - 4 * dist);
			//
			EA_Move(ms->client, hordir, speed);
			VectorCopy(hordir, result.movedir);
		} //end if
	} //end else
	return result;
}