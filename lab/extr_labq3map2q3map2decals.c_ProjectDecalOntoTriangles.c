#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int numpoints; scalar_t__** p; } ;
typedef  TYPE_3__ winding_t ;
typedef  scalar_t__* vec4_t ;
struct TYPE_16__ {scalar_t__ type; size_t planeNum; int numIndexes; size_t* indexes; TYPE_2__* verts; scalar_t__ planar; TYPE_1__* shaderInfo; } ;
typedef  TYPE_4__ mapDrawSurface_t ;
struct TYPE_17__ {scalar_t__** planes; } ;
typedef  TYPE_5__ decalProjector_t ;
struct TYPE_18__ {scalar_t__ dist; int /*<<< orphan*/  normal; } ;
struct TYPE_14__ {int /*<<< orphan*/  xyz; } ;
struct TYPE_13__ {int /*<<< orphan*/ * shaderText; } ;

/* Variables and functions */
 TYPE_3__* AllocWinding (int) ; 
 float DotProduct (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ProjectDecalOntoWinding (TYPE_5__*,TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ SURFACE_TRIANGLES ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__* entityOrigin ; 
 TYPE_6__* mapplanes ; 

__attribute__((used)) static void ProjectDecalOntoTriangles( decalProjector_t *dp, mapDrawSurface_t *ds ){
	int i;
	vec4_t plane;
	float d;
	winding_t   *w;


	/* triangle surfaces without shaders don't get marks by default */
	if ( ds->type == SURFACE_TRIANGLES && ds->shaderInfo->shaderText == NULL ) {
		return;
	}

	/* backface check */
	if ( ds->planar ) {
		VectorCopy( mapplanes[ ds->planeNum ].normal, plane );
		plane[ 3 ] = mapplanes[ ds->planeNum ].dist + DotProduct( plane, entityOrigin );
		d = DotProduct( dp->planes[ 0 ], plane );
		if ( d < -0.0001f ) {
			return;
		}
	}

	/* iterate through triangles */
	for ( i = 0; i < ds->numIndexes; i += 3 )
	{
		/* generate decal */
		w = AllocWinding( 3 );
		w->numpoints = 3;
		VectorCopy( ds->verts[ ds->indexes[ i ] ].xyz, w->p[ 0 ] );
		VectorCopy( ds->verts[ ds->indexes[ i + 1 ] ].xyz, w->p[ 1 ] );
		VectorCopy( ds->verts[ ds->indexes[ i + 2 ] ].xyz, w->p[ 2 ] );
		ProjectDecalOntoWinding( dp, ds, w );
	}
}