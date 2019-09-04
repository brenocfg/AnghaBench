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
typedef  int /*<<< orphan*/  bspDrawSurface_t ;

/* Variables and functions */
 int MAX_MAP_DRAW_SURFS ; 
 scalar_t__ bspDrawSurfaces ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int numBSPDrawSurfacesBuffer ; 
 scalar_t__ safe_malloc_info (int,char*) ; 

void SetDrawSurfacesBuffer(){
	if ( bspDrawSurfaces != 0 ) {
		free( bspDrawSurfaces );
	}

	numBSPDrawSurfacesBuffer = MAX_MAP_DRAW_SURFS;

	bspDrawSurfaces = safe_malloc_info( sizeof( bspDrawSurface_t ) * numBSPDrawSurfacesBuffer, "IncDrawSurfaces" );

	memset( bspDrawSurfaces, 0, numBSPDrawSurfacesBuffer * sizeof( bspDrawSurface_t ) );
}