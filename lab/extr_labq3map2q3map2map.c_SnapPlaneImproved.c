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
typedef  scalar_t__ vec_t ;
typedef  int* vec3_t ;

/* Variables and functions */
 scalar_t__ DotProduct (int*,int*) ; 
 scalar_t__ Q_rint (scalar_t__) ; 
 scalar_t__ SnapNormal (int*) ; 
 int /*<<< orphan*/  VectorAdd (int*,int* const,int*) ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 scalar_t__ VectorIsOnAxis (int*) ; 
 scalar_t__ distanceEpsilon ; 

void SnapPlaneImproved( vec3_t normal, vec_t *dist, int numPoints, const vec3_t *points ){
	int i;
	vec3_t center;
	vec_t distNearestInt;

	if ( SnapNormal( normal ) ) {
		if ( numPoints > 0 ) {
			// Adjust the dist so that the provided points don't drift away.
			VectorClear( center );
			for ( i = 0; i < numPoints; i++ )
			{
				VectorAdd( center, points[i], center );
			}
			for ( i = 0; i < 3; i++ ) { center[i] = center[i] / numPoints; }
			*dist = DotProduct( normal, center );
		}
	}

	if ( VectorIsOnAxis( normal ) ) {
		// Only snap distance if the normal is an axis.  Otherwise there
		// is nothing "natural" about snapping the distance to an integer.
		distNearestInt = Q_rint( *dist );
		if ( -distanceEpsilon < *dist - distNearestInt && *dist - distNearestInt < distanceEpsilon ) {
			*dist = distNearestInt;
		}
	}
}