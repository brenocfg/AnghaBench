#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {size_t firstedge; int numedges; } ;
typedef  TYPE_1__ aas_face_t ;
struct TYPE_6__ {size_t* v; } ;
typedef  TYPE_2__ aas_edge_t ;
struct TYPE_7__ {int* edgeindex; int /*<<< orphan*/ ** vertexes; TYPE_2__* edges; } ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ aasworld ; 
 size_t abs (int) ; 

float AAS_FaceArea(aas_face_t *face)
{
	int i, edgenum, side;
	float total;
	vec_t *v;
	vec3_t d1, d2, cross;
	aas_edge_t *edge;

	edgenum = aasworld.edgeindex[face->firstedge];
	side = edgenum < 0;
	edge = &aasworld.edges[abs(edgenum)];
	v = aasworld.vertexes[edge->v[side]];

	total = 0;
	for (i = 1; i < face->numedges - 1; i++)
	{
		edgenum = aasworld.edgeindex[face->firstedge + i];
		side = edgenum < 0;
		edge = &aasworld.edges[abs(edgenum)];
		VectorSubtract(aasworld.vertexes[edge->v[side]], v, d1);
		VectorSubtract(aasworld.vertexes[edge->v[!side]], v, d2);
		CrossProduct(d1, d2, cross);
		total += 0.5 * VectorLength(cross);
	} //end for
	return total;
}