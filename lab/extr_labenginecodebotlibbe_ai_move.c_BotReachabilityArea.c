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
struct TYPE_7__ {int fraction; scalar_t__ ent; int /*<<< orphan*/  startsolid; } ;
typedef  TYPE_1__ bsp_trace_t ;
struct TYPE_8__ {int* endpos; int /*<<< orphan*/  startsolid; } ;
typedef  TYPE_2__ aas_trace_t ;
struct TYPE_9__ {int areanum; } ;
typedef  TYPE_3__ aas_reachability_t ;

/* Variables and functions */
 scalar_t__ AAS_AreaReachability (int) ; 
 int AAS_EntityModelindex (scalar_t__) ; 
 int AAS_NextModelReachability (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AAS_PresenceTypeBoundingBox (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  AAS_ReachabilityFromNum (int,TYPE_3__*) ; 
 scalar_t__ AAS_Swimming (int*) ; 
 TYPE_1__ AAS_Trace (int*,int*,int*,int*,int,int) ; 
 TYPE_2__ AAS_TraceClientBBox (int*,int*,int /*<<< orphan*/ ,int) ; 
 int BotFuzzyPointReachabilityArea (int*) ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SOLID ; 
 scalar_t__ ENTITYNUM_NONE ; 
 scalar_t__ ENTITYNUM_WORLD ; 
 int MODELTYPE_FUNC_BOB ; 
 int MODELTYPE_FUNC_PLAT ; 
 int /*<<< orphan*/  PRESENCE_CROUCH ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 int /*<<< orphan*/  VectorMA (int*,int,int*,int*) ; 
 int* modeltypes ; 

int BotReachabilityArea(vec3_t origin, int client)
{
	int modelnum, modeltype, reachnum, areanum;
	aas_reachability_t reach;
	vec3_t org, end, mins, maxs, up = {0, 0, 1};
	bsp_trace_t bsptrace;
	aas_trace_t trace;

	//check if the bot is standing on something
	AAS_PresenceTypeBoundingBox(PRESENCE_CROUCH, mins, maxs);
	VectorMA(origin, -3, up, end);
	bsptrace = AAS_Trace(origin, mins, maxs, end, client, CONTENTS_SOLID|CONTENTS_PLAYERCLIP);
	if (!bsptrace.startsolid && bsptrace.fraction < 1 && bsptrace.ent != ENTITYNUM_NONE)
	{
		//if standing on the world the bot should be in a valid area
		if (bsptrace.ent == ENTITYNUM_WORLD)
		{
			return BotFuzzyPointReachabilityArea(origin);
		} //end if

		modelnum = AAS_EntityModelindex(bsptrace.ent);
		modeltype = modeltypes[modelnum];

		//if standing on a func_plat or func_bobbing then the bot is assumed to be
		//in the area the reachability points to
		if (modeltype == MODELTYPE_FUNC_PLAT || modeltype == MODELTYPE_FUNC_BOB)
		{
			reachnum = AAS_NextModelReachability(0, modelnum);
			if (reachnum)
			{
				AAS_ReachabilityFromNum(reachnum, &reach);
				return reach.areanum;
			} //end if
		} //end else if

		//if the bot is swimming the bot should be in a valid area
		if (AAS_Swimming(origin))
		{
			return BotFuzzyPointReachabilityArea(origin);
		} //end if
		//
		areanum = BotFuzzyPointReachabilityArea(origin);
		//if the bot is in an area with reachabilities
		if (areanum && AAS_AreaReachability(areanum)) return areanum;
		//trace down till the ground is hit because the bot is standing on some other entity
		VectorCopy(origin, org);
		VectorCopy(org, end);
		end[2] -= 800;
		trace = AAS_TraceClientBBox(org, end, PRESENCE_CROUCH, -1);
		if (!trace.startsolid)
		{
			VectorCopy(trace.endpos, org);
		} //end if
		//
		return BotFuzzyPointReachabilityArea(org);
	} //end if
	//
	return BotFuzzyPointReachabilityArea(origin);
}