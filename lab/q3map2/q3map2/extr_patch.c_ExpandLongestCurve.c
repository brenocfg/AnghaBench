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
typedef  float* vec3_t ;

/* Variables and functions */
 int APPROX_SUBDIVISION ; 
 float DotProduct (float*,float*) ; 
 int /*<<< orphan*/  VectorAdd (float*,float*,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 scalar_t__ VectorLength (float*) ; 
 float VectorNormalize (float*,float*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 

__attribute__((used)) static void ExpandLongestCurve( float *longestCurve, vec3_t a, vec3_t b, vec3_t c ){
	int i;
	float t, len;
	vec3_t ab, bc, ac, pt, last, delta;


	/* calc vectors */
	VectorSubtract( b, a, ab );
	if ( VectorNormalize( ab, ab ) < 0.125f ) {
		return;
	}
	VectorSubtract( c, b, bc );
	if ( VectorNormalize( bc, bc ) < 0.125f ) {
		return;
	}
	VectorSubtract( c, a, ac );
	if ( VectorNormalize( ac, ac ) < 0.125f ) {
		return;
	}

	/* if all 3 vectors are the same direction, then this edge is linear, so we ignore it */
	if ( DotProduct( ab, bc ) > 0.99f && DotProduct( ab, ac ) > 0.99f ) {
		return;
	}

	/* recalculate vectors */
	VectorSubtract( b, a, ab );
	VectorSubtract( c, b, bc );

	/* determine length */
	VectorCopy( a, last );
	for ( i = 0, len = 0.0f, t = 0.0f; i < APPROX_SUBDIVISION; i++, t += ( 1.0f / APPROX_SUBDIVISION ) )
	{
		/* calculate delta */
		delta[ 0 ] = ( ( 1.0f - t ) * ab[ 0 ] ) + ( t * bc[ 0 ] );
		delta[ 1 ] = ( ( 1.0f - t ) * ab[ 1 ] ) + ( t * bc[ 1 ] );
		delta[ 2 ] = ( ( 1.0f - t ) * ab[ 2 ] ) + ( t * bc[ 2 ] );

		/* add to first point and calculate pt-pt delta */
		VectorAdd( a, delta, pt );
		VectorSubtract( pt, last, delta );

		/* add it to length and store last point */
		len += VectorLength( delta );
		VectorCopy( pt, last );
	}

	/* longer? */
	if ( len > *longestCurve ) {
		*longestCurve = len;
	}
}