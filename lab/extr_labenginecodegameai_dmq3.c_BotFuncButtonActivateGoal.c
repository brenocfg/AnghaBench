#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
typedef  int /*<<< orphan*/  model ;
struct TYPE_9__ {double fraction; int ent; } ;
typedef  TYPE_2__ bsp_trace_t ;
struct TYPE_10__ {scalar_t__* origin; int areanum; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  eye; } ;
typedef  TYPE_3__ bot_state_t ;
struct TYPE_8__ {int entitynum; scalar_t__* origin; int areanum; scalar_t__* mins; scalar_t__* maxs; scalar_t__ flags; scalar_t__ number; } ;
struct TYPE_11__ {int shoot; scalar_t__* target; TYPE_1__ goal; } ;
typedef  TYPE_4__ bot_activategoal_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_Trace (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BotModelMinsMaxs (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  BotSetMovedir (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ET_MOVER ; 
 int /*<<< orphan*/  MASK_SHOT ; 
 int /*<<< orphan*/  PRESENCE_CROUCH ; 
 int /*<<< orphan*/  VectorAdd (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorClear (scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorMA (scalar_t__*,float,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorScale (scalar_t__*,double,scalar_t__*) ; 
 int /*<<< orphan*/  VectorSet (scalar_t__*,int,int,int) ; 
 int /*<<< orphan*/  VectorSubtract (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int atoi (char*) ; 
 float fabs (scalar_t__) ; 
 int qfalse ; 
 int qtrue ; 
 scalar_t__ trap_AAS_AreaReachability (int) ; 
 int /*<<< orphan*/  trap_AAS_FloatForBSPEpairKey (int,char*,float*) ; 
 int /*<<< orphan*/  trap_AAS_PresenceTypeBoundingBox (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int trap_AAS_TraceAreas (scalar_t__*,scalar_t__*,int*,scalar_t__**,int) ; 
 int /*<<< orphan*/  trap_AAS_ValueForBSPEpairKey (int,char*,char*,int) ; 

int BotFuncButtonActivateGoal(bot_state_t *bs, int bspent, bot_activategoal_t *activategoal) {
	int i, areas[10], numareas, modelindex, entitynum;
	char model[128];
	float lip, dist, health, angle;
	vec3_t size, start, end, mins, maxs, angles, points[10];
	vec3_t movedir, origin, goalorigin, bboxmins, bboxmaxs;
	vec3_t extramins = {1, 1, 1}, extramaxs = {-1, -1, -1};
	bsp_trace_t bsptrace;

	activategoal->shoot = qfalse;
	VectorClear(activategoal->target);
	//create a bot goal towards the button
	trap_AAS_ValueForBSPEpairKey(bspent, "model", model, sizeof(model));
	if (!*model)
		return qfalse;
	modelindex = atoi(model+1);
	if (!modelindex)
		return qfalse;
	entitynum = BotModelMinsMaxs(modelindex, ET_MOVER, 0, mins, maxs);
	//get the lip of the button
	trap_AAS_FloatForBSPEpairKey(bspent, "lip", &lip);
	if (!lip) lip = 4;
	//get the move direction from the angle
	trap_AAS_FloatForBSPEpairKey(bspent, "angle", &angle);
	VectorSet(angles, 0, angle, 0);
	BotSetMovedir(angles, movedir);
	//button size
	VectorSubtract(maxs, mins, size);
	//button origin
	VectorAdd(mins, maxs, origin);
	VectorScale(origin, 0.5, origin);
	//touch distance of the button
	dist = fabs(movedir[0]) * size[0] + fabs(movedir[1]) * size[1] + fabs(movedir[2]) * size[2];
	dist *= 0.5;
	//
	trap_AAS_FloatForBSPEpairKey(bspent, "health", &health);
	//if the button is shootable
	if (health) {
		//calculate the shoot target
		VectorMA(origin, -dist, movedir, goalorigin);
		//
		VectorCopy(goalorigin, activategoal->target);
		activategoal->shoot = qtrue;
		//
		BotAI_Trace(&bsptrace, bs->eye, NULL, NULL, goalorigin, bs->entitynum, MASK_SHOT);
		// if the button is visible from the current position
		if (bsptrace.fraction >= 1.0 || bsptrace.ent == entitynum) {
			//
			activategoal->goal.entitynum = entitynum; //NOTE: this is the entity number of the shootable button
			activategoal->goal.number = 0;
			activategoal->goal.flags = 0;
			VectorCopy(bs->origin, activategoal->goal.origin);
			activategoal->goal.areanum = bs->areanum;
			VectorSet(activategoal->goal.mins, -8, -8, -8);
			VectorSet(activategoal->goal.maxs, 8, 8, 8);
			//
			return qtrue;
		}
		else {
			//create a goal from where the button is visible and shoot at the button from there
			//add bounding box size to the dist
			trap_AAS_PresenceTypeBoundingBox(PRESENCE_CROUCH, bboxmins, bboxmaxs);
			for (i = 0; i < 3; i++) {
				if (movedir[i] < 0) dist += fabs(movedir[i]) * fabs(bboxmaxs[i]);
				else dist += fabs(movedir[i]) * fabs(bboxmins[i]);
			}
			//calculate the goal origin
			VectorMA(origin, -dist, movedir, goalorigin);
			//
			VectorCopy(goalorigin, start);
			start[2] += 24;
			VectorCopy(start, end);
			end[2] -= 512;
			numareas = trap_AAS_TraceAreas(start, end, areas, points, 10);
			//
			for (i = numareas-1; i >= 0; i--) {
				if (trap_AAS_AreaReachability(areas[i])) {
					break;
				}
			}
			if (i < 0) {
				// FIXME: trace forward and maybe in other directions to find a valid area
			}
			if (i >= 0) {
				//
				VectorCopy(points[i], activategoal->goal.origin);
				activategoal->goal.areanum = areas[i];
				VectorSet(activategoal->goal.mins, 8, 8, 8);
				VectorSet(activategoal->goal.maxs, -8, -8, -8);
				//
				for (i = 0; i < 3; i++)
				{
					if (movedir[i] < 0) activategoal->goal.maxs[i] += fabs(movedir[i]) * fabs(extramaxs[i]);
					else activategoal->goal.mins[i] += fabs(movedir[i]) * fabs(extramins[i]);
				} //end for
				//
				activategoal->goal.entitynum = entitynum;
				activategoal->goal.number = 0;
				activategoal->goal.flags = 0;
				return qtrue;
			}
		}
		return qfalse;
	}
	else {
		//add bounding box size to the dist
		trap_AAS_PresenceTypeBoundingBox(PRESENCE_CROUCH, bboxmins, bboxmaxs);
		for (i = 0; i < 3; i++) {
			if (movedir[i] < 0) dist += fabs(movedir[i]) * fabs(bboxmaxs[i]);
			else dist += fabs(movedir[i]) * fabs(bboxmins[i]);
		}
		//calculate the goal origin
		VectorMA(origin, -dist, movedir, goalorigin);
		//
		VectorCopy(goalorigin, start);
		start[2] += 24;
		VectorCopy(start, end);
		end[2] -= 100;
		numareas = trap_AAS_TraceAreas(start, end, areas, NULL, 10);
		//
		for (i = 0; i < numareas; i++) {
			if (trap_AAS_AreaReachability(areas[i])) {
				break;
			}
		}
		if (i < numareas) {
			//
			VectorCopy(origin, activategoal->goal.origin);
			activategoal->goal.areanum = areas[i];
			VectorSubtract(mins, origin, activategoal->goal.mins);
			VectorSubtract(maxs, origin, activategoal->goal.maxs);
			//
			for (i = 0; i < 3; i++)
			{
				if (movedir[i] < 0) activategoal->goal.maxs[i] += fabs(movedir[i]) * fabs(extramaxs[i]);
				else activategoal->goal.mins[i] += fabs(movedir[i]) * fabs(extramins[i]);
			} //end for
			//
			activategoal->goal.entitynum = entitynum;
			activategoal->goal.number = 0;
			activategoal->goal.flags = 0;
			return qtrue;
		}
	}
	return qfalse;
}