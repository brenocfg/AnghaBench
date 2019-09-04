#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_11__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; } ;
typedef  TYPE_3__ th_plane_t ;
struct TYPE_12__ {int numedges; TYPE_2__* edges; TYPE_1__* vertexes; } ;
struct TYPE_10__ {int* v; int /*<<< orphan*/  usercount; } ;
struct TYPE_9__ {float* v; } ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DotProduct (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TH_CreateTrianglePlanes (int*,TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ TH_IntersectTrianglePlanes (int,int,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,int /*<<< orphan*/ ) ; 
 TYPE_4__ thworld ; 

int TH_TryTriangle(int verts[3])
{
	th_plane_t planes[3], triplane;
	vec3_t t1, t2;
	float *p0, *p1, *p2;
	int i, j;

	p0 = thworld.vertexes[verts[0]].v;
	p1 = thworld.vertexes[verts[1]].v;
	p2 = thworld.vertexes[verts[2]].v;

	VectorSubtract(p0, p1, t1);
	VectorSubtract(p2, p1, t2);
	CrossProduct(t1, t2, triplane.normal);
	VectorNormalize(triplane.normal);
	triplane.dist = DotProduct(p0, triplane.normal);
	//
	TH_CreateTrianglePlanes(verts, &triplane, planes);
	//test if any existing edge intersects with this triangle
	for (i = 1; i < thworld.numedges; i++)
	{
		//if the edge is only used by triangles with tetrahedrons at both sides
		if (!thworld.edges[i].usercount) continue;
		//if one of the triangle vertexes is used by this edge
		for (j = 0; j < 3; j++)
		{
			if (verts[j] == thworld.edges[j].v[0] ||
				verts[j] == thworld.edges[j].v[1]) break;
		} //end for
		if (j < 3) continue;
		//if this edge intersects with the triangle
		if (TH_IntersectTrianglePlanes(thworld.edges[i].v[0], thworld.edges[i].v[1], &triplane, planes)) return false;
	} //end for
	return true;
}