#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int qboolean ;
struct TYPE_10__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_11__ {int firstedge; int numedges; scalar_t__ backarea; scalar_t__ frontarea; scalar_t__ faceflags; int /*<<< orphan*/  planenum; } ;
typedef  TYPE_3__ aas_face_t ;
struct TYPE_13__ {int numfaces; int edgeindexsize; int* edgeindex; TYPE_3__* faces; } ;
struct TYPE_12__ {int max_faces; int max_edgeindexsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_GetEdge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  AAS_GetPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Error (char*,int) ; 
 int /*<<< orphan*/  Log_Write (char*,size_t,...) ; 
 TYPE_6__ aasworld ; 
 TYPE_5__ max_aas ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ verbose ; 

qboolean AAS_GetFace(winding_t *w, plane_t *p, int side, int *facenum)
{
	int edgenum, i, j;
	aas_face_t *face;

	//face zero is a dummy, because of the face index with negative numbers
	if (aasworld.numfaces == 0) aasworld.numfaces = 1;

	if (aasworld.numfaces >= max_aas.max_faces)
	{
		Error("AAS_MAX_FACES = %d", max_aas.max_faces);
	} //end if
	face = &aasworld.faces[aasworld.numfaces];
	AAS_GetPlane(p->normal, p->dist, &face->planenum);
	face->faceflags = 0;
	face->firstedge = aasworld.edgeindexsize;
	face->frontarea = 0;
	face->backarea = 0;
	face->numedges = 0;
	for (i = 0; i < w->numpoints; i++)
	{
		if (aasworld.edgeindexsize >= max_aas.max_edgeindexsize)
		{
			Error("AAS_MAX_EDGEINDEXSIZE = %d", max_aas.max_edgeindexsize);
		} //end if
		j = (i+1) % w->numpoints;
		AAS_GetEdge(w->p[i], w->p[j], &edgenum);
		//if the edge wasn't degenerate
		if (edgenum)
		{
			aasworld.edgeindex[aasworld.edgeindexsize++] = edgenum;
			face->numedges++;
		} //end if
		else if (verbose)
		{
			Log_Write("AAS_GetFace: face %d had degenerate edge %d-%d\r\n",
														aasworld.numfaces, i, j);
		} //end else
	} //end for
	if (face->numedges < 1
#ifdef NOTHREEVERTEXFACES
		|| face->numedges < 3
#endif //NOTHREEVERTEXFACES
		)
	{
		memset(&aasworld.faces[aasworld.numfaces], 0, sizeof(aas_face_t));
		Log_Write("AAS_GetFace: face %d was tiny\r\n", aasworld.numfaces);
		return false;
	} //end if
	*facenum = aasworld.numfaces;
	aasworld.numfaces++;
	return true;
}