#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double** p; int numpoints; } ;
typedef  TYPE_1__ winding_accu_t ;
typedef  double vec_t ;
typedef  double vec_accu_t ;
typedef  scalar_t__* vec3_t ;
typedef  double* vec3_accu_t ;

/* Variables and functions */
 TYPE_1__* AllocWindingAccu (int) ; 
 int /*<<< orphan*/  CrossProductAccu (double*,double*,double*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ MAX_WORLD_COORD ; 
 int /*<<< orphan*/  VectorAddAccu (double*,double*,double*) ; 
 int /*<<< orphan*/  VectorCopyRegularToAccu (scalar_t__*,double*) ; 
 int /*<<< orphan*/  VectorScaleAccu (double*,double,double*) ; 
 int /*<<< orphan*/  VectorSubtractAccu (double*,double*,double*) ; 
 scalar_t__ fabs (scalar_t__) ; 

winding_accu_t *BaseWindingForPlaneAccu( vec3_t normal, vec_t dist ){
	// The goal in this function is to replicate the behavior of the original BaseWindingForPlane()
	// function (see below) but at the same time increasing accuracy substantially.

	// The original code gave a preference for the vup vector to start out as (0, 0, 1), unless the
	// normal had a dominant Z value, in which case vup started out as (1, 0, 0).  After that, vup
	// was "bent" [along the plane defined by normal and vup] to become perpendicular to normal.
	// After that the vright vector was computed as the cross product of vup and normal.

	// I'm constructing the winding polygon points in a fashion similar to the method used in the
	// original function.  Orientation is the same.  The size of the winding polygon, however, is
	// variable in this function (depending on the angle of normal), and is larger (by about a factor
	// of 2) than the winding polygon in the original function.

	int x, i;
	vec_t max, v;
	vec3_accu_t vright, vup, org, normalAccu;
	winding_accu_t  *w;

	// One of the components of normal must have a magnitiude greater than this value,
	// otherwise normal is not a unit vector.  This is a little bit of inexpensive
	// partial error checking we can do.
	max = 0.56; // 1 / sqrt(1^2 + 1^2 + 1^2) = 0.577350269

	x = -1;
	for ( i = 0; i < 3; i++ ) {
		v = (vec_t) fabs( normal[i] );
		if ( v > max ) {
			x = i;
			max = v;
		}
	}
	if ( x == -1 ) {
		Error( "BaseWindingForPlaneAccu: no dominant axis found because normal is too short" );
	}

	switch ( x ) {
	case 0:     // Fall through to next case.
	case 1:
		vright[0] = (vec_accu_t) -normal[1];
		vright[1] = (vec_accu_t) normal[0];
		vright[2] = 0;
		break;
	case 2:
		vright[0] = 0;
		vright[1] = (vec_accu_t) -normal[2];
		vright[2] = (vec_accu_t) normal[1];
		break;
	}

	// vright and normal are now perpendicular; you can prove this by taking their
	// dot product and seeing that it's always exactly 0 (with no error).

	// NOTE: vright is NOT a unit vector at this point.  vright will have length
	// not exceeding 1.0.  The minimum length that vright can achieve happens when,
	// for example, the Z and X components of the normal input vector are equal,
	// and when normal's Y component is zero.  In that case Z and X of the normal
	// vector are both approximately 0.70711.  The resulting vright vector in this
	// case will have a length of 0.70711.

	// We're relying on the fact that MAX_WORLD_COORD is a power of 2 to keep
	// our calculation precise and relatively free of floating point error.
	// [However, the code will still work fine if that's not the case.]
	VectorScaleAccu( vright, ( (vec_accu_t) MAX_WORLD_COORD ) * 4.0, vright );

	// At time time of this writing, MAX_WORLD_COORD was 65536 (2^16).  Therefore
	// the length of vright at this point is at least 185364.  In comparison, a
	// corner of the world at location (65536, 65536, 65536) is distance 113512
	// away from the origin.

	VectorCopyRegularToAccu( normal, normalAccu );
	CrossProductAccu( normalAccu, vright, vup );

	// vup now has length equal to that of vright.

	VectorScaleAccu( normalAccu, (vec_accu_t) dist, org );

	// org is now a point on the plane defined by normal and dist.  Furthermore,
	// org, vright, and vup are pairwise perpendicular.  Now, the 4 vectors
	// { (+-)vright + (+-)vup } have length that is at least sqrt(185364^2 + 185364^2),
	// which is about 262144.  That length lies outside the world, since the furthest
	// point in the world has distance 113512 from the origin as mentioned above.
	// Also, these 4 vectors are perpendicular to the org vector.  So adding them
	// to org will only increase their length.  Therefore the 4 points defined below
	// all lie outside of the world.  Furthermore, it can be easily seen that the
	// edges connecting these 4 points (in the winding_accu_t below) lie completely
	// outside the world.  sqrt(262144^2 + 262144^2)/2 = 185363, which is greater than
	// 113512.

	w = AllocWindingAccu( 4 );

	VectorSubtractAccu( org, vright, w->p[0] );
	VectorAddAccu( w->p[0], vup, w->p[0] );

	VectorAddAccu( org, vright, w->p[1] );
	VectorAddAccu( w->p[1], vup, w->p[1] );

	VectorAddAccu( org, vright, w->p[2] );
	VectorSubtractAccu( w->p[2], vup, w->p[2] );

	VectorSubtractAccu( org, vright, w->p[3] );
	VectorSubtractAccu( w->p[3], vup, w->p[3] );

	w->numpoints = 4;

	return w;
}