#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* normal; int dist; } ;
typedef  TYPE_1__ visPlane_t ;
typedef  int vec_t ;
typedef  int* vec3_t ;
struct TYPE_8__ {int numpoints; int** points; } ;
typedef  TYPE_2__ fixedWinding_t ;

/* Variables and functions */
 int DotProduct (int*,int*) ; 
 int MAX_POINTS_ON_FIXED_WINDING ; 
 int ON_EPSILON ; 
 int SIDE_BACK ; 
 int SIDE_FRONT ; 
 int SIDE_ON ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 

fixedWinding_t *PassageChopWinding( fixedWinding_t *in, fixedWinding_t *out, visPlane_t *split ){
	vec_t dists[128];
	int sides[128];
	int counts[3];
	vec_t dot;
	int i, j;
	vec_t   *p1, *p2;
	vec3_t mid;
	fixedWinding_t  *neww;

	counts[0] = counts[1] = counts[2] = 0;

	// determine sides for each point
	for ( i = 0 ; i < in->numpoints ; i++ )
	{
		dot = DotProduct( in->points[i], split->normal );
		dot -= split->dist;
		dists[i] = dot;
		if ( dot > ON_EPSILON ) {
			sides[i] = SIDE_FRONT;
		}
		else if ( dot < -ON_EPSILON ) {
			sides[i] = SIDE_BACK;
		}
		else
		{
			sides[i] = SIDE_ON;
		}
		counts[sides[i]]++;
	}

	if ( !counts[1] ) {
		return in;      // completely on front side

	}
	if ( !counts[0] ) {
		return NULL;
	}

	sides[i] = sides[0];
	dists[i] = dists[0];

	neww = out;

	neww->numpoints = 0;

	for ( i = 0 ; i < in->numpoints ; i++ )
	{
		p1 = in->points[i];

		if ( neww->numpoints == MAX_POINTS_ON_FIXED_WINDING ) {
			return in;      // can't chop -- fall back to original
		}

		if ( sides[i] == SIDE_ON ) {
			VectorCopy( p1, neww->points[neww->numpoints] );
			neww->numpoints++;
			continue;
		}

		if ( sides[i] == SIDE_FRONT ) {
			VectorCopy( p1, neww->points[neww->numpoints] );
			neww->numpoints++;
		}

		if ( sides[i + 1] == SIDE_ON || sides[i + 1] == sides[i] ) {
			continue;
		}

		if ( neww->numpoints == MAX_POINTS_ON_FIXED_WINDING ) {
			return in;      // can't chop -- fall back to original
		}

		// generate a split point
		p2 = in->points[( i + 1 ) % in->numpoints];

		dot = dists[i] / ( dists[i] - dists[i + 1] );
		for ( j = 0 ; j < 3 ; j++ )
		{   // avoid round off error when possible
			if ( split->normal[j] == 1 ) {
				mid[j] = split->dist;
			}
			else if ( split->normal[j] == -1 ) {
				mid[j] = -split->dist;
			}
			else{
				mid[j] = p1[j] + dot * ( p2[j] - p1[j] );
			}
		}

		VectorCopy( mid, neww->points[neww->numpoints] );
		neww->numpoints++;
	}

	return neww;
}