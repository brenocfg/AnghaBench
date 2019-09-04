#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_13__ {double fraction; int* endpos; int /*<<< orphan*/  startsolid; } ;
typedef  TYPE_2__ aas_trace_t ;
struct TYPE_14__ {int* normal; } ;
typedef  TYPE_3__ aas_plane_t ;
struct TYPE_15__ {int areanum; int edgenum; int* start; int* end; int traveltime; void* next; void* traveltype; scalar_t__ facenum; } ;
typedef  TYPE_4__ aas_lreachability_t ;
struct TYPE_16__ {int faceflags; int planenum; int numedges; int firstedge; } ;
typedef  TYPE_5__ aas_face_t ;
struct TYPE_17__ {size_t* v; } ;
typedef  TYPE_6__ aas_edge_t ;
struct TYPE_18__ {scalar_t__* mins; scalar_t__* maxs; int numfaces; int firstface; } ;
typedef  TYPE_7__ aas_area_t ;
struct TYPE_20__ {float phys_maxstep; int phys_maxwaterjump; int rs_waterjump; float phys_maxbarrier; int rs_barrierjump; int rs_maxfallheight; int rs_startwalkoffledge; int phys_gravity; scalar_t__ phys_falldelta5; scalar_t__ phys_falldelta10; scalar_t__ rs_falldamage10; scalar_t__ rs_falldamage5; scalar_t__ rs_startcrouch; } ;
struct TYPE_19__ {int* faceindex; int* edgeindex; int** vertexes; TYPE_1__* areasettings; TYPE_6__* edges; TYPE_5__* faces; TYPE_3__* planes; TYPE_7__* areas; } ;
struct TYPE_12__ {int areaflags; int presencetype; } ;

