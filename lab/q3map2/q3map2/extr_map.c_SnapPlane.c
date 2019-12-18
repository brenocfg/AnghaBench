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
typedef  scalar_t__ vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 scalar_t__ Q_rint (scalar_t__) ; 
 int /*<<< orphan*/  SnapNormal (int /*<<< orphan*/ ) ; 
 scalar_t__ distanceEpsilon ; 
 scalar_t__ fabs (scalar_t__) ; 

void SnapPlane( vec3_t normal, vec_t *dist ){
// SnapPlane disabled by LordHavoc because it often messes up collision
// brushes made from triangles of embedded models, and it has little effect
// on anything else (axial planes are usually derived from snapped points)
/*
   SnapPlane reenabled by namespace because of multiple reports of
   q3map2-crashes which were triggered by this patch.
 */
	SnapNormal( normal );

	// TODO: Rambetter has some serious comments here as well.  First off,
	// in the case where a normal is non-axial, there is nothing special
	// about integer distances.  I would think that snapping a distance might
	// make sense for axial normals, but I'm not so sure about snapping
	// non-axial normals.  A shift by 0.01 in a plane, multiplied by a clipping
	// against another plane that is 5 degrees off, and we introduce 0.1 error
	// easily.  A 0.1 error in a vertex is where problems start to happen, such
	// as disappearing triangles.

	// Second, assuming we have snapped the normal above, let's say that the
	// plane we just snapped was defined for some points that are actually
	// quite far away from normal * dist.  Well, snapping the normal in this
	// case means that we've just moved those points by potentially many units!
	// Therefore, if we are going to snap the normal, we need to know the
	// points we're snapping for so that the plane snaps with those points in
	// mind (points remain close to the plane).

	// I would like to know exactly which problems SnapPlane() is trying to
	// solve so that we can better engineer it (I'm not saying that SnapPlane()
	// should be removed altogether).  Fix all this snapping code at some point!

	if ( fabs( *dist - Q_rint( *dist ) ) < distanceEpsilon ) {
		*dist = Q_rint( *dist );
	}
}