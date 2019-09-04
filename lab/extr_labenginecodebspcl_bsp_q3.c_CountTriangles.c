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
struct TYPE_3__ {int numIndexes; int patchWidth; int patchHeight; } ;
typedef  TYPE_1__ q3_dsurface_t ;

/* Variables and functions */
 int /*<<< orphan*/  Log_Print (char*,int) ; 
 TYPE_1__* q3_drawSurfaces ; 
 int q3_numDrawSurfaces ; 

void CountTriangles( void ) {
	int i, numTris, numPatchTris;
	q3_dsurface_t *surface;

	numTris = numPatchTris = 0;
	for ( i = 0; i < q3_numDrawSurfaces; i++ ) {
		surface = &q3_drawSurfaces[i];

		numTris += surface->numIndexes / 3;

		if ( surface->patchWidth ) {
			numPatchTris += surface->patchWidth * surface->patchHeight * 2;
		}
	}

	Log_Print( "%6d triangles\n", numTris );
	Log_Print( "%6d patch tris\n", numPatchTris );
}