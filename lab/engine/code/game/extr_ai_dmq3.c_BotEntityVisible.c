#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_5__ {int contents; int fraction; int ent; scalar_t__* endpos; } ;
typedef  TYPE_1__ bsp_trace_t ;
struct TYPE_6__ {scalar_t__* mins; scalar_t__* maxs; scalar_t__* origin; int /*<<< orphan*/  valid; } ;
typedef  TYPE_2__ aas_entityinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_Trace (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  BotEntityInfo (int,TYPE_2__*) ; 
 int CONTENTS_FOG ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_SOLID ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  InFieldOfVision (scalar_t__*,float,scalar_t__*) ; 
 int /*<<< orphan*/  VectorAdd (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 float VectorLengthSquared (scalar_t__*) ; 
 int /*<<< orphan*/  VectorScale (scalar_t__*,double,scalar_t__*) ; 
 int /*<<< orphan*/  VectorSubtract (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int trap_AAS_PointContents (scalar_t__*) ; 
 int /*<<< orphan*/  vectoangles (scalar_t__*,scalar_t__*) ; 

float BotEntityVisible(int viewer, vec3_t eye, vec3_t viewangles, float fov, int ent) {
	int i, contents_mask, passent, hitent, infog, inwater, otherinfog, pc;
	float squaredfogdist, waterfactor, vis, bestvis;
	bsp_trace_t trace;
	aas_entityinfo_t entinfo;
	vec3_t dir, entangles, start, end, middle;

	BotEntityInfo(ent, &entinfo);
	if (!entinfo.valid) {
		return 0;
	}

	//calculate middle of bounding box
	VectorAdd(entinfo.mins, entinfo.maxs, middle);
	VectorScale(middle, 0.5, middle);
	VectorAdd(entinfo.origin, middle, middle);
	//check if entity is within field of vision
	VectorSubtract(middle, eye, dir);
	vectoangles(dir, entangles);
	if (!InFieldOfVision(viewangles, fov, entangles)) return 0;
	//
	pc = trap_AAS_PointContents(eye);
	infog = (pc & CONTENTS_FOG);
	inwater = (pc & (CONTENTS_LAVA|CONTENTS_SLIME|CONTENTS_WATER));
	//
	bestvis = 0;
	for (i = 0; i < 3; i++) {
		//if the point is not in potential visible sight
		//if (!AAS_inPVS(eye, middle)) continue;
		//
		contents_mask = CONTENTS_SOLID|CONTENTS_PLAYERCLIP;
		passent = viewer;
		hitent = ent;
		VectorCopy(eye, start);
		VectorCopy(middle, end);
		//if the entity is in water, lava or slime
		if (trap_AAS_PointContents(middle) & (CONTENTS_LAVA|CONTENTS_SLIME|CONTENTS_WATER)) {
			contents_mask |= (CONTENTS_LAVA|CONTENTS_SLIME|CONTENTS_WATER);
		}
		//if eye is in water, lava or slime
		if (inwater) {
			if (!(contents_mask & (CONTENTS_LAVA|CONTENTS_SLIME|CONTENTS_WATER))) {
				passent = ent;
				hitent = viewer;
				VectorCopy(middle, start);
				VectorCopy(eye, end);
			}
			contents_mask ^= (CONTENTS_LAVA|CONTENTS_SLIME|CONTENTS_WATER);
		}
		//trace from start to end
		BotAI_Trace(&trace, start, NULL, NULL, end, passent, contents_mask);
		//if water was hit
		waterfactor = 1.0;
		//note: trace.contents is always 0, see BotAI_Trace
		if (trace.contents & (CONTENTS_LAVA|CONTENTS_SLIME|CONTENTS_WATER)) {
			//if the water surface is translucent
			if (1) {
				//trace through the water
				contents_mask &= ~(CONTENTS_LAVA|CONTENTS_SLIME|CONTENTS_WATER);
				BotAI_Trace(&trace, trace.endpos, NULL, NULL, end, passent, contents_mask);
				waterfactor = 0.5;
			}
		}
		//if a full trace or the hitent was hit
		if (trace.fraction >= 1 || trace.ent == hitent) {
			//check for fog, assuming there's only one fog brush where
			//either the viewer or the entity is in or both are in
			otherinfog = (trap_AAS_PointContents(middle) & CONTENTS_FOG);
			if (infog && otherinfog) {
				VectorSubtract(trace.endpos, eye, dir);
				squaredfogdist = VectorLengthSquared(dir);
			}
			else if (infog) {
				VectorCopy(trace.endpos, start);
				BotAI_Trace(&trace, start, NULL, NULL, eye, viewer, CONTENTS_FOG);
				VectorSubtract(eye, trace.endpos, dir);
				squaredfogdist = VectorLengthSquared(dir);
			}
			else if (otherinfog) {
				VectorCopy(trace.endpos, end);
				BotAI_Trace(&trace, eye, NULL, NULL, end, viewer, CONTENTS_FOG);
				VectorSubtract(end, trace.endpos, dir);
				squaredfogdist = VectorLengthSquared(dir);
			}
			else {
				//if the entity and the viewer are not in fog assume there's no fog in between
				squaredfogdist = 0;
			}
			//decrease visibility with the view distance through fog
			vis = 1 / ((squaredfogdist * 0.001) < 1 ? 1 : (squaredfogdist * 0.001));
			//if entering water visibility is reduced
			vis *= waterfactor;
			//
			if (vis > bestvis) bestvis = vis;
			//if pretty much no fog
			if (bestvis >= 0.95) return bestvis;
		}
		//check bottom and top of bounding box as well
		if (i == 0) middle[2] += entinfo.mins[2];
		else if (i == 1) middle[2] += entinfo.maxs[2] - entinfo.mins[2];
	}
	return bestvis;
}