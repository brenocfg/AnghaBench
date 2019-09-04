#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shaderInfo_t ;
struct TYPE_7__ {int numVerts; int numIndexes; struct TYPE_7__* indexes; struct TYPE_7__* verts; int /*<<< orphan*/ * shaderInfo; int /*<<< orphan*/ * sideRef; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ mapDrawSurface_t ;

/* Variables and functions */
 TYPE_1__* AllocDrawSurface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 void* safe_malloc (int) ; 

mapDrawSurface_t *CloneSurface( mapDrawSurface_t *src, shaderInfo_t *si ){
	mapDrawSurface_t    *ds;


	/* dummy check */
	if ( src == NULL || si == NULL ) {
		return NULL;
	}

	/* allocate a new surface */
	ds = AllocDrawSurface( src->type );
	if ( ds == NULL ) {
		return NULL;
	}

	/* copy it */
	memcpy( ds, src, sizeof( *ds ) );

	/* destroy side reference */
	ds->sideRef = NULL;

	/* set shader */
	ds->shaderInfo = si;

	/* copy verts */
	if ( ds->numVerts > 0 ) {
		ds->verts = safe_malloc( ds->numVerts * sizeof( *ds->verts ) );
		memcpy( ds->verts, src->verts, ds->numVerts * sizeof( *ds->verts ) );
	}

	/* copy indexes */
	if ( ds->numIndexes <= 0 ) {
		return ds;
	}
	ds->indexes = safe_malloc( ds->numIndexes * sizeof( *ds->indexes ) );
	memcpy( ds->indexes, src->indexes, ds->numIndexes * sizeof( *ds->indexes ) );

	/* return the surface */
	return ds;
}