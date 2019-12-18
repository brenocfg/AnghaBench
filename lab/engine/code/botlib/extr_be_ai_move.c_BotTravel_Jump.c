#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_10__ {scalar_t__ reachareanum; int* origin; int /*<<< orphan*/  client; int /*<<< orphan*/  lastreachnum; int /*<<< orphan*/  jumpreach; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_11__ {int* movedir; } ;
typedef  TYPE_2__ bot_moveresult_t ;
struct TYPE_12__ {int* start; int* end; } ;
typedef  TYPE_3__ aas_reachability_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_JumpReachRunStart (TYPE_3__*,int*) ; 
 scalar_t__ AAS_PointAreaNum (int*) ; 
 double DotProduct (int*,int*) ; 
 int /*<<< orphan*/  EA_DelayedJump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_Jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_Move (int /*<<< orphan*/ ,int*,float) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 int /*<<< orphan*/  VectorMA (int*,int,int*,int*) ; 
 float VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int*,int*) ; 
 int /*<<< orphan*/  bot_moveresult_t_cleared (TYPE_2__) ; 
 TYPE_2__ result ; 

bot_moveresult_t BotTravel_Jump(bot_movestate_t *ms, aas_reachability_t *reach)
{
	vec3_t hordir, dir1, dir2, start, end, runstart;
//	vec3_t runstart, dir1, dir2, hordir;
	int gapdist;
	float dist1, dist2, speed;
	bot_moveresult_t_cleared( result );

	//
	AAS_JumpReachRunStart(reach, runstart);
	//*
	hordir[0] = runstart[0] - reach->start[0];
	hordir[1] = runstart[1] - reach->start[1];
	hordir[2] = 0;
	VectorNormalize(hordir);
	//
	VectorCopy(reach->start, start);
	start[2] += 1;
	VectorMA(reach->start, 80, hordir, runstart);
	//check for a gap
	for (gapdist = 0; gapdist < 80; gapdist += 10)
	{
		VectorMA(start, gapdist+10, hordir, end);
		end[2] += 1;
		if (AAS_PointAreaNum(end) != ms->reachareanum) break;
	} //end for
	if (gapdist < 80) VectorMA(reach->start, gapdist, hordir, runstart);
	//
	VectorSubtract(ms->origin, reach->start, dir1);
	dir1[2] = 0;
	dist1 = VectorNormalize(dir1);
	VectorSubtract(ms->origin, runstart, dir2);
	dir2[2] = 0;
	dist2 = VectorNormalize(dir2);
	//if just before the reachability start
	if (DotProduct(dir1, dir2) < -0.8 || dist2 < 5)
	{
//		botimport.Print(PRT_MESSAGE, "between jump start and run start point\n");
		hordir[0] = reach->end[0] - ms->origin[0];
		hordir[1] = reach->end[1] - ms->origin[1];
		hordir[2] = 0;
		VectorNormalize(hordir);
		//elemantary action jump
		if (dist1 < 24) EA_Jump(ms->client);
		else if (dist1 < 32) EA_DelayedJump(ms->client);
		EA_Move(ms->client, hordir, 600);
		//
		ms->jumpreach = ms->lastreachnum;
	} //end if
	else
	{
//		botimport.Print(PRT_MESSAGE, "going towards run start point\n");
		hordir[0] = runstart[0] - ms->origin[0];
		hordir[1] = runstart[1] - ms->origin[1];
		hordir[2] = 0;
		VectorNormalize(hordir);
		//
		if (dist2 > 80) dist2 = 80;
		speed = 400 - (400 - 5 * dist2);
		EA_Move(ms->client, hordir, speed);
	} //end else
	VectorCopy(hordir, result.movedir);
	//
	return result;
}