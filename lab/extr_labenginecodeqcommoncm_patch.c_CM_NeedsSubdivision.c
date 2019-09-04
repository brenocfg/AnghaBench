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
typedef  double* vec3_t ;
typedef  int qboolean ;

/* Variables and functions */
 float SUBDIVIDE_DISTANCE ; 
 float VectorLength (double*) ; 
 int /*<<< orphan*/  VectorSubtract (double*,double*,double*) ; 

__attribute__((used)) static qboolean	CM_NeedsSubdivision( vec3_t a, vec3_t b, vec3_t c ) {
	vec3_t		cmid;
	vec3_t		lmid;
	vec3_t		delta;
	float		dist;
	int			i;

	// calculate the linear midpoint
	for ( i = 0 ; i < 3 ; i++ ) {
		lmid[i] = 0.5*(a[i] + c[i]);
	}

	// calculate the exact curve midpoint
	for ( i = 0 ; i < 3 ; i++ ) {
		cmid[i] = 0.5 * ( 0.5*(a[i] + b[i]) + 0.5*(b[i] + c[i]) );
	}

	// see if the curve is far enough away from the linear mid
	VectorSubtract( cmid, lmid, delta );
	dist = VectorLength( delta );
	
	return dist >= SUBDIVIDE_DISTANCE;
}