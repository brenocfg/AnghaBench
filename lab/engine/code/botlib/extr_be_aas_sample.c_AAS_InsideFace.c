#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {int numedges; int firstedge; } ;
typedef  TYPE_1__ aas_face_t ;
struct TYPE_7__ {size_t* v; } ;
typedef  TYPE_2__ aas_edge_t ;
struct TYPE_9__ {int* edgeindex; int /*<<< orphan*/ * vertexes; TYPE_2__* edges; int /*<<< orphan*/  loaded; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_OrthogonalToVectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ aasworld ; 
 size_t abs (int) ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

qboolean AAS_InsideFace(aas_face_t *face, vec3_t pnormal, vec3_t point, float epsilon)
{
	int i, firstvertex, edgenum;
	vec3_t v0;
	vec3_t edgevec, pointvec, sepnormal;
	aas_edge_t *edge;
#ifdef AAS_SAMPLE_DEBUG
	int lastvertex = 0;
#endif //AAS_SAMPLE_DEBUG

	if (!aasworld.loaded) return qfalse;

	for (i = 0; i < face->numedges; i++)
	{
		edgenum = aasworld.edgeindex[face->firstedge + i];
		edge = &aasworld.edges[abs(edgenum)];
		//get the first vertex of the edge
		firstvertex = edgenum < 0;
		VectorCopy(aasworld.vertexes[edge->v[firstvertex]], v0);
		//edge vector
		VectorSubtract(aasworld.vertexes[edge->v[!firstvertex]], v0, edgevec);
		//
#ifdef AAS_SAMPLE_DEBUG
		if (lastvertex && lastvertex != edge->v[firstvertex])
		{
			botimport.Print(PRT_MESSAGE, "winding not counter clockwise\n");
		} //end if
		lastvertex = edge->v[!firstvertex];
#endif //AAS_SAMPLE_DEBUG
		//vector from first edge point to point possible in face
		VectorSubtract(point, v0, pointvec);
		//get a vector pointing inside the face orthogonal to both the
		//edge vector and the normal vector of the plane the face is in
		//this vector defines a plane through the origin (first vertex of
		//edge) and through both the edge vector and the normal vector
		//of the plane
		AAS_OrthogonalToVectors(edgevec, pnormal, sepnormal);
		//check on which side of the above plane the point is
		//this is done by checking the sign of the dot product of the
		//vector orthogonal vector from above and the vector from the
		//origin (first vertex of edge) to the point 
		//if the dotproduct is smaller than zero the point is outside the face
		if (DotProduct(pointvec, sepnormal) < -epsilon) return qfalse;
	} //end for
	return qtrue;
}