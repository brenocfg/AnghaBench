#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vec_t ;
struct TYPE_4__ {scalar_t__ radius; scalar_t__* extents; int /*<<< orphan*/  origin; } ;
struct TYPE_5__ {int /*<<< orphan*/ * axes; TYPE_1__ aabb; } ;
typedef  TYPE_2__ bbox_t ;

/* Variables and functions */
 scalar_t__ DotProduct (scalar_t__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ fabs (scalar_t__) ; 

int bbox_intersect_plane( const bbox_t *bbox, const vec_t* plane ){
	vec_t fDist, fIntersect;

	// calc distance of origin from plane
	fDist = DotProduct( plane, bbox->aabb.origin ) + plane[3];

	// trivial accept/reject using bounding sphere
	if ( fabs( fDist ) > bbox->aabb.radius ) {
		if ( fDist < 0 ) {
			return 2; // totally inside
		}
		else{
			return 0; // totally outside
		}
	}

	// calc extents distance relative to plane normal
	fIntersect = (vec_t)( fabs( bbox->aabb.extents[0] * DotProduct( plane, bbox->axes[0] ) )
						  + fabs( bbox->aabb.extents[1] * DotProduct( plane, bbox->axes[1] ) )
						  + fabs( bbox->aabb.extents[2] * DotProduct( plane, bbox->axes[2] ) ) );
	// accept if origin is less than this distance
	if ( fabs( fDist ) < fIntersect ) {
		return 1;                         // partially inside
	}
	else if ( fDist < 0 ) {
		return 2;               // totally inside
	}
	return 0; // totally outside
}