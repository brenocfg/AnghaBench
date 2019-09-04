#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
typedef  int /*<<< orphan*/  vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_7__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; } ;
typedef  TYPE_1__ hl_dplane_t ;
struct TYPE_8__ {size_t planenum; int numedges; int firstedge; scalar_t__ side; } ;
typedef  TYPE_2__ hl_dface_t ;
struct TYPE_10__ {size_t* v; } ;
struct TYPE_9__ {int /*<<< orphan*/ * point; } ;

/* Variables and functions */
 int /*<<< orphan*/  ChopWindingInPlace (int /*<<< orphan*/ **,int /*<<< orphan*/ ,float,double) ; 
 int /*<<< orphan*/ * CopyWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorNegate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 float WindingArea (int /*<<< orphan*/ *) ; 
 size_t abs (int) ; 
 TYPE_5__* hl_dedges ; 
 int /*<<< orphan*/ * hl_dplanes ; 
 int* hl_dsurfedges ; 
 TYPE_4__* hl_dvertexes ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

float HL_FaceOnWinding(hl_dface_t *face, winding_t *winding)
{
	int i, edgenum, side;
	float dist, area;
	hl_dplane_t plane;
	vec_t *v1, *v2;
	vec3_t normal, edgevec;
	winding_t *w;

	//
	w = CopyWinding(winding);
	memcpy(&plane, &hl_dplanes[face->planenum], sizeof(hl_dplane_t));
	//check on which side of the plane the face is
	if (face->side)
	{
		VectorNegate(plane.normal, plane.normal);
		plane.dist = -plane.dist;
	} //end if
	for (i = 0; i < face->numedges && w; i++)
	{
		//get the first and second vertex of the edge
		edgenum = hl_dsurfedges[face->firstedge + i];
		side = edgenum > 0;
		//if the face plane is flipped
		v1 = hl_dvertexes[hl_dedges[abs(edgenum)].v[side]].point;
		v2 = hl_dvertexes[hl_dedges[abs(edgenum)].v[!side]].point;
		//create a plane through the edge vector, orthogonal to the face plane
		//and with the normal vector pointing out of the face
		VectorSubtract(v1, v2, edgevec);
		CrossProduct(edgevec, plane.normal, normal);
		VectorNormalize(normal);
		dist = DotProduct(normal, v1);
		//
		ChopWindingInPlace(&w, normal, dist, 0.9); //CLIP_EPSILON
	} //end for
	if (w)
	{
		area = WindingArea(w);
		FreeWinding(w);
		return area;
	} //end if
	return 0;
}