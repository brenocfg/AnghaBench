#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_7__ {int* endpos; scalar_t__ fraction; } ;
typedef  TYPE_1__ bsp_trace_t ;
struct TYPE_8__ {int* origin; int /*<<< orphan*/  entitynum; } ;
typedef  TYPE_2__ bot_state_t ;
struct TYPE_9__ {int* origin; int areanum; int* mins; int* maxs; scalar_t__ entitynum; scalar_t__ iteminfo; scalar_t__ number; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ bot_goal_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_Trace (TYPE_1__*,int*,int*,int*,int*,int /*<<< orphan*/ ,int) ; 
 int BotPointAreaNum (int*) ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_SOLID ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  GFL_AIR ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 int qfalse ; 
 int qtrue ; 

int BotGetAirGoal(bot_state_t *bs, bot_goal_t *goal) {
	bsp_trace_t bsptrace;
	vec3_t end, mins = {-15, -15, -2}, maxs = {15, 15, 2};
	int areanum;

	//trace up until we hit solid
	VectorCopy(bs->origin, end);
	end[2] += 1000;
	BotAI_Trace(&bsptrace, bs->origin, mins, maxs, end, bs->entitynum, CONTENTS_SOLID|CONTENTS_PLAYERCLIP);
	//trace down until we hit water
	VectorCopy(bsptrace.endpos, end);
	BotAI_Trace(&bsptrace, end, mins, maxs, bs->origin, bs->entitynum, CONTENTS_WATER|CONTENTS_SLIME|CONTENTS_LAVA);
	//if we found the water surface
	if (bsptrace.fraction > 0) {
		areanum = BotPointAreaNum(bsptrace.endpos);
		if (areanum) {
			VectorCopy(bsptrace.endpos, goal->origin);
			goal->origin[2] -= 2;
			goal->areanum = areanum;
			goal->mins[0] = -15;
			goal->mins[1] = -15;
			goal->mins[2] = -1;
			goal->maxs[0] = 15;
			goal->maxs[1] = 15;
			goal->maxs[2] = 1;
			goal->flags = GFL_AIR;
			goal->number = 0;
			goal->iteminfo = 0;
			goal->entitynum = 0;
			return qtrue;
		}
	}
	return qfalse;
}