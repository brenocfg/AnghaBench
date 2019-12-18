#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int numpoints; int** p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int vec_t ;
typedef  int* vec3_t ;

/* Variables and functions */
 TYPE_1__* AllocWinding (int) ; 
 TYPE_1__* CopyWinding (TYPE_1__*) ; 
 int DotProduct (int*,int*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_POINTS_ON_WINDING ; 
 int SIDE_BACK ; 
 int SIDE_FRONT ; 
 int SIDE_ON ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 

void    ClipWindingEpsilon( winding_t *in, vec3_t normal, vec_t dist,
							vec_t epsilon, winding_t **front, winding_t **back ){
	vec_t dists[MAX_POINTS_ON_WINDING + 4];
	int sides[MAX_POINTS_ON_WINDING + 4];
	int counts[3];
	static vec_t dot;           // VC 4.2 optimizer bug if not static
	int i, j;
	vec_t   *p1, *p2;
	vec3_t mid;
	winding_t   *f, *b;
	int maxpts;

	counts[0] = counts[1] = counts[2] = 0;

// determine sides for each point
	for ( i = 0 ; i < in->numpoints ; i++ )
	{

		dot = DotProduct( in->p[i], normal );
		dot -= dist;
		dists[i] = dot;
		if ( dot > epsilon ) {
			sides[i] = SIDE_FRONT;
		}
		else if ( dot < -epsilon ) {
			sides[i] = SIDE_BACK;
		}
		else
		{
			sides[i] = SIDE_ON;
		}
		counts[sides[i]]++;
	}
	sides[i] = sides[0];
	dists[i] = dists[0];

	*front = *back = NULL;

	if ( !counts[0] ) {
		*back = CopyWinding( in );
		return;
	}
	if ( !counts[1] ) {
		*front = CopyWinding( in );
		return;
	}

	maxpts = in->numpoints + 4;   // cant use counts[0]+2 because
	                              // of fp grouping errors

	*front = f = AllocWinding( maxpts );
	*back = b = AllocWinding( maxpts );

	for ( i = 0 ; i < in->numpoints ; i++ )
	{
		p1 = in->p[i];

		if ( sides[i] == SIDE_ON ) {
			VectorCopy( p1, f->p[f->numpoints] );
			f->numpoints++;
			VectorCopy( p1, b->p[b->numpoints] );
			b->numpoints++;
			continue;
		}

		if ( sides[i] == SIDE_FRONT ) {
			VectorCopy( p1, f->p[f->numpoints] );
			f->numpoints++;
		}
		if ( sides[i] == SIDE_BACK ) {
			VectorCopy( p1, b->p[b->numpoints] );
			b->numpoints++;
		}

		if ( sides[i + 1] == SIDE_ON || sides[i + 1] == sides[i] ) {
			continue;
		}

		// generate a split point
		p2 = in->p[( i + 1 ) % in->numpoints];

		dot = dists[i] / ( dists[i] - dists[i + 1] );
		for ( j = 0 ; j < 3 ; j++ )
		{   // avoid round off error when possible
			if ( normal[j] == 1 ) {
				mid[j] = dist;
			}
			else if ( normal[j] == -1 ) {
				mid[j] = -dist;
			}
			else{
				mid[j] = p1[j] + dot * ( p2[j] - p1[j] );
			}
		}

		VectorCopy( mid, f->p[f->numpoints] );
		f->numpoints++;
		VectorCopy( mid, b->p[b->numpoints] );
		b->numpoints++;
	}

	if ( f->numpoints > maxpts || b->numpoints > maxpts ) {
		Error( "ClipWinding: points exceeded estimate" );
	}
	if ( f->numpoints > MAX_POINTS_ON_WINDING || b->numpoints > MAX_POINTS_ON_WINDING ) {
		Error( "ClipWinding: MAX_POINTS_ON_WINDING" );
	}
}