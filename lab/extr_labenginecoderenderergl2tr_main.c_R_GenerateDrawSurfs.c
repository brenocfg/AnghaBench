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
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {TYPE_2__ viewParms; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_AddEntitySurfaces () ; 
 int /*<<< orphan*/  R_AddPolygonSurfaces () ; 
 int /*<<< orphan*/  R_AddWorldSurfaces () ; 
 int /*<<< orphan*/  R_SetFarClip () ; 
 int /*<<< orphan*/  R_SetupProjectionZ (TYPE_2__*) ; 
 int VPF_SHADOWMAP ; 
 TYPE_1__ tr ; 

void R_GenerateDrawSurfs( void ) {
	R_AddWorldSurfaces ();

	R_AddPolygonSurfaces();

	// set the projection matrix with the minimum zfar
	// now that we have the world bounded
	// this needs to be done before entities are
	// added, because they use the projection
	// matrix for lod calculation

	// dynamically compute far clip plane distance
	if (!(tr.viewParms.flags & VPF_SHADOWMAP))
	{
		R_SetFarClip();
	}

	// we know the size of the clipping volume. Now set the rest of the projection matrix.
	R_SetupProjectionZ (&tr.viewParms);

	R_AddEntitySurfaces ();
}