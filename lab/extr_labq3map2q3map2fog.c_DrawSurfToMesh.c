#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int width; int height; void* verts; } ;
typedef  TYPE_1__ mesh_t ;
struct TYPE_6__ {int patchWidth; int patchHeight; int /*<<< orphan*/  verts; } ;
typedef  TYPE_2__ mapDrawSurface_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 void* safe_malloc (int) ; 

mesh_t *DrawSurfToMesh( mapDrawSurface_t *ds ){
	mesh_t      *m;


	m = safe_malloc( sizeof( *m ) );
	m->width = ds->patchWidth;
	m->height = ds->patchHeight;
	m->verts = safe_malloc( sizeof( m->verts[ 0 ] ) * m->width * m->height );
	memcpy( m->verts, ds->verts, sizeof( m->verts[ 0 ] ) * m->width * m->height );

	return m;
}