/* Variables and functions */
 TYPE_4__* AAS_AllocReachability () ; 
 scalar_t__ AAS_AreaClusterPortal (int) ; 
 scalar_t__ AAS_AreaCrouch (int) ; 
 int /*<<< orphan*/  AAS_AreaGrounded (int) ; 
 int /*<<< orphan*/  AAS_AreaJumpPad (int) ; 
 int AAS_AreaSwim (int) ; 
 scalar_t__ AAS_FallDelta (float) ; 
 int AAS_PointAreaNum (int*) ; 
 int AAS_TraceAreas (int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ AAS_TraceClientBBox (int*,int*,int,int) ; 
 int AREA_LIQUID ; 
 int /*<<< orphan*/  ARRAY_LEN (int*) ; 
 int /*<<< orphan*/  CrossProduct (int*,int*,int*) ; 
 float DotProduct (int*,int*) ; 
 int FACE_GROUND ; 
 int /*<<< orphan*/  INSIDEUNITS ; 
 int /*<<< orphan*/  INSIDEUNITS_WALKEND ; 
 int /*<<< orphan*/  INSIDEUNITS_WALKSTART ; 
 int /*<<< orphan*/  INSIDEUNITS_WATERJUMP ; 
 int PRESENCE_NORMAL ; 
 void* TRAVEL_BARRIERJUMP ; 
 void* TRAVEL_WALK ; 
 void* TRAVEL_WALKOFFLEDGE ; 
 void* TRAVEL_WATERJUMP ; 
 int /*<<< orphan*/  VectorAdd (int*,int*,int*) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 float VectorLength (int*) ; 
 int /*<<< orphan*/  VectorMA (int*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorScale (int*,double,int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int*,int*) ; 
 TYPE_9__ aassettings ; 
 TYPE_8__ aasworld ; 
 size_t abs (int) ; 
 void** areareachability ; 
 int fabs (float) ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  reach_barrier ; 
 int /*<<< orphan*/  reach_step ; 
 int /*<<< orphan*/  reach_walk ; 
 int /*<<< orphan*/  reach_walkoffledge ; 
 int /*<<< orphan*/  reach_waterjump ; 

int AAS_Reachability_Step_Barrier_WaterJump_WalkOffLedge(int area1num, int area2num)
{
	int i, j, k, l, edge1num, edge2num, areas[10], numareas;
	int ground_bestarea2groundedgenum, ground_foundreach;
	int water_bestarea2groundedgenum, water_foundreach;
	int side1, area1swim, faceside1, groundface1num;
	float dist, dist1, dist2, diff, ortdot;
	//float invgravitydot;
	float x1, x2, x3, x4, y1, y2, y3, y4, tmp, y;
	float length, ground_bestlength, water_bestlength, ground_bestdist, water_bestdist;
	vec3_t v1, v2, v3, v4, tmpv, p1area1, p1area2, p2area1, p2area2;
	vec3_t normal, ort, edgevec, start, end, dir;
	vec3_t ground_beststart = {0, 0, 0}, ground_bestend = {0, 0, 0}, ground_bestnormal = {0, 0, 0};
	vec3_t water_beststart = {0, 0, 0}, water_bestend = {0, 0, 0}, water_bestnormal = {0, 0, 0};
	vec3_t invgravity = {0, 0, 1};
	vec3_t testpoint;
	aas_plane_t *plane;
	aas_area_t *area1, *area2;
	aas_face_t *groundface1, *groundface2;
	aas_edge_t *edge1, *edge2;
	aas_lreachability_t *lreach;
	aas_trace_t trace;

	//must be able to walk or swim in the first area
	if (!AAS_AreaGrounded(area1num) && !AAS_AreaSwim(area1num)) return qfalse;
	//
	if (!AAS_AreaGrounded(area2num) && !AAS_AreaSwim(area2num)) return qfalse;
	//
	area1 = &aasworld.areas[area1num];
	area2 = &aasworld.areas[area2num];
	//if the first area contains a liquid
	area1swim = AAS_AreaSwim(area1num);
	//if the areas are not near enough in the x-y direction
	for (i = 0; i < 2; i++)
	{
		if (area1->mins[i] > area2->maxs[i] + 10) return qfalse;
		if (area1->maxs[i] < area2->mins[i] - 10) return qfalse;
	} //end for
	//
	ground_foundreach = qfalse;
	ground_bestdist = 99999;
	ground_bestlength = 0;
	ground_bestarea2groundedgenum = 0;
	//
	water_foundreach = qfalse;
	water_bestdist = 99999;
	water_bestlength = 0;
	water_bestarea2groundedgenum = 0;
	//
	for (i = 0; i < area1->numfaces; i++)
	{
		groundface1num = aasworld.faceindex[area1->firstface + i];
		faceside1 = groundface1num < 0;
		groundface1 = &aasworld.faces[abs(groundface1num)];
		//if this isn't a ground face
		if (!(groundface1->faceflags & FACE_GROUND))
		{
			//if we can swim in the first area
			if (area1swim)
			{
				//face plane must be more or less horizontal
				plane = &aasworld.planes[groundface1->planenum ^ (!faceside1)];
				if (DotProduct(plane->normal, invgravity) < 0.7) continue;
			} //end if
			else
			{
				//if we can't swim in the area it must be a ground face
				continue;
			} //end else
		} //end if
		//
		for (k = 0; k < groundface1->numedges; k++)
		{
			edge1num = aasworld.edgeindex[groundface1->firstedge + k];
			side1 = (edge1num < 0);
			//NOTE: for water faces we must take the side area 1 is
			// on into account because the face is shared and doesn't
			// have to be oriented correctly
			if (!(groundface1->faceflags & FACE_GROUND)) side1 = (side1 == faceside1);
			edge1num = abs(edge1num);
			edge1 = &aasworld.edges[edge1num];
			//vertexes of the edge
			VectorCopy(aasworld.vertexes[edge1->v[!side1]], v1);
			VectorCopy(aasworld.vertexes[edge1->v[side1]], v2);
			//get a vertical plane through the edge
			//NOTE: normal is pointing into area 2 because the
			//face edges are stored counter clockwise
			VectorSubtract(v2, v1, edgevec);
			CrossProduct(edgevec, invgravity, normal);
			VectorNormalize(normal);
			dist = DotProduct(normal, v1);
			//check the faces from the second area
			for (j = 0; j < area2->numfaces; j++)
			{
				groundface2 = &aasworld.faces[abs(aasworld.faceindex[area2->firstface + j])];
				//must be a ground face
				if (!(groundface2->faceflags & FACE_GROUND)) continue;
				//check the edges of this ground face
				for (l = 0; l < groundface2->numedges; l++)
				{
					edge2num = abs(aasworld.edgeindex[groundface2->firstedge + l]);
					edge2 = &aasworld.edges[edge2num];
					//vertexes of the edge
					VectorCopy(aasworld.vertexes[edge2->v[0]], v3);
					VectorCopy(aasworld.vertexes[edge2->v[1]], v4);
					//check the distance between the two points and the vertical plane
					//through the edge of area1
					diff = DotProduct(normal, v3) - dist;
					if (diff < -0.1 || diff > 0.1) continue;
					diff = DotProduct(normal, v4) - dist;
					if (diff < -0.1 || diff > 0.1) continue;
					//
					//project the two ground edges into the step side plane
					//and calculate the shortest distance between the two
					//edges if they overlap in the direction orthogonal to
					//the gravity direction
					CrossProduct(invgravity, normal, ort);
					//invgravitydot = DotProduct(invgravity, invgravity);
					ortdot = DotProduct(ort, ort);
					//projection into the step plane
					//NOTE: since gravity is vertical this is just the z coordinate
					y1 = v1[2];//DotProduct(v1, invgravity) / invgravitydot;
					y2 = v2[2];//DotProduct(v2, invgravity) / invgravitydot;
					y3 = v3[2];//DotProduct(v3, invgravity) / invgravitydot;
					y4 = v4[2];//DotProduct(v4, invgravity) / invgravitydot;
					//
					x1 = DotProduct(v1, ort) / ortdot;
					x2 = DotProduct(v2, ort) / ortdot;
					x3 = DotProduct(v3, ort) / ortdot;
					x4 = DotProduct(v4, ort) / ortdot;
					//
					if (x1 > x2)
					{
						tmp = x1; x1 = x2; x2 = tmp;
						tmp = y1; y1 = y2; y2 = tmp;
						VectorCopy(v1, tmpv); VectorCopy(v2, v1); VectorCopy(tmpv, v2);
					} //end if
					if (x3 > x4)
					{
						tmp = x3; x3 = x4; x4 = tmp;
						tmp = y3; y3 = y4; y4 = tmp;
						VectorCopy(v3, tmpv); VectorCopy(v4, v3); VectorCopy(tmpv, v4);
					} //end if
					//if the two projected edge lines have no overlap
					if (x2 <= x3 || x4 <= x1)
					{
//						Log_Write("lines no overlap: from area %d to %d\r\n", area1num, area2num);
						continue;
					} //end if
					//if the two lines fully overlap
					if ((x1 - 0.5 < x3 && x4 < x2 + 0.5) &&
							(x3 - 0.5 < x1 && x2 < x4 + 0.5))
					{
						dist1 = y3 - y1;
						dist2 = y4 - y2;
						VectorCopy(v1, p1area1);
						VectorCopy(v2, p2area1);
						VectorCopy(v3, p1area2);
						VectorCopy(v4, p2area2);
					} //end if
					else
					{
						//if the points are equal
						if (x1 > x3 - 0.1 && x1 < x3 + 0.1)
						{
							dist1 = y3 - y1;
							VectorCopy(v1, p1area1);
							VectorCopy(v3, p1area2);
						} //end if
						else if (x1 < x3)
						{
							y = y1 + (x3 - x1) * (y2 - y1) / (x2 - x1);
							dist1 = y3 - y;
							VectorCopy(v3, p1area1);
							p1area1[2] = y;
							VectorCopy(v3, p1area2);
						} //end if
						else
						{
							y = y3 + (x1 - x3) * (y4 - y3) / (x4 - x3);
							dist1 = y - y1;
							VectorCopy(v1, p1area1);
							VectorCopy(v1, p1area2);
							p1area2[2] = y;
						} //end if
						//if the points are equal
						if (x2 > x4 - 0.1 && x2 < x4 + 0.1)
						{
							dist2 = y4 - y2;
							VectorCopy(v2, p2area1);
							VectorCopy(v4, p2area2);
						} //end if
						else if (x2 < x4)
						{
							y = y3 + (x2 - x3) * (y4 - y3) / (x4 - x3);
							dist2 = y - y2;
							VectorCopy(v2, p2area1);
							VectorCopy(v2, p2area2);
							p2area2[2] = y;
						} //end if
						else
						{
							y = y1 + (x4 - x1) * (y2 - y1) / (x2 - x1);
							dist2 = y4 - y;
							VectorCopy(v4, p2area1);
							p2area1[2] = y;
							VectorCopy(v4, p2area2);
						} //end else
					} //end else
					//if both distances are pretty much equal
					//then we take the middle of the points
					if (dist1 > dist2 - 1 && dist1 < dist2 + 1)
					{
						dist = dist1;
						VectorAdd(p1area1, p2area1, start);
						VectorScale(start, 0.5, start);
						VectorAdd(p1area2, p2area2, end);
						VectorScale(end, 0.5, end);
					} //end if
					else if (dist1 < dist2)
					{
						dist = dist1;
						VectorCopy(p1area1, start);
						VectorCopy(p1area2, end);
					} //end else if
					else
					{
						dist = dist2;
						VectorCopy(p2area1, start);
						VectorCopy(p2area2, end);
					} //end else
					//get the length of the overlapping part of the edges of the two areas
					VectorSubtract(p2area2, p1area2, dir);
					length = VectorLength(dir);
					//
					if (groundface1->faceflags & FACE_GROUND)
					{
						//if the vertical distance is smaller
						if (dist < ground_bestdist ||
								//or the vertical distance is pretty much the same
								//but the overlapping part of the edges is longer
								(dist < ground_bestdist + 1 && length > ground_bestlength))
						{
							ground_bestdist = dist;
							ground_bestlength = length;
							ground_foundreach = qtrue;
							ground_bestarea2groundedgenum = edge1num;
							//best point towards area1
							VectorCopy(start, ground_beststart);
							//normal is pointing into area2
							VectorCopy(normal, ground_bestnormal);
							//best point towards area2
							VectorCopy(end, ground_bestend);
						} //end if
					} //end if
					else
					{
						//if the vertical distance is smaller
						if (dist < water_bestdist ||
								//or the vertical distance is pretty much the same
								//but the overlapping part of the edges is longer
								(dist < water_bestdist + 1 && length > water_bestlength))
						{
							water_bestdist = dist;
							water_bestlength = length;
							water_foundreach = qtrue;
							water_bestarea2groundedgenum = edge1num;
							//best point towards area1
							VectorCopy(start, water_beststart);
							//normal is pointing into area2
							VectorCopy(normal, water_bestnormal);
							//best point towards area2
							VectorCopy(end, water_bestend);
						} //end if
					} //end else
				} //end for
			} //end for
		} //end for
	} //end for
	//
	// NOTE: swim reachabilities are already filtered out
	//
	// Steps
	//
	//        ---------
	//        |          step height -> TRAVEL_WALK
	//--------|
	//
	//        ---------
	//~~~~~~~~|          step height and low water -> TRAVEL_WALK
	//--------|
	//
	//~~~~~~~~~~~~~~~~~~
	//        ---------
	//        |          step height and low water up to the step -> TRAVEL_WALK
	//--------|
	//
	//check for a step reachability
	if (ground_foundreach)
	{
		//if area2 is higher but lower than the maximum step height
		//NOTE: ground_bestdist >= 0 also catches equal floor reachabilities
		if (ground_bestdist >= 0 && ground_bestdist < aassettings.phys_maxstep)
		{
			//create walk reachability from area1 to area2
			lreach = AAS_AllocReachability();
			if (!lreach) return qfalse;
			lreach->areanum = area2num;
			lreach->facenum = 0;
			lreach->edgenum = ground_bestarea2groundedgenum;
			VectorMA(ground_beststart, INSIDEUNITS_WALKSTART, ground_bestnormal, lreach->start);
			VectorMA(ground_bestend, INSIDEUNITS_WALKEND, ground_bestnormal, lreach->end);
			lreach->traveltype = TRAVEL_WALK;
			lreach->traveltime = 0;//1;
			//if going into a crouch area
			if (!AAS_AreaCrouch(area1num) && AAS_AreaCrouch(area2num))
			{
				lreach->traveltime += aassettings.rs_startcrouch;
			} //end if
			lreach->next = areareachability[area1num];
			areareachability[area1num] = lreach;
			//NOTE: if there's nearby solid or a gap area after this area
			/*
			if (!AAS_NearbySolidOrGap(lreach->start, lreach->end))
			{
				lreach->traveltime += 100;
			} //end if
			*/
			//avoid rather small areas
			//if (AAS_AreaGroundFaceArea(lreach->areanum) < 500) lreach->traveltime += 100;
			//
			reach_step++;
			return qtrue;
		} //end if
	} //end if
	//
	// Water Jumps
	//
	//        ---------
	//        |
	//~~~~~~~~|
	//        |
	//        |          higher than step height and water up to waterjump height -> TRAVEL_WATERJUMP
	//--------|
	//
	//~~~~~~~~~~~~~~~~~~
	//        ---------
	//        |
	//        |
	//        |
	//        |          higher than step height and low water up to the step -> TRAVEL_WATERJUMP
	//--------|
	//
	//check for a waterjump reachability
	if (water_foundreach)
	{
		//get a test point a little bit towards area1
		VectorMA(water_bestend, -INSIDEUNITS, water_bestnormal, testpoint);
		//go down the maximum waterjump height
		testpoint[2] -= aassettings.phys_maxwaterjump;
		//if there IS water the sv_maxwaterjump height below the bestend point
		if (aasworld.areasettings[AAS_PointAreaNum(testpoint)].areaflags & AREA_LIQUID)
		{
			//don't create ridiculous water jump reachabilities from areas very far below
			//the water surface
			if (water_bestdist < aassettings.phys_maxwaterjump + 24)
			{
				//waterjumping from or towards a crouch only area is not possible in Quake2
				if ((aasworld.areasettings[area1num].presencetype & PRESENCE_NORMAL) &&
						(aasworld.areasettings[area2num].presencetype & PRESENCE_NORMAL))
				{
					//create water jump reachability from area1 to area2
					lreach = AAS_AllocReachability();
					if (!lreach) return qfalse;
					lreach->areanum = area2num;
					lreach->facenum = 0;
					lreach->edgenum = water_bestarea2groundedgenum;
					VectorCopy(water_beststart, lreach->start);
					VectorMA(water_bestend, INSIDEUNITS_WATERJUMP, water_bestnormal, lreach->end);
					lreach->traveltype = TRAVEL_WATERJUMP;
					lreach->traveltime = aassettings.rs_waterjump;
					lreach->next = areareachability[area1num];
					areareachability[area1num] = lreach;
					//we've got another waterjump reachability
					reach_waterjump++;
					return qtrue;
				} //end if
			} //end if
		} //end if
	} //end if
	//
	// Barrier Jumps
	//
	//        ---------
	//        |
	//        |
	//        |
	//        |         higher than step height lower than barrier height -> TRAVEL_BARRIERJUMP
	//--------|
	//
	//        ---------
	//        |
	//        |
	//        |
	//~~~~~~~~|         higher than step height lower than barrier height
	//--------|         and a thin layer of water in the area to jump from -> TRAVEL_BARRIERJUMP
	//
	//check for a barrier jump reachability
	if (ground_foundreach)
	{
		//if area2 is higher but lower than the maximum barrier jump height
		if (ground_bestdist > 0 && ground_bestdist < aassettings.phys_maxbarrier)
		{
			//if no water in area1 or a very thin layer of water on the ground
			if (!water_foundreach || (ground_bestdist - water_bestdist < 16))
			{
				//cannot perform a barrier jump towards or from a crouch area in Quake2
				if (!AAS_AreaCrouch(area1num) && !AAS_AreaCrouch(area2num))
				{
					//create barrier jump reachability from area1 to area2
					lreach = AAS_AllocReachability();
					if (!lreach) return qfalse;
					lreach->areanum = area2num;
					lreach->facenum = 0;
					lreach->edgenum = ground_bestarea2groundedgenum;
					VectorMA(ground_beststart, INSIDEUNITS_WALKSTART, ground_bestnormal, lreach->start);
					VectorMA(ground_bestend, INSIDEUNITS_WALKEND, ground_bestnormal, lreach->end);
					lreach->traveltype = TRAVEL_BARRIERJUMP;
					lreach->traveltime = aassettings.rs_barrierjump;//AAS_BarrierJumpTravelTime();
					lreach->next = areareachability[area1num];
					areareachability[area1num] = lreach;
					//we've got another barrierjump reachability
					reach_barrier++;
					return qtrue;
				} //end if
			} //end if
		} //end if
	} //end if
	//
	// Walk and Walk Off Ledge
	//
	//--------|
	//        |          can walk or step back -> TRAVEL_WALK
	//        ---------
	//
	//--------|
	//        |
	//        |
	//        |
	//        |          cannot walk/step back -> TRAVEL_WALKOFFLEDGE
	//        ---------
	//
	//--------|
	//        |
	//        |~~~~~~~~
	//        |
	//        |          cannot step back but can waterjump back -> TRAVEL_WALKOFFLEDGE
	//        ---------  FIXME: create TRAVEL_WALK reach??
	//
	//check for a walk or walk off ledge reachability
	if (ground_foundreach)
	{
		if (ground_bestdist < 0)
		{
			if (ground_bestdist > -aassettings.phys_maxstep)
			{
				//create walk reachability from area1 to area2
				lreach = AAS_AllocReachability();
				if (!lreach) return qfalse;
				lreach->areanum = area2num;
				lreach->facenum = 0;
				lreach->edgenum = ground_bestarea2groundedgenum;
				VectorMA(ground_beststart, INSIDEUNITS_WALKSTART, ground_bestnormal, lreach->start);
				VectorMA(ground_bestend, INSIDEUNITS_WALKEND, ground_bestnormal, lreach->end);
				lreach->traveltype = TRAVEL_WALK;
				lreach->traveltime = 1;
				lreach->next = areareachability[area1num];
				areareachability[area1num] = lreach;
				//we've got another walk reachability
				reach_walk++;
				return qtrue;
			} //end if
			// if no maximum fall height set or less than the max
			if (!aassettings.rs_maxfallheight || fabs(ground_bestdist) < aassettings.rs_maxfallheight) {
				//trace a bounding box vertically to check for solids
				VectorMA(ground_bestend, INSIDEUNITS, ground_bestnormal, ground_bestend);
				VectorCopy(ground_bestend, start);
				start[2] = ground_beststart[2];
				VectorCopy(ground_bestend, end);
				end[2] += 4;
				trace = AAS_TraceClientBBox(start, end, PRESENCE_NORMAL, -1);
				//if no solids were found
				if (!trace.startsolid && trace.fraction >= 1.0)
				{
					//the trace end point must be in the goal area
					trace.endpos[2] += 1;
					if (AAS_PointAreaNum(trace.endpos) == area2num)
					{
						//if not going through a cluster portal
						numareas = AAS_TraceAreas(start, end, areas, NULL, ARRAY_LEN(areas));
						for (i = 0; i < numareas; i++)
							if (AAS_AreaClusterPortal(areas[i]))
								break;
						if (i >= numareas)
						{
							//create a walk off ledge reachability from area1 to area2
							lreach = AAS_AllocReachability();
							if (!lreach) return qfalse;
							lreach->areanum = area2num;
							lreach->facenum = 0;
							lreach->edgenum = ground_bestarea2groundedgenum;
							VectorCopy(ground_beststart, lreach->start);
							VectorCopy(ground_bestend, lreach->end);
							lreach->traveltype = TRAVEL_WALKOFFLEDGE;
							lreach->traveltime = aassettings.rs_startwalkoffledge + fabs(ground_bestdist) * 50 / aassettings.phys_gravity;
							//if falling from too high and not falling into water
							if (!AAS_AreaSwim(area2num) && !AAS_AreaJumpPad(area2num))
							{
								if (AAS_FallDelta(ground_bestdist) > aassettings.phys_falldelta5)
								{
									lreach->traveltime += aassettings.rs_falldamage5;
								} //end if
								if (AAS_FallDelta(ground_bestdist) > aassettings.phys_falldelta10)
								{
									lreach->traveltime += aassettings.rs_falldamage10;
								} //end if
							} //end if
							lreach->next = areareachability[area1num];
							areareachability[area1num] = lreach;
							//
							reach_walkoffledge++;
							//NOTE: don't create a weapon (rl, bfg) jump reachability here
							//because it interferes with other reachabilities
							//like the ladder reachability
							return qtrue;
						} //end if
					} //end if
				} //end if
			} //end if
		} //end else
	} //end if
	return qfalse;
}