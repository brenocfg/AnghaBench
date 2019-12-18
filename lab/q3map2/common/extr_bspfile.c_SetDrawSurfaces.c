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
typedef  int /*<<< orphan*/  dsurface_t ;
typedef  int /*<<< orphan*/  drawVert_t ;

/* Variables and functions */
 scalar_t__ drawSurfaces ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int numDrawSurfaces ; 
 int numDrawSurfacesBuffer ; 
 scalar_t__ safe_malloc_info (int,char*) ; 

void SetDrawSurfaces( int n ){
	if ( drawSurfaces != 0 ) {
		free( drawSurfaces );
	}

	numDrawSurfaces = n;
	numDrawSurfacesBuffer = numDrawSurfaces;

	drawSurfaces = safe_malloc_info( sizeof( dsurface_t ) * numDrawSurfacesBuffer, "IncDrawSurfaces" );

	memset( drawSurfaces, 0, n * sizeof( drawVert_t ) );
}