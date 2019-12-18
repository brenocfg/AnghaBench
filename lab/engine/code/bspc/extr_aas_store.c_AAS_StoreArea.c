#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_9__ {int aasfacenum; int planenum; int /*<<< orphan*/  faceflags; int /*<<< orphan*/ * winding; TYPE_2__* frontarea; struct TYPE_9__** next; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_10__ {int aasareanum; int /*<<< orphan*/  settings; TYPE_1__* tmpfaces; scalar_t__ invalid; struct TYPE_10__* mergedarea; } ;
typedef  TYPE_2__ tmp_area_t ;
typedef  int /*<<< orphan*/  plane_t ;
typedef  size_t aas_faceindex_t ;
struct TYPE_11__ {int backarea; int frontarea; int numedges; int firstedge; int /*<<< orphan*/  faceflags; } ;
typedef  TYPE_3__ aas_face_t ;
struct TYPE_12__ {size_t* v; } ;
typedef  TYPE_4__ aas_edge_t ;
struct TYPE_13__ {int areanum; double numfaces; scalar_t__ firstface; int /*<<< orphan*/  center; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
typedef  TYPE_5__ aas_area_t ;
struct TYPE_15__ {scalar_t__ numareas; scalar_t__ faceindexsize; size_t* faceindex; int /*<<< orphan*/ * vertexes; int /*<<< orphan*/ * edgeindex; TYPE_4__* edges; TYPE_3__* faces; TYPE_5__* areas; } ;
struct TYPE_14__ {scalar_t__ max_areas; size_t max_faces; scalar_t__ max_faceindexsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_GetFace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  AAS_StoreAreaSettings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*,...) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReverseWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 TYPE_7__ aasworld ; 
 size_t abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mapplanes ; 
 TYPE_6__ max_aas ; 
 int /*<<< orphan*/  qprintf (char*,int) ; 

int AAS_StoreArea(tmp_area_t *tmparea)
{
	int side, edgenum, i;
	plane_t *plane;
	tmp_face_t *tmpface;
	aas_area_t *aasarea;
	aas_edge_t *edge;
	aas_face_t *aasface;
	aas_faceindex_t aasfacenum;
	vec3_t facecenter;
	winding_t *w;

	//when the area is merged go to the merged area
	//FIXME: this isn't necessary anymore because the tree
	//			is refreshed after area merging
	while(tmparea->mergedarea) tmparea = tmparea->mergedarea;
	//
	if (tmparea->invalid) Error("AAS_StoreArea: tried to store invalid area");
	//if there is an aas area already stored for this tmp area
	if (tmparea->aasareanum) return -tmparea->aasareanum;
	//
	if (aasworld.numareas >= max_aas.max_areas)
	{
		Error("AAS_MAX_AREAS = %d", max_aas.max_areas);
	} //end if
	//area zero is a dummy
	if (aasworld.numareas == 0) aasworld.numareas = 1;
	//create an area from this leaf
	aasarea = &aasworld.areas[aasworld.numareas];
	aasarea->areanum = aasworld.numareas;
	aasarea->numfaces = 0;
	aasarea->firstface = aasworld.faceindexsize;
	ClearBounds(aasarea->mins, aasarea->maxs);
	VectorClear(aasarea->center);
	//
//	Log_Write("tmparea %d became aasarea %d\r\n", tmparea->areanum, aasarea->areanum);
	//store the aas area number at the tmp area
	tmparea->aasareanum = aasarea->areanum;
	//
	for (tmpface = tmparea->tmpfaces; tmpface; tmpface = tmpface->next[side])
	{
		side = tmpface->frontarea != tmparea;
		//if there's an aas face created for the tmp face already
		if (tmpface->aasfacenum)
		{
			//we're at the back of the face so use a negative index
			aasfacenum = -tmpface->aasfacenum;
#ifdef DEBUG
			if (tmpface->aasfacenum < 0 || tmpface->aasfacenum > max_aas.max_faces)
			{
				Error("AAS_CreateTree_r: face number out of range");
			} //end if
#endif //DEBUG
			aasface = &aasworld.faces[tmpface->aasfacenum];
			aasface->backarea = aasarea->areanum;
		} //end if
		else
		{
			plane = &mapplanes[tmpface->planenum ^ side];
			if (side)
			{
				w = tmpface->winding;
				tmpface->winding = ReverseWinding(tmpface->winding);
			} //end if
			if (!AAS_GetFace(tmpface->winding, plane, 0, &aasfacenum)) continue;
			if (side)
			{
				FreeWinding(tmpface->winding);
				tmpface->winding = w;
			} //end if
			aasface = &aasworld.faces[aasfacenum];
			aasface->frontarea = aasarea->areanum;
			aasface->backarea = 0;
			aasface->faceflags = tmpface->faceflags;
			//set the face number at the tmp face
			tmpface->aasfacenum = aasfacenum;
		} //end else
		//add face points to the area bounds and
		//calculate the face 'center'
		VectorClear(facecenter);
		for (edgenum = 0; edgenum < aasface->numedges; edgenum++)
		{
			edge = &aasworld.edges[abs(aasworld.edgeindex[aasface->firstedge + edgenum])];
			for (i = 0; i < 2; i++)
			{
				AddPointToBounds(aasworld.vertexes[edge->v[i]], aasarea->mins, aasarea->maxs);
				VectorAdd(aasworld.vertexes[edge->v[i]], facecenter, facecenter);
			} //end for
		} //end for
		VectorScale(facecenter, 1.0 / (aasface->numedges * 2.0), facecenter);
		//add the face 'center' to the area 'center'
		VectorAdd(aasarea->center, facecenter, aasarea->center);
		//
		if (aasworld.faceindexsize >= max_aas.max_faceindexsize)
		{
			Error("AAS_MAX_FACEINDEXSIZE = %d", max_aas.max_faceindexsize);
		} //end if
		aasworld.faceindex[aasworld.faceindexsize++] = aasfacenum;
		aasarea->numfaces++;
	} //end for
	//if the area has no faces at all (return 0, = solid leaf)
	if (!aasarea->numfaces) return 0;
	//
	VectorScale(aasarea->center, 1.0 / aasarea->numfaces, aasarea->center);
	//Log_Write("area %d center %f %f %f\r\n", aasworld.numareas,
	//				aasarea->center[0], aasarea->center[1], aasarea->center[2]);
	//store the area settings
	AAS_StoreAreaSettings(tmparea->settings);
	//
	//Log_Write("tmp area %d became aas area %d\r\n", tmpareanum, aasarea->areanum);
	qprintf("\r%6d", aasarea->areanum);
	//
	aasworld.numareas++;
	return -(aasworld.numareas - 1);
}