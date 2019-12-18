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
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  VectorClear (double*) ; 
 int /*<<< orphan*/  VectorNormalize (double*,double*) ; 
 double fabs (double) ; 
 double normalEpsilon ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

qboolean SnapNormal( vec3_t normal ){
#if Q3MAP2_EXPERIMENTAL_SNAP_NORMAL_FIX
	int i;
	qboolean adjusted = qfalse;

	// A change from the original SnapNormal() is that we snap each
	// component that's close to 0.  So for example if a normal is
	// (0.707, 0.707, 0.0000001), it will get snapped to lie perfectly in the
	// XY plane (its Z component will be set to 0 and its length will be
	// normalized).  The original SnapNormal() didn't snap such vectors - it
	// only snapped vectors that were near a perfect axis.

	for ( i = 0; i < 3; i++ )
	{
		if ( normal[i] != 0.0 && -normalEpsilon < normal[i] && normal[i] < normalEpsilon ) {
			normal[i] = 0.0;
			adjusted = qtrue;
		}
	}

	if ( adjusted ) {
		VectorNormalize( normal, normal );
		return qtrue;
	}
	return qfalse;
#else
	int i;

	// I would suggest that you uncomment the following code and look at the
	// results:

	/*
	   Sys_Printf("normalEpsilon is %f\n", normalEpsilon);
	   for (i = 0;; i++)
	   {
	    normal[0] = 1.0;
	    normal[1] = 0.0;
	    normal[2] = i * 0.000001;
	    VectorNormalize(normal, normal);
	    if (1.0 - normal[0] >= normalEpsilon) {
	        Sys_Printf("(%f %f %f)\n", normal[0], normal[1], normal[2]);
	        Error("SnapNormal: test completed");
	    }
	   }
	 */

	// When the normalEpsilon is 0.00001, the loop will break out when normal is
	// (0.999990 0.000000 0.004469).  In other words, this is the vector closest
	// to axial that will NOT be snapped.  Anything closer will be snaped.  Now,
	// 0.004469 is close to 1/225.  The length of a circular quarter-arc of radius
	// 1 is PI/2, or about 1.57.  And 0.004469/1.57 is about 0.0028, or about
	// 1/350.  Expressed a different way, 1/350 is also about 0.26/90.
	// This means is that a normal with an angle that is within 1/4 of a degree
	// from axial will be "snapped".  My belief is that the person who wrote the
	// code below did not intend it this way.  I think the person intended that
	// the epsilon be measured against the vector components close to 0, not 1.0.
	// I think the logic should be: if 2 of the normal components are within
	// epsilon of 0, then the vector can be snapped to be perfectly axial.
	// We may consider adjusting the epsilon to a larger value when we make this
	// code fix.

	for ( i = 0; i < 3; i++ )
	{
		if ( fabs( normal[ i ] - 1 ) < normalEpsilon ) {
			VectorClear( normal );
			normal[ i ] = 1;
			return qtrue;
		}
		if ( fabs( normal[ i ] - -1 ) < normalEpsilon ) {
			VectorClear( normal );
			normal[ i ] = -1;
			return qtrue;
		}
	}
	return qfalse;
#endif
}