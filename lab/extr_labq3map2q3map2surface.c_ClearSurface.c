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
struct TYPE_3__ {int planeNum; int /*<<< orphan*/ * indexes; scalar_t__ numIndexes; int /*<<< orphan*/ * verts; scalar_t__ numVerts; int /*<<< orphan*/  planar; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ mapDrawSurface_t ;

/* Variables and functions */
 int /*<<< orphan*/  SURFACE_BAD ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  numClearedSurfaces ; 
 int /*<<< orphan*/  qfalse ; 

void ClearSurface( mapDrawSurface_t *ds ){
	ds->type = SURFACE_BAD;
	ds->planar = qfalse;
	ds->planeNum = -1;
	ds->numVerts = 0;
	if ( ds->verts != NULL ) {
		free( ds->verts );
	}
	ds->verts = NULL;
	ds->numIndexes = 0;
	if ( ds->indexes != NULL ) {
		free( ds->indexes );
	}
	ds->indexes = NULL;
	numClearedSurfaces++;
}