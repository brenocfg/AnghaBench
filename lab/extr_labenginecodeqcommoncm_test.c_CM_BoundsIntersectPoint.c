#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__* vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 scalar_t__ SURFACE_CLIP_EPSILON ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean CM_BoundsIntersectPoint( const vec3_t mins, const vec3_t maxs, const vec3_t point )
{
	if (maxs[0] < point[0] - SURFACE_CLIP_EPSILON ||
		maxs[1] < point[1] - SURFACE_CLIP_EPSILON ||
		maxs[2] < point[2] - SURFACE_CLIP_EPSILON ||
		mins[0] > point[0] + SURFACE_CLIP_EPSILON ||
		mins[1] > point[1] + SURFACE_CLIP_EPSILON ||
		mins[2] > point[2] + SURFACE_CLIP_EPSILON)
	{
		return qfalse;
	}

	return qtrue;
}