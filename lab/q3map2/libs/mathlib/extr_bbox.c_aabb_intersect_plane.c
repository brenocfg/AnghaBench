#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  float vec_t ;
struct TYPE_3__ {float radius; float const* extents; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ aabb_t ;

/* Variables and functions */
 float const DotProduct (float const*,int /*<<< orphan*/ ) ; 
 float fabs (float const) ; 

int aabb_intersect_plane( const aabb_t *aabb, const float *plane ){
	float fDist, fIntersect;

	// calc distance of origin from plane
	fDist = DotProduct( plane, aabb->origin ) + plane[3];

	// trivial accept/reject using bounding sphere
	if ( fabs( fDist ) > aabb->radius ) {
		if ( fDist < 0 ) {
			return 2; // totally inside
		}
		else{
			return 0; // totally outside
		}
	}

	// calc extents distance relative to plane normal
	fIntersect = (vec_t)( fabs( plane[0] * aabb->extents[0] ) + fabs( plane[1] * aabb->extents[1] ) + fabs( plane[2] * aabb->extents[2] ) );
	// accept if origin is less than or equal to this distance
	if ( fabs( fDist ) < fIntersect ) {
		return 1;                         // partially inside
	}
	else if ( fDist < 0 ) {
		return 2;               // totally inside
	}
	return 0; // totally outside
}