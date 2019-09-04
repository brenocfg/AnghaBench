#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numpoints; int** p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DotProduct (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*,...) ; 
 int MAX_WORLD_COORD ; 
 int MIN_WORLD_COORD ; 
 int ON_EPSILON ; 
 int VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int*,int /*<<< orphan*/ ) ; 
 int WindingArea (TYPE_1__*) ; 
 int /*<<< orphan*/  WindingPlane (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

void CheckWinding( winding_t *w ){
	int i, j;
	vec_t   *p1, *p2;
	vec_t d, edgedist;
	vec3_t dir, edgenormal, facenormal;
	vec_t area;
	vec_t facedist;

	if ( w->numpoints < 3 ) {
		Error( "CheckWinding: %i points",w->numpoints );
	}

	area = WindingArea( w );
	if ( area < 1 ) {
		Error( "CheckWinding: %f area", area );
	}

	WindingPlane( w, facenormal, &facedist );

	for ( i = 0 ; i < w->numpoints ; i++ )
	{
		p1 = w->p[i];

		for ( j = 0 ; j < 3 ; j++ )
			if ( p1[j] > MAX_WORLD_COORD || p1[j] < MIN_WORLD_COORD ) {
				Error( "CheckFace: MAX_WORLD_COORD exceeded: %f",p1[j] );
			}

		j = i + 1 == w->numpoints ? 0 : i + 1;

		// check the point is on the face plane
		d = DotProduct( p1, facenormal ) - facedist;
		if ( d < -ON_EPSILON || d > ON_EPSILON ) {
			Error( "CheckWinding: point off plane" );
		}

		// check the edge isnt degenerate
		p2 = w->p[j];
		VectorSubtract( p2, p1, dir );

		if ( VectorLength( dir ) < ON_EPSILON ) {
			Error( "CheckWinding: degenerate edge" );
		}

		CrossProduct( facenormal, dir, edgenormal );
		VectorNormalize( edgenormal, edgenormal );
		edgedist = DotProduct( p1, edgenormal );
		edgedist += ON_EPSILON;

		// all other points must be on front side
		for ( j = 0 ; j < w->numpoints ; j++ )
		{
			if ( j == i ) {
				continue;
			}
			d = DotProduct( w->p[j], edgenormal );
			if ( d > edgedist ) {
				Error( "CheckWinding: non-convex" );
			}
		}
	}
}