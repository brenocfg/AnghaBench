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
 float DotProduct (float*,float*) ; 
 int MAX_EXPANDED_AXIS ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 float VectorLength (float*) ; 
 float VectorNormalize (float*,float*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 

__attribute__((used)) static void ExpandMaxIterations( int *maxIterations, int maxError, vec3_t a, vec3_t b, vec3_t c ){
	int i, j;
	vec3_t prev, next, mid, delta, delta2;
	float len, len2;
	int numPoints, iterations;
	vec3_t points[ MAX_EXPANDED_AXIS ];


	/* initial setup */
	numPoints = 3;
	VectorCopy( a, points[ 0 ] );
	VectorCopy( b, points[ 1 ] );
	VectorCopy( c, points[ 2 ] );

	/* subdivide */
	for ( i = 0; i + 2 < numPoints; i += 2 )
	{
		/* check subdivision limit */
		if ( numPoints + 2 >= MAX_EXPANDED_AXIS ) {
			break;
		}

		/* calculate new curve deltas */
		for ( j = 0; j < 3; j++ )
		{
			prev[ j ] = points[ i + 1 ][ j ] - points[ i ][ j ];
			next[ j ] = points[ i + 2 ][ j ] - points[ i + 1 ][ j ];
			mid[ j ] = ( points[ i ][ j ] + points[ i + 1 ][ j ] * 2.0f + points[ i + 2 ][ j ] ) * 0.25f;
		}

		/* see if this midpoint is off far enough to subdivide */
		VectorSubtract( points[ i + 1 ], mid, delta );
		len = VectorLength( delta );
		if ( len < maxError ) {
			continue;
		}

		/* subdivide */
		numPoints += 2;

		/* create new points */
		for ( j = 0; j < 3; j++ )
		{
			prev[ j ] = 0.5f * ( points[ i ][ j ] + points[ i + 1 ][ j ] );
			next[ j ] = 0.5f * ( points[ i + 1 ][ j ] + points[ i + 2 ][ j ] );
			mid[ j ] = 0.5f * ( prev[ j ] + next[ j ] );
		}

		/* push points out */
		for ( j = numPoints - 1; j > i + 3; j-- )
			VectorCopy( points[ j - 2 ], points[ j ] );

		/* insert new points */
		VectorCopy( prev, points[ i + 1 ] );
		VectorCopy( mid, points[ i + 2 ] );
		VectorCopy( next, points[ i + 3 ] );

		/* back up and recheck this set again, it may need more subdivision */
		i -= 2;
	}

	/* put the line on the curve */
	for ( i = 1; i < numPoints; i += 2 )
	{
		for ( j = 0; j < 3; j++ )
		{
			prev[ j ] = 0.5f * ( points[ i ][ j ] + points[ i + 1 ][ j ] );
			next[ j ] = 0.5f * ( points[ i ][ j ] + points[ i - 1 ][ j ] );
			points[ i ][ j ] = 0.5f * ( prev[ j ] + next[ j ] );
		}
	}

	/* eliminate linear sections */
	for ( i = 0; i + 2 < numPoints; i++ )
	{
		/* create vectors */
		VectorSubtract( points[ i + 1 ], points[ i ], delta );
		len = VectorNormalize( delta, delta );
		VectorSubtract( points[ i + 2 ], points[ i + 1 ], delta2 );
		len2 = VectorNormalize( delta2, delta2 );

		/* if either edge is degenerate, then eliminate it */
		if ( len < 0.0625f || len2 < 0.0625f || DotProduct( delta, delta2 ) >= 1.0f ) {
			for ( j = i + 1; j + 1 < numPoints; j++ )
				VectorCopy( points[ j + 1 ], points[ j ] );
			numPoints--;
			continue;
		}
	}

	/* the number of iterations is 2^(points - 1) - 1 */
	numPoints >>= 1;
	iterations = 0;
	while ( numPoints > 1 )
	{
		numPoints >>= 1;
		iterations++;
	}

	/* more? */
	if ( iterations > *maxIterations ) {
		*maxIterations = iterations;
	}
}