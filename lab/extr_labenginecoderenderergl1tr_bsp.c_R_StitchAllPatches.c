#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ surfaceType; void* lodStitched; } ;
typedef  TYPE_2__ srfGridMesh_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_7__ {int numsurfaces; TYPE_1__* surfaces; } ;
struct TYPE_5__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ALL ; 
 scalar_t__ R_TryStitchingPatch (int) ; 
 scalar_t__ SF_GRID ; 
 int qfalse ; 
 void* qtrue ; 
 TYPE_4__ ri ; 
 TYPE_3__ s_worldData ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

void R_StitchAllPatches( void ) {
	int i, stitched, numstitches;
	srfGridMesh_t *grid1;

	numstitches = 0;
	do
	{
		stitched = qfalse;
		for ( i = 0; i < s_worldData.numsurfaces; i++ ) {
			//
			grid1 = (srfGridMesh_t *) s_worldData.surfaces[i].data;
			// if this surface is not a grid
			if ( grid1->surfaceType != SF_GRID )
				continue;
			//
			if ( grid1->lodStitched )
				continue;
			//
			grid1->lodStitched = qtrue;
			stitched = qtrue;
			//
			numstitches += R_TryStitchingPatch( i );
		}
	}
	while (stitched);
	ri.Printf( PRINT_ALL, "stitched %d LoD cracks\n", numstitches );
}