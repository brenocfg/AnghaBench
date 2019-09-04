#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec_t ;
typedef  int* vec3_t ;
struct TYPE_17__ {int fraction; size_t planenum; int* endpos; scalar_t__ startsolid; } ;
typedef  TYPE_1__ aas_trace_t ;
struct TYPE_18__ {int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ aas_plane_t ;
struct TYPE_19__ {int areanum; int* start; int* end; int traveltype; struct TYPE_19__* next; scalar_t__ traveltime; scalar_t__ edgenum; scalar_t__ facenum; } ;
typedef  TYPE_3__ aas_lreachability_t ;
struct TYPE_20__ {int faceflags; int numedges; int firstedge; size_t planenum; } ;
typedef  TYPE_4__ aas_face_t ;
struct TYPE_21__ {size_t* v; } ;
typedef  TYPE_5__ aas_edge_t ;
struct TYPE_22__ {int frames; int stopevent; int* endpos; } ;
typedef  TYPE_6__ aas_clientmove_t ;
struct TYPE_23__ {scalar_t__* mins; scalar_t__* maxs; int numfaces; int firstface; } ;
typedef  TYPE_7__ aas_area_t ;
struct TYPE_24__ {int* faceindex; int* edgeindex; TYPE_2__* planes; int /*<<< orphan*/ ** vertexes; TYPE_5__* edges; TYPE_4__* faces; TYPE_7__* areas; } ;
struct TYPE_16__ {float phys_jumpvel; int phys_maxbarrier; float phys_gravity; int phys_maxwalkvelocity; scalar_t__ phys_falldelta5; scalar_t__ phys_falldelta10; scalar_t__ rs_falldamage10; scalar_t__ rs_falldamage5; scalar_t__ rs_startjump; scalar_t__ rs_startwalkoffledge; } ;

/* Variables and functions */
 TYPE_3__* AAS_AllocReachability () ; 
 int /*<<< orphan*/  AAS_AreaClusterPortal (int) ; 
 scalar_t__ AAS_AreaCrouch (int) ; 
 int /*<<< orphan*/  AAS_AreaGrounded (int) ; 
 int /*<<< orphan*/  AAS_AreaJumpPad (int) ; 
 float AAS_ClosestEdgePoints (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int*,int*,int*,int*,float) ; 
 scalar_t__ AAS_FallDelta (int) ; 
 scalar_t__ AAS_HorizontalVelocityForJump (float,int*,int*,float*) ; 
 int AAS_MaxJumpDistance (float) ; 
 float AAS_MaxJumpHeight (float) ; 
 int AAS_PointContents (int*) ; 
 int /*<<< orphan*/  AAS_PredictClientMovement (TYPE_6__*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int,int,float,int,int /*<<< orphan*/ ,int) ; 
 int AAS_TraceAreas (int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ AAS_TraceClientBBox (int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ARRAY_LEN (int*) ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int /*<<< orphan*/  CrossProduct (int*,int*,int*) ; 
 double DotProduct (int /*<<< orphan*/ ,int*) ; 
 int FACE_GROUND ; 
 int /*<<< orphan*/  PRESENCE_NORMAL ; 
 int SE_ENTERLAVA ; 
 int SE_ENTERSLIME ; 
 int SE_ENTERWATER ; 
 int SE_HITGROUND ; 
 int SE_HITGROUNDDAMAGE ; 
 int SE_TOUCHCLUSTERPORTAL ; 
 int TRAVELTYPE_MASK ; 
 int TRAVEL_JUMP ; 
 int TRAVEL_WALKOFFLEDGE ; 
 int /*<<< orphan*/  VectorAdd (int*,int*,int*) ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 int VectorDistance (int*,int*) ; 
 float VectorLength (int*) ; 
 int /*<<< orphan*/  VectorMA (int*,int,int*,int*) ; 
 int /*<<< orphan*/  VectorMiddle (int*,int*,int*) ; 
 int /*<<< orphan*/  VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorScale (int*,float,int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int*,int*) ; 
 TYPE_10__ aassettings ; 
 TYPE_9__ aasworld ; 
 size_t abs (int) ; 
 TYPE_3__** areareachability ; 
 int fabs (int) ; 
 int qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  reach_jump ; 
 int /*<<< orphan*/  reach_walkoffledge ; 

int AAS_Reachability_Jump(int area1num, int area2num)
{
	int i, j, k, l, face1num, face2num, edge1num, edge2num, traveltype;
	int stopevent, areas[10], numareas;
	float phys_jumpvel, maxjumpdistance, maxjumpheight, height, bestdist, speed;
	vec_t *v1, *v2, *v3, *v4;
	vec3_t beststart = {0}, beststart2 = {0}, bestend = {0}, bestend2 = {0};
	vec3_t teststart, testend, dir, velocity, cmdmove, up = {0, 0, 1}, sidewards;
	aas_area_t *area1, *area2;
	aas_face_t *face1, *face2;
	aas_edge_t *edge1, *edge2;
	aas_plane_t *plane1, *plane2, *plane;
	aas_trace_t trace;
	aas_clientmove_t move;
	aas_lreachability_t *lreach;

	if (!AAS_AreaGrounded(area1num) || !AAS_AreaGrounded(area2num)) return qfalse;
	//cannot jump from or to a crouch area
	if (AAS_AreaCrouch(area1num) || AAS_AreaCrouch(area2num)) return qfalse;
	//
	area1 = &aasworld.areas[area1num];
	area2 = &aasworld.areas[area2num];
	//
	phys_jumpvel = aassettings.phys_jumpvel;
	//maximum distance a player can jump
	maxjumpdistance = 2 * AAS_MaxJumpDistance(phys_jumpvel);
	//maximum height a player can jump with the given initial z velocity
	maxjumpheight = AAS_MaxJumpHeight(phys_jumpvel);

	//if the areas are not near enough in the x-y direction
	for (i = 0; i < 2; i++)
	{
		if (area1->mins[i] > area2->maxs[i] + maxjumpdistance) return qfalse;
		if (area1->maxs[i] < area2->mins[i] - maxjumpdistance) return qfalse;
	} //end for
	//if area2 is way to high to jump up to
	if (area2->mins[2] > area1->maxs[2] + maxjumpheight) return qfalse;
	//
	bestdist = 999999;
	//
	for (i = 0; i < area1->numfaces; i++)
	{
		face1num = aasworld.faceindex[area1->firstface + i];
		face1 = &aasworld.faces[abs(face1num)];
		//if not a ground face
		if (!(face1->faceflags & FACE_GROUND)) continue;
		//
		for (j = 0; j < area2->numfaces; j++)
		{
			face2num = aasworld.faceindex[area2->firstface + j];
			face2 = &aasworld.faces[abs(face2num)];
			//if not a ground face
			if (!(face2->faceflags & FACE_GROUND)) continue;
			//
			for (k = 0; k < face1->numedges; k++)
			{
				edge1num = abs(aasworld.edgeindex[face1->firstedge + k]);
				edge1 = &aasworld.edges[edge1num];
				for (l = 0; l < face2->numedges; l++)
				{
					edge2num = abs(aasworld.edgeindex[face2->firstedge + l]);
					edge2 = &aasworld.edges[edge2num];
					//calculate the minimum distance between the two edges
					v1 = aasworld.vertexes[edge1->v[0]];
					v2 = aasworld.vertexes[edge1->v[1]];
					v3 = aasworld.vertexes[edge2->v[0]];
					v4 = aasworld.vertexes[edge2->v[1]];
					//get the ground planes
					plane1 = &aasworld.planes[face1->planenum];
					plane2 = &aasworld.planes[face2->planenum];
					//
					bestdist = AAS_ClosestEdgePoints(v1, v2, v3, v4, plane1, plane2,
														beststart, bestend,
														beststart2, bestend2, bestdist);
				} //end for
			} //end for
		} //end for
	} //end for
	VectorMiddle(beststart, beststart2, beststart);
	VectorMiddle(bestend, bestend2, bestend);
	if (bestdist > 4 && bestdist < maxjumpdistance)
	{
//		Log_Write("shortest distance between %d and %d is %f\r\n", area1num, area2num, bestdist);
		// if very close and almost no height difference then the bot can walk
		if (bestdist <= 48 && fabs(beststart[2] - bestend[2]) < 8)
		{
			speed = 400;
			traveltype = TRAVEL_WALKOFFLEDGE;
		} //end if
		else if (AAS_HorizontalVelocityForJump(0, beststart, bestend, &speed))
		{
			//FIXME: why multiply with 1.2???
			speed *= 1.2f;
			traveltype = TRAVEL_WALKOFFLEDGE;
		} //end else if
		else
		{
			//get the horizontal speed for the jump, if it isn't possible to calculate this
			//speed (the jump is not possible) then there's no jump reachability created
			if (!AAS_HorizontalVelocityForJump(phys_jumpvel, beststart, bestend, &speed))
				return qfalse;
			speed *= 1.05f;
			traveltype = TRAVEL_JUMP;
			//
			//NOTE: test if the horizontal distance isn't too small
			VectorSubtract(bestend, beststart, dir);
			dir[2] = 0;
			if (VectorLength(dir) < 10)
				return qfalse;
		} //end if
		//
		VectorSubtract(bestend, beststart, dir);
		VectorNormalize(dir);
		VectorMA(beststart, 1, dir, teststart);
		//
		VectorCopy(teststart, testend);
		testend[2] -= 100;
		trace = AAS_TraceClientBBox(teststart, testend, PRESENCE_NORMAL, -1);
		//
		if (trace.startsolid)
			return qfalse;
		if (trace.fraction < 1)
		{
			plane = &aasworld.planes[trace.planenum];
			// if the bot can stand on the surface
			if (DotProduct(plane->normal, up) >= 0.7)
			{
				// if no lava or slime below
				if (!(AAS_PointContents(trace.endpos) & (CONTENTS_LAVA|CONTENTS_SLIME)))
				{
					if (teststart[2] - trace.endpos[2] <= aassettings.phys_maxbarrier)
						return qfalse;
				} //end if
			} //end if
		} //end if
		//
		VectorMA(bestend, -1, dir, teststart);
		//
		VectorCopy(teststart, testend);
		testend[2] -= 100;
		trace = AAS_TraceClientBBox(teststart, testend, PRESENCE_NORMAL, -1);
		//
		if (trace.startsolid)
			return qfalse;
		if (trace.fraction < 1)
		{
			plane = &aasworld.planes[trace.planenum];
			// if the bot can stand on the surface
			if (DotProduct(plane->normal, up) >= 0.7)
			{
				// if no lava or slime below
				if (!(AAS_PointContents(trace.endpos) & (CONTENTS_LAVA|CONTENTS_SLIME)))
				{
					if (teststart[2] - trace.endpos[2] <= aassettings.phys_maxbarrier)
						return qfalse;
				} //end if
			} //end if
		} //end if
		//
		// get command movement
		VectorClear(cmdmove);
		if ((traveltype & TRAVELTYPE_MASK) == TRAVEL_JUMP)
			cmdmove[2] = aassettings.phys_jumpvel;
		else
			cmdmove[2] = 0;
		//
		VectorSubtract(bestend, beststart, dir);
		dir[2] = 0;
		VectorNormalize(dir);
		CrossProduct(dir, up, sidewards);
		//
		stopevent = SE_HITGROUND|SE_ENTERWATER|SE_ENTERSLIME|SE_ENTERLAVA|SE_HITGROUNDDAMAGE;
		if (!AAS_AreaClusterPortal(area1num) && !AAS_AreaClusterPortal(area2num))
			stopevent |= SE_TOUCHCLUSTERPORTAL;
		//
		for (i = 0; i < 3; i++)
		{
			//
			if (i == 1)
				VectorAdd(testend, sidewards, testend);
			else if (i == 2)
				VectorSubtract(bestend, sidewards, testend);
			else
				VectorCopy(bestend, testend);
			VectorSubtract(testend, beststart, dir);
			dir[2] = 0;
			VectorNormalize(dir);
			VectorScale(dir, speed, velocity);
			//
			AAS_PredictClientMovement(&move, -1, beststart, PRESENCE_NORMAL, qtrue,
										velocity, cmdmove, 3, 30, 0.1f,
										stopevent, 0, qfalse);
			// if prediction time wasn't enough to fully predict the movement
			if (move.frames >= 30)
				return qfalse;
			// don't enter slime or lava and don't fall from too high
			if (move.stopevent & (SE_ENTERSLIME|SE_ENTERLAVA))
				return qfalse;
			// never jump or fall through a cluster portal
			if (move.stopevent & SE_TOUCHCLUSTERPORTAL)
				return qfalse;
			//the end position should be in area2, also test a little bit back
			//because the predicted jump could have rushed through the area
			VectorMA(move.endpos, -64, dir, teststart);
			teststart[2] += 1;
			numareas = AAS_TraceAreas(move.endpos, teststart, areas, NULL, ARRAY_LEN(areas));
			for (j = 0; j < numareas; j++)
			{
				if (areas[j] == area2num)
					break;
			} //end for
			if (j < numareas)
				break;
		}
		if (i >= 3)
			return qfalse;
		//
#ifdef REACH_DEBUG
		//create the reachability
		Log_Write("jump reachability between %d and %d\r\n", area1num, area2num);
#endif //REACH_DEBUG
		//create a new reachability link
		lreach = AAS_AllocReachability();
		if (!lreach) return qfalse;
		lreach->areanum = area2num;
		lreach->facenum = 0;
		lreach->edgenum = 0;
		VectorCopy(beststart, lreach->start);
		VectorCopy(bestend, lreach->end);
		lreach->traveltype = traveltype;

		VectorSubtract(bestend, beststart, dir);
		height = dir[2];
		dir[2] = 0;
		if ((traveltype & TRAVELTYPE_MASK) == TRAVEL_WALKOFFLEDGE && height > VectorLength(dir))
		{
			lreach->traveltime = aassettings.rs_startwalkoffledge + height * 50 / aassettings.phys_gravity;
		}
		else
		{
			lreach->traveltime = aassettings.rs_startjump + VectorDistance(bestend, beststart) * 240 / aassettings.phys_maxwalkvelocity;
		} //end if
		//
		if (!AAS_AreaJumpPad(area2num))
		{
			if (AAS_FallDelta(beststart[2] - bestend[2]) > aassettings.phys_falldelta5)
			{
				lreach->traveltime += aassettings.rs_falldamage5;
			} //end if
			else if (AAS_FallDelta(beststart[2] - bestend[2]) > aassettings.phys_falldelta10)
			{
				lreach->traveltime += aassettings.rs_falldamage10;
			} //end if
		} //end if
		lreach->next = areareachability[area1num];
		areareachability[area1num] = lreach;
		//
		if ((traveltype & TRAVELTYPE_MASK) == TRAVEL_JUMP)
			reach_jump++;
		else
			reach_walkoffledge++;
	} //end if
	return qfalse;
}