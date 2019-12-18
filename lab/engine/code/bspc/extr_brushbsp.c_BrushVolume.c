#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ winding_t ;
typedef  int vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_10__ {int dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ plane_t ;
struct TYPE_11__ {int numsides; TYPE_1__* sides; } ;
typedef  TYPE_4__ bspbrush_t ;
struct TYPE_8__ {size_t planenum; TYPE_2__* winding; } ;

/* Variables and functions */
 int DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WindingArea (TYPE_2__*) ; 
 TYPE_3__* mapplanes ; 

vec_t BrushVolume (bspbrush_t *brush)
{
	int i;
	winding_t *w;
	vec3_t corner;
	vec_t d, area, volume;
	plane_t *plane;

	if (!brush) return 0;

	// grab the first valid point as the corner
	w = NULL;
	for (i = 0; i < brush->numsides; i++)
	{
		w = brush->sides[i].winding;
		if (w) break;
	} //end for
	if (!w) return 0;
	VectorCopy (w->p[0], corner);

	// make tetrahedrons to all other faces
	volume = 0;
	for ( ; i < brush->numsides; i++)
	{
		w = brush->sides[i].winding;
		if (!w) continue;
		plane = &mapplanes[brush->sides[i].planenum];
		d = -(DotProduct (corner, plane->normal) - plane->dist);
		area = WindingArea(w);
		volume += d * area;
	} //end for

	volume /= 3;
	return volume;
}