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
struct TYPE_3__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_accu_t ;
typedef  scalar_t__ vec_accu_t ;
typedef  int /*<<< orphan*/  vec3_accu_t ;
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 scalar_t__ DEGENERATE_EPSILON ; 
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  SnapWeldVectorAccu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopyAccu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VectorLengthAccu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtractAccu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

qboolean FixWindingAccu( winding_accu_t *w ){
	int i, j, k;
	vec3_accu_t vec;
	vec_accu_t dist;
	qboolean done, altered;

	if ( w == NULL ) {
		Error( "FixWindingAccu: NULL argument" );
	}

	altered = qfalse;

	while ( qtrue )
	{
		if ( w->numpoints < 2 ) {
			break;                   // Don't remove the only remaining point.
		}
		done = qtrue;
		for ( i = 0; i < w->numpoints; i++ )
		{
			j = ( ( ( i + 1 ) == w->numpoints ) ? 0 : ( i + 1 ) );

			VectorSubtractAccu( w->p[i], w->p[j], vec );
			dist = VectorLengthAccu( vec );
			if ( dist < DEGENERATE_EPSILON ) {
				// TODO: I think the "snap weld vector" was written before
				// some of the math precision fixes, and its purpose was
				// probably to address math accuracy issues.  We can think
				// about changing the logic here.  Maybe once plane distance
				// gets 64 bits, we can look at it then.
				SnapWeldVectorAccu( w->p[i], w->p[j], vec );
				VectorCopyAccu( vec, w->p[i] );
				for ( k = j + 1; k < w->numpoints; k++ )
				{
					VectorCopyAccu( w->p[k], w->p[k - 1] );
				}
				w->numpoints--;
				altered = qtrue;
				// The only way to finish off fixing the winding consistently and
				// accurately is by fixing the winding all over again.  For example,
				// the point at index i and the point at index i-1 could now be
				// less than the epsilon distance apart.  There are too many special
				// case problems we'd need to handle if we didn't start from the
				// beginning.
				done = qfalse;
				break; // This will cause us to return to the "while" loop.
			}
		}
		if ( done ) {
			break;
		}
	}

	return altered;
}