#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* edges; size_t planenum; int /*<<< orphan*/  planes; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; scalar_t__ back; scalar_t__ front; } ;
typedef  TYPE_2__ th_triangle_t ;
typedef  int /*<<< orphan*/  th_plane_t ;
struct TYPE_6__ {int numtriangles; int /*<<< orphan*/ * planes; TYPE_1__* edges; TYPE_2__* triangles; } ;
struct TYPE_4__ {int* v; } ;

/* Variables and functions */
 scalar_t__ TH_FindEdge (int,int) ; 
 scalar_t__ TH_IntersectTrianglePlanes (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TH_OutsideBoundingBox (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t abs (scalar_t__) ; 
 TYPE_3__ thworld ; 

int TH_TryEdge(int v1, int v2)
{
	int i, j, v;
	th_plane_t *plane;
	th_triangle_t *tri;

	//if the edge already exists it must be valid
	if (TH_FindEdge(v1, v2)) return true;
	//test the edge with all existing triangles
	for (i = 1; i < thworld.numtriangles; i++)
	{
		tri = &thworld.triangles[i];
		//if triangle is enclosed by two tetrahedrons we don't have to test it
		//because the edge always has to go through another triangle of those
		//tetrahedrons first to reach the enclosed triangle
		if (tri->front && tri->back) continue;
		//if the edges is totally outside the triangle bounding box
		if (TH_OutsideBoundingBox(v1, v2, tri->mins, tri->maxs)) continue;
		//if one of the edge vertexes is used by this triangle
		for (j = 0; j < 3; j++)
		{
			v = thworld.edges[abs(tri->edges[j])].v[tri->edges[j] < 0];
			if (v == v1 || v == v2) break;
		} //end for
		if (j < 3) continue;
		//get the triangle plane
		plane = &thworld.planes[tri->planenum];
		//if the edge intersects with a triangle then it's not valid
		if (TH_IntersectTrianglePlanes(v1, v2, plane, tri->planes)) return false;
	} //end for
	return true;
}