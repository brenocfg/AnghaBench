#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
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
struct TYPE_12__ {int* endpos; } ;
typedef  TYPE_1__ aas_trace_t ;
struct TYPE_13__ {int* normal; } ;
typedef  TYPE_2__ aas_plane_t ;
struct TYPE_14__ {int areanum; int facenum; size_t edgenum; int* start; int* end; int traveltime; void* next; void* traveltype; } ;
typedef  TYPE_3__ aas_lreachability_t ;
struct TYPE_15__ {int faceflags; int numedges; int firstedge; int planenum; } ;
typedef  TYPE_4__ aas_face_t ;
struct TYPE_16__ {size_t* v; } ;
typedef  TYPE_5__ aas_edge_t ;
struct TYPE_17__ {int numfaces; int firstface; } ;
typedef  TYPE_6__ aas_area_t ;
struct TYPE_19__ {float phys_jumpvel; } ;
struct TYPE_18__ {int* faceindex; int* edgeindex; int** vertexes; TYPE_2__* planes; TYPE_4__* faces; TYPE_6__* areas; TYPE_5__* edges; } ;

/* Variables and functions */
 TYPE_3__* AAS_AllocReachability () ; 
 int /*<<< orphan*/  AAS_AreaLadder (int) ; 
 float AAS_FaceArea (TYPE_4__*) ; 
 float AAS_MaxJumpHeight (float) ; 
 int AAS_PointAreaNum (int*) ; 
 int /*<<< orphan*/  AAS_ReachabilityExists (int,int) ; 
 TYPE_1__ AAS_TraceClientBBox (int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CrossProduct (int*,int*,int*) ; 
 double DotProduct (int*,int*) ; 
 int FACE_GROUND ; 
 int FACE_LADDER ; 
 int /*<<< orphan*/  PRESENCE_NORMAL ; 
 void* TRAVEL_JUMP ; 
 void* TRAVEL_LADDER ; 
 void* TRAVEL_WALKOFFLEDGE ; 
 int /*<<< orphan*/  VectorAdd (int*,int*,int*) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 int /*<<< orphan*/  VectorMA (int*,int,int*,int*) ; 
 int /*<<< orphan*/  VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorScale (int*,double,int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int*,int*) ; 
 TYPE_8__ aassettings ; 
 TYPE_7__ aasworld ; 
 size_t abs (int) ; 
 void** areareachability ; 
 double fabsf (double) ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  reach_jump ; 
 int /*<<< orphan*/  reach_ladder ; 
 int /*<<< orphan*/  reach_walkoffledge ; 

int AAS_Reachability_Ladder(int area1num, int area2num)
{
	int i, j, k, l, edge1num, edge2num, sharededgenum = 0, lowestedgenum = 0;
	int face1num, face2num, ladderface1num = 0, ladderface2num = 0;
	int ladderface1vertical, ladderface2vertical, firstv;
	float face1area, face2area, bestface1area = -9999, bestface2area = -9999;
	float phys_jumpvel, maxjumpheight;
	vec3_t area1point, area2point, v1, v2, up = {0, 0, 1};
	vec3_t mid, lowestpoint = {0, 0}, start, end, sharededgevec, dir;
	aas_area_t *area1, *area2;
	aas_face_t *face1, *face2, *ladderface1 = NULL, *ladderface2 = NULL;
	aas_plane_t *plane1, *plane2;
	aas_edge_t *sharededge, *edge1;
	aas_lreachability_t *lreach;
	aas_trace_t trace;

	if (!AAS_AreaLadder(area1num) || !AAS_AreaLadder(area2num)) return qfalse;
	//
	phys_jumpvel = aassettings.phys_jumpvel;
	//maximum height a player can jump with the given initial z velocity
	maxjumpheight = AAS_MaxJumpHeight(phys_jumpvel);

	area1 = &aasworld.areas[area1num];
	area2 = &aasworld.areas[area2num];
	
	for (i = 0; i < area1->numfaces; i++)
	{
		face1num = aasworld.faceindex[area1->firstface + i];
		face1 = &aasworld.faces[abs(face1num)];
		//if not a ladder face
		if (!(face1->faceflags & FACE_LADDER)) continue;
		//
		for (j = 0; j < area2->numfaces; j++)
		{
			face2num = aasworld.faceindex[area2->firstface + j];
			face2 = &aasworld.faces[abs(face2num)];
			//if not a ladder face
			if (!(face2->faceflags & FACE_LADDER)) continue;
			//check if the faces share an edge
			for (k = 0; k < face1->numedges; k++)
			{
				edge1num = aasworld.edgeindex[face1->firstedge + k];
				for (l = 0; l < face2->numedges; l++)
				{
					edge2num = aasworld.edgeindex[face2->firstedge + l];
					if (abs(edge1num) == abs(edge2num))
					{
						//get the face with the largest area
						face1area = AAS_FaceArea(face1);
						face2area = AAS_FaceArea(face2);
						if (face1area > bestface1area && face2area > bestface2area)
						{
							bestface1area = face1area;
							bestface2area = face2area;
							ladderface1 = face1;
							ladderface2 = face2;
							ladderface1num = face1num;
							ladderface2num = face2num;
							sharededgenum = edge1num;
						} //end if
						break;
					} //end if
				} //end for
				if (l != face2->numedges) break;
			} //end for
		} //end for
	} //end for
	//
	if (ladderface1 && ladderface2)
	{
		//get the middle of the shared edge
		sharededge = &aasworld.edges[abs(sharededgenum)];
		firstv = sharededgenum < 0;
		//
		VectorCopy(aasworld.vertexes[sharededge->v[firstv]], v1);
		VectorCopy(aasworld.vertexes[sharededge->v[!firstv]], v2);
		VectorAdd(v1, v2, area1point);
		VectorScale(area1point, 0.5, area1point);
		VectorCopy(area1point, area2point);
		//
		//if the face plane in area 1 is pretty much vertical
		plane1 = &aasworld.planes[ladderface1->planenum ^ (ladderface1num < 0)];
		plane2 = &aasworld.planes[ladderface2->planenum ^ (ladderface2num < 0)];
		//
		//get the points really into the areas
		VectorSubtract(v2, v1, sharededgevec);
		CrossProduct(plane1->normal, sharededgevec, dir);
		VectorNormalize(dir);
		//NOTE: 32 because that's larger than 16 (bot bbox x,y)
		VectorMA(area1point, -32, dir, area1point);
		VectorMA(area2point, 32, dir, area2point);
		//
		ladderface1vertical = fabsf(DotProduct(plane1->normal, up)) < 0.1;
		ladderface2vertical = fabsf(DotProduct(plane2->normal, up)) < 0.1;
		//there's only reachability between vertical ladder faces
		if (!ladderface1vertical && !ladderface2vertical) return qfalse;
		//if both vertical ladder faces
		if (ladderface1vertical && ladderface2vertical
					//and the ladder faces do not make a sharp corner
					&& DotProduct(plane1->normal, plane2->normal) > 0.7
					//and the shared edge is not too vertical
					&& fabsf(DotProduct(sharededgevec, up)) < 0.7)
		{
			//create a new reachability link
			lreach = AAS_AllocReachability();
			if (!lreach) return qfalse;
			lreach->areanum = area2num;
			lreach->facenum = ladderface1num;
			lreach->edgenum = abs(sharededgenum);
			VectorCopy(area1point, lreach->start);
			//VectorCopy(area2point, lreach->end);
			VectorMA(area2point, -3, plane1->normal, lreach->end);
			lreach->traveltype = TRAVEL_LADDER;
			lreach->traveltime = 10;
			lreach->next = areareachability[area1num];
			areareachability[area1num] = lreach;
			//
			reach_ladder++;
			//create a new reachability link
			lreach = AAS_AllocReachability();
			if (!lreach) return qfalse;
			lreach->areanum = area1num;
			lreach->facenum = ladderface2num;
			lreach->edgenum = abs(sharededgenum);
			VectorCopy(area2point, lreach->start);
			//VectorCopy(area1point, lreach->end);
			VectorMA(area1point, -3, plane1->normal, lreach->end);
			lreach->traveltype = TRAVEL_LADDER;
			lreach->traveltime = 10;
			lreach->next = areareachability[area2num];
			areareachability[area2num] = lreach;
			//
			reach_ladder++;
			//
			return qtrue;
		} //end if
		//if the second ladder face is also a ground face
		//create ladder end (just ladder) reachability and
		//walk off a ladder (ledge) reachability
		if (ladderface1vertical && (ladderface2->faceflags & FACE_GROUND))
		{
			//create a new reachability link
			lreach = AAS_AllocReachability();
			if (!lreach) return qfalse;
			lreach->areanum = area2num;
			lreach->facenum = ladderface1num;
			lreach->edgenum = abs(sharededgenum);
			VectorCopy(area1point, lreach->start);
			VectorCopy(area2point, lreach->end);
			lreach->end[2] += 16;
			VectorMA(lreach->end, -15, plane1->normal, lreach->end);
			lreach->traveltype = TRAVEL_LADDER;
			lreach->traveltime = 10;
			lreach->next = areareachability[area1num];
			areareachability[area1num] = lreach;
			//
			reach_ladder++;
			//create a new reachability link
			lreach = AAS_AllocReachability();
			if (!lreach) return qfalse;
			lreach->areanum = area1num;
			lreach->facenum = ladderface2num;
			lreach->edgenum = abs(sharededgenum);
			VectorCopy(area2point, lreach->start);
			VectorCopy(area1point, lreach->end);
			lreach->traveltype = TRAVEL_WALKOFFLEDGE;
			lreach->traveltime = 10;
			lreach->next = areareachability[area2num];
			areareachability[area2num] = lreach;
			//
			reach_walkoffledge++;
			//
			return qtrue;
		} //end if
		//
		if (ladderface1vertical)
		{
			//find lowest edge of the ladder face
			lowestpoint[2] = 99999;
			for (i = 0; i < ladderface1->numedges; i++)
			{
				edge1num = abs(aasworld.edgeindex[ladderface1->firstedge + i]);
				edge1 = &aasworld.edges[edge1num];
				//
				VectorCopy(aasworld.vertexes[edge1->v[0]], v1);
				VectorCopy(aasworld.vertexes[edge1->v[1]], v2);
				//
				VectorAdd(v1, v2, mid);
				VectorScale(mid, 0.5, mid);
				//
				if (mid[2] < lowestpoint[2])
				{
					VectorCopy(mid, lowestpoint);
					lowestedgenum = edge1num;
				} //end if
			} //end for
			//
			plane1 = &aasworld.planes[ladderface1->planenum];
			//trace down in the middle of this edge
			VectorMA(lowestpoint, 5, plane1->normal, start);
			VectorCopy(start, end);
			start[2] += 5;
			end[2] -= 100;
			//trace without entity collision
			trace = AAS_TraceClientBBox(start, end, PRESENCE_NORMAL, -1);
			//
			//
#ifdef REACH_DEBUG
			if (trace.startsolid)
			{
				Log_Write("trace from area %d started in solid\r\n", area1num);
			} //end if
#endif //REACH_DEBUG
			//
			trace.endpos[2] += 1;
			area2num = AAS_PointAreaNum(trace.endpos);
			//
			area2 = &aasworld.areas[area2num];
			for (i = 0; i < area2->numfaces; i++)
			{
				face2num = aasworld.faceindex[area2->firstface + i];
				face2 = &aasworld.faces[abs(face2num)];
				//
				if (face2->faceflags & FACE_LADDER)
				{
					plane2 = &aasworld.planes[face2->planenum];
					if (fabsf(DotProduct(plane2->normal, up)) < 0.1) break;
				} //end if
			} //end for
			//if from another area without vertical ladder faces
			if (i >= area2->numfaces && area2num != area1num &&
						//the reachabilities shouldn't exist already
						!AAS_ReachabilityExists(area1num, area2num) &&
						!AAS_ReachabilityExists(area2num, area1num))
			{
				//if the height is jumpable
				if (start[2] - trace.endpos[2] < maxjumpheight)
				{
					//create a new reachability link
					lreach = AAS_AllocReachability();
					if (!lreach) return qfalse;
					lreach->areanum = area2num;
					lreach->facenum = ladderface1num;
					lreach->edgenum = lowestedgenum;
					VectorCopy(lowestpoint, lreach->start);
					VectorCopy(trace.endpos, lreach->end);
					lreach->traveltype = TRAVEL_LADDER;
					lreach->traveltime = 10;
					lreach->next = areareachability[area1num];
					areareachability[area1num] = lreach;
					//
					reach_ladder++;
					//create a new reachability link
					lreach = AAS_AllocReachability();
					if (!lreach) return qfalse;
					lreach->areanum = area1num;
					lreach->facenum = ladderface1num;
					lreach->edgenum = lowestedgenum;
					VectorCopy(trace.endpos, lreach->start);
					//get the end point a little bit into the ladder
					VectorMA(lowestpoint, -5, plane1->normal, lreach->end);
					//get the end point a little higher
					lreach->end[2] += 10;
					lreach->traveltype = TRAVEL_JUMP;
					lreach->traveltime = 10;
					lreach->next = areareachability[area2num];
					areareachability[area2num] = lreach;
					//
					reach_jump++;	
					//
					return qtrue;
#ifdef REACH_DEBUG
					Log_Write("jump up to ladder reach between %d and %d\r\n", area2num, area1num);
#endif //REACH_DEBUG
				} //end if
#ifdef REACH_DEBUG
				else Log_Write("jump too high between area %d and %d\r\n", area2num, area1num);
#endif //REACH_DEBUG
			} //end if
			/*//if slime or lava below the ladder
			//try jump reachability from far towards the ladder
			if (aasworld.areasettings[area2num].contents & (AREACONTENTS_SLIME
													| AREACONTENTS_LAVA))
			{
				for (i = 20; i <= 120; i += 20)
				{
					//trace down in the middle of this edge
					VectorMA(lowestpoint, i, plane1->normal, start);
					VectorCopy(start, end);
					start[2] += 5;
					end[2] -= 100;
					//trace without entity collision
					trace = AAS_TraceClientBBox(start, end, PRESENCE_NORMAL, -1);
					//
					if (trace.startsolid) break;
					trace.endpos[2] += 1;
					area2num = AAS_PointAreaNum(trace.endpos);
					if (area2num == area1num) continue;
					//
					if (start[2] - trace.endpos[2] > maxjumpheight) continue;
					if (aasworld.areasettings[area2num].contents & (AREACONTENTS_SLIME
												| AREACONTENTS_LAVA)) continue;
					//
					//create a new reachability link
					lreach = AAS_AllocReachability();
					if (!lreach) return qfalse;
					lreach->areanum = area1num;
					lreach->facenum = ladderface1num;
					lreach->edgenum = lowestedgenum;
					VectorCopy(trace.endpos, lreach->start);
					VectorCopy(lowestpoint, lreach->end);
					lreach->end[2] += 5;
					lreach->traveltype = TRAVEL_JUMP;
					lreach->traveltime = 10;
					lreach->next = areareachability[area2num];
					areareachability[area2num] = lreach;
					//
					reach_jump++;
					//
					Log_Write("jump far to ladder reach between %d and %d\r\n", area2num, area1num);
					//
					break;
				} //end for
			} //end if*/
		} //end if
	} //end if
	return qfalse;
}