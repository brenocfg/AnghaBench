#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_6__ {size_t planenum; int /*<<< orphan*/  surf; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_7__ {float dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_8__ {int numsides; TYPE_1__* original_sides; } ;
typedef  TYPE_3__ mapbrush_t ;

/* Variables and functions */
 scalar_t__ BoxOriginDistanceFromPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CapsuleOriginDistanceFromPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t FindFloatPlane (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  SFL_BEVEL ; 
 int /*<<< orphan*/  SURF_SKIP ; 
 scalar_t__ capsule_collision ; 
 TYPE_2__* mapplanes ; 

void AAS_ExpandMapBrush(mapbrush_t *brush, vec3_t mins, vec3_t maxs)
{
	int sn;
	float dist;
	side_t *s;
	plane_t *plane;

	for (sn = 0; sn < brush->numsides; sn++)
	{
		s = brush->original_sides + sn;
		plane = &mapplanes[s->planenum];
		dist = plane->dist;
		if (capsule_collision) {
			dist += CapsuleOriginDistanceFromPlane(plane->normal, mins, maxs);
		}
		else {
			dist += BoxOriginDistanceFromPlane(plane->normal, mins, maxs, 0);
		}
		s->planenum = FindFloatPlane(plane->normal, dist);
		//the side isn't a bevel after expanding
		s->flags &= ~SFL_BEVEL;
		//don't skip the surface
		s->surf &= ~SURF_SKIP;
		//make sure the texinfo is not TEXINFO_NODE
		//when player clip contents brushes are read from the bsp tree
		//they have the texinfo field set to TEXINFO_NODE
		//s->texinfo = 0;
	} //end for
}