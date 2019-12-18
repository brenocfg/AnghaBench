#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  float vec_t ;
typedef  float* vec3_t ;
struct TYPE_5__ {float* origin; float* direction; } ;
typedef  TYPE_1__ ray_t ;
struct TYPE_6__ {float const* origin; float const* extents; } ;
typedef  TYPE_2__ aabb_t ;

/* Variables and functions */
 float DotProduct (float*,float const*) ; 
 char LEFT ; 
 char MIDDLE ; 
 int NUMDIM ; 
 char RIGHT ; 
 int /*<<< orphan*/  VectorSubtract (float*,float const*,float*) ; 
 double fabs (float) ; 

int aabb_intersect_ray( const aabb_t *aabb, const ray_t *ray, vec_t *dist ){
	int inside = 1;
	char quadrant[NUMDIM];
	register int i;
	int whichPlane;
	double maxT[NUMDIM];
	double candidatePlane[NUMDIM];
	vec3_t coord, segment;

	const float *origin = ray->origin;
	const float *direction = ray->direction;

	/* Find candidate planes; this loop can be avoided if
	   rays cast all from the eye(assume perpsective view) */
	for ( i = 0; i < NUMDIM; i++ )
	{
		if ( origin[i] < ( aabb->origin[i] - aabb->extents[i] ) ) {
			quadrant[i] = LEFT;
			candidatePlane[i] = ( aabb->origin[i] - aabb->extents[i] );
			inside = 0;
		}
		else if ( origin[i] > ( aabb->origin[i] + aabb->extents[i] ) ) {
			quadrant[i] = RIGHT;
			candidatePlane[i] = ( aabb->origin[i] + aabb->extents[i] );
			inside = 0;
		}
		else
		{
			quadrant[i] = MIDDLE;
		}
	}

	/* Ray origin inside bounding box */
	if ( inside == 1 ) {
		*dist = 0.0f;
		return 1;
	}


	/* Calculate T distances to candidate planes */
	for ( i = 0; i < NUMDIM; i++ )
	{
		if ( quadrant[i] != MIDDLE && direction[i] != 0. ) {
			maxT[i] = ( candidatePlane[i] - origin[i] ) / direction[i];
		}
		else{
			maxT[i] = -1.;
		}
	}

	/* Get largest of the maxT's for final choice of intersection */
	whichPlane = 0;
	for ( i = 1; i < NUMDIM; i++ )
		if ( maxT[whichPlane] < maxT[i] ) {
			whichPlane = i;
		}

	/* Check final candidate actually inside box */
	if ( maxT[whichPlane] < 0. ) {
		return 0;
	}
	for ( i = 0; i < NUMDIM; i++ )
	{
		if ( whichPlane != i ) {
			coord[i] = (vec_t)( origin[i] + maxT[whichPlane] * direction[i] );
			if ( fabs( coord[i] - aabb->origin[i] ) > aabb->extents[i] ) {
				return 0;
			}
		}
		else
		{
			coord[i] = (vec_t)candidatePlane[i];
		}
	}

	VectorSubtract( coord, origin, segment );
	*dist = DotProduct( segment, direction );

	return 1;               /* ray hits box */
}