#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_9__ {int numVerts; TYPE_1__* verts; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_7__ {int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 TYPE_2__* AllocWinding (int) ; 
 int MAX_POINTS_ON_WINDING ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  xml_Winding (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

winding_t *WindingFromDrawSurf( mapDrawSurface_t *ds ){
	winding_t   *w;
	int i;

	// we use the first point of the surface, maybe something more clever would be useful
	// (actually send the whole draw surface would be cool?)
	if ( ds->numVerts >= MAX_POINTS_ON_WINDING ) {
		int max = ds->numVerts;
		vec3_t p[256];

		if ( max > 256 ) {
			max = 256;
		}

		for ( i = 0 ; i < max ; i++ ) {
			VectorCopy( ds->verts[i].xyz, p[i] );
		}

		xml_Winding( "WindingFromDrawSurf failed: MAX_POINTS_ON_WINDING exceeded", p, max, qtrue );
	}

	w = AllocWinding( ds->numVerts );
	w->numpoints = ds->numVerts;
	for ( i = 0 ; i < ds->numVerts ; i++ ) {
		VectorCopy( ds->verts[i].xyz, w->p[i] );
	}
	return w;
}