#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_9__ {int /*<<< orphan*/  client; scalar_t__* origin; int /*<<< orphan*/  jumpreach; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_10__ {int /*<<< orphan*/  movedir; } ;
typedef  TYPE_2__ bot_moveresult_t ;
struct TYPE_11__ {scalar_t__* start; scalar_t__* end; } ;
typedef  TYPE_3__ aas_reachability_t ;

/* Variables and functions */
 double DotProduct (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  EA_Move (int /*<<< orphan*/ ,scalar_t__*,float) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,int /*<<< orphan*/ ) ; 
 float VectorNormalize (scalar_t__*) ; 
 int /*<<< orphan*/  bot_moveresult_t_cleared (TYPE_2__) ; 
 TYPE_2__ result ; 

bot_moveresult_t BotFinishTravel_Jump(bot_movestate_t *ms, aas_reachability_t *reach)
{
	vec3_t hordir, hordir2;
	float speed, dist;
	bot_moveresult_t_cleared( result );

	//if not jumped yet
	if (!ms->jumpreach) return result;
	//go straight to the reachability end
	hordir[0] = reach->end[0] - ms->origin[0];
	hordir[1] = reach->end[1] - ms->origin[1];
	hordir[2] = 0;
	dist = VectorNormalize(hordir);
	//
	hordir2[0] = reach->end[0] - reach->start[0];
	hordir2[1] = reach->end[1] - reach->start[1];
	hordir2[2] = 0;
	VectorNormalize(hordir2);
	//
	if (DotProduct(hordir, hordir2) < -0.5 && dist < 24) return result;
	//always use max speed when traveling through the air
	speed = 800;
	//
	EA_Move(ms->client, hordir, speed);
	VectorCopy(hordir, result.movedir);
	//
	return result;
}