#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {int numedges; int firstedge; } ;
typedef  TYPE_1__ aas_face_t ;
struct TYPE_6__ {size_t* v; } ;
typedef  TYPE_2__ aas_edge_t ;
struct TYPE_8__ {int numfaces; int* edgeindex; int /*<<< orphan*/ * vertexes; TYPE_2__* edges; TYPE_1__* faces; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_ShowPolygon (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ aasworld ; 
 size_t abs (int) ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

void AAS_ShowFacePolygon(int facenum, int color, int flip)
{
	int i, edgenum, numpoints;
	vec3_t points[128];
	aas_edge_t *edge;
	aas_face_t *face;

	//check if face number is in range
	if (facenum >= aasworld.numfaces)
	{
		botimport.Print(PRT_ERROR, "facenum %d out of range\n", facenum);
	} //end if
	face = &aasworld.faces[facenum];
	//walk through the edges of the face
	numpoints = 0;
	if (flip)
	{
		for (i = face->numedges-1; i >= 0; i--)
		{
			//edge number
			edgenum = aasworld.edgeindex[face->firstedge + i];
			edge = &aasworld.edges[abs(edgenum)];
			VectorCopy(aasworld.vertexes[edge->v[edgenum < 0]], points[numpoints]);
			numpoints++;
		} //end for
	} //end if
	else
	{
		for (i = 0; i < face->numedges; i++)
		{
			//edge number
			edgenum = aasworld.edgeindex[face->firstedge + i];
			edge = &aasworld.edges[abs(edgenum)];
			VectorCopy(aasworld.vertexes[edge->v[edgenum < 0]], points[numpoints]);
			numpoints++;
		} //end for
	} //end else
	AAS_ShowPolygon(color, numpoints, points);
}