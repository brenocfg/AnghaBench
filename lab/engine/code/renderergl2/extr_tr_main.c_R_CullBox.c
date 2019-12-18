#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  cplane_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/ * frustum; } ;
struct TYPE_4__ {TYPE_1__ viewParms; } ;

/* Variables and functions */
 int BoxOnPlaneSide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CULL_CLIP ; 
 int CULL_IN ; 
 int CULL_OUT ; 
 int VPF_FARPLANEFRUSTUM ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_2__ tr ; 

int R_CullBox(vec3_t worldBounds[2]) {
	int             i;
	cplane_t       *frust;
	qboolean        anyClip;
	int             r, numPlanes;

	numPlanes = (tr.viewParms.flags & VPF_FARPLANEFRUSTUM) ? 5 : 4;

	// check against frustum planes
	anyClip = qfalse;
	for(i = 0; i < numPlanes; i++)
	{
		frust = &tr.viewParms.frustum[i];

		r = BoxOnPlaneSide(worldBounds[0], worldBounds[1], frust);

		if(r == 2)
		{
			// completely outside frustum
			return CULL_OUT;
		}
		if(r == 3)
		{
			anyClip = qtrue;
		}
	}

	if(!anyClip)
	{
		// completely inside frustum
		return CULL_IN;
	}

	// partially clipped
	return CULL_CLIP;
}