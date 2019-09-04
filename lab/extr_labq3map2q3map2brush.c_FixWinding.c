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
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 float DEGENERATE_EPSILON ; 
 int /*<<< orphan*/  SnapWeldVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean FixWinding( winding_t *w ){
	qboolean valid = qtrue;
	int i, j, k;
	vec3_t vec;
	float dist;


	/* dummy check */
	if ( !w ) {
		return qfalse;
	}

	/* check all verts */
	for ( i = 0; i < w->numpoints; i++ )
	{
		/* don't remove points if winding is a triangle */
		if ( w->numpoints == 3 ) {
			return valid;
		}

		/* get second point index */
		j = ( i + 1 ) % w->numpoints;

		/* degenerate edge? */
		VectorSubtract( w->p[ i ], w->p[ j ], vec );
		dist = VectorLength( vec );
		if ( dist < DEGENERATE_EPSILON ) {
			valid = qfalse;
			//Sys_FPrintf( SYS_VRB, "WARNING: Degenerate winding edge found, fixing...\n" );

			/* create an average point (ydnar 2002-01-26: using nearest-integer weld preference) */
			SnapWeldVector( w->p[ i ], w->p[ j ], vec );
			VectorCopy( vec, w->p[ i ] );
			//VectorAdd( w->p[ i ], w->p[ j ], vec );
			//VectorScale( vec, 0.5, w->p[ i ] );

			/* move the remaining verts */
			for ( k = i + 2; k < w->numpoints; k++ )
			{
				VectorCopy( w->p[ k ], w->p[ k - 1 ] );
			}
			w->numpoints--;
		}
	}

	/* one last check and return */
	if ( w->numpoints < 3 ) {
		valid = qfalse;
	}
	return valid;
}