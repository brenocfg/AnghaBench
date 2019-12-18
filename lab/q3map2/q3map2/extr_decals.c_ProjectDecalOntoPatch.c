#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int numpoints; scalar_t__** p; } ;
typedef  TYPE_2__ winding_t ;
typedef  scalar_t__* vec4_t ;
struct TYPE_22__ {int width; int height; TYPE_1__* verts; } ;
typedef  TYPE_3__ mesh_t ;
struct TYPE_23__ {size_t planeNum; int patchWidth; int patchHeight; int /*<<< orphan*/  longestCurve; TYPE_1__* verts; scalar_t__ planar; } ;
typedef  TYPE_4__ mapDrawSurface_t ;
struct TYPE_24__ {scalar_t__** planes; } ;
typedef  TYPE_5__ decalProjector_t ;
struct TYPE_25__ {scalar_t__ dist; int /*<<< orphan*/  normal; } ;
struct TYPE_20__ {int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 TYPE_2__* AllocWinding (int) ; 
 float DotProduct (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  FreeMesh (TYPE_3__*) ; 
 int IterationsForCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProjectDecalOntoWinding (TYPE_5__*,TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  PutMeshOnCurve (TYPE_3__) ; 
 TYPE_3__* RemoveLinearMeshColumnsRows (TYPE_3__*) ; 
 TYPE_3__* SubdivideMesh2 (TYPE_3__,int) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__* entityOrigin ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_6__* mapplanes ; 
 int /*<<< orphan*/  patchSubdivisions ; 

__attribute__((used)) static void ProjectDecalOntoPatch( decalProjector_t *dp, mapDrawSurface_t *ds ){
	int x, y, pw[ 5 ], r, iterations;
	vec4_t plane;
	float d;
	mesh_t src, *mesh, *subdivided;
	winding_t   *w;


	/* backface check */
	if ( ds->planar ) {
		VectorCopy( mapplanes[ ds->planeNum ].normal, plane );
		plane[ 3 ] = mapplanes[ ds->planeNum ].dist + DotProduct( plane, entityOrigin );
		d = DotProduct( dp->planes[ 0 ], plane );
		if ( d < -0.0001f ) {
			return;
		}
	}

	/* tesselate the patch */
	src.width = ds->patchWidth;
	src.height = ds->patchHeight;
	src.verts = ds->verts;
	iterations = IterationsForCurve( ds->longestCurve, patchSubdivisions );
	subdivided = SubdivideMesh2( src, iterations );

	/* fit it to the curve and remove colinear verts on rows/columns */
	PutMeshOnCurve( *subdivided );
	mesh = RemoveLinearMeshColumnsRows( subdivided );
	FreeMesh( subdivided );

	/* iterate through the mesh quads */
	for ( y = 0; y < ( mesh->height - 1 ); y++ )
	{
		for ( x = 0; x < ( mesh->width - 1 ); x++ )
		{
			/* set indexes */
			pw[ 0 ] = x + ( y * mesh->width );
			pw[ 1 ] = x + ( ( y + 1 ) * mesh->width );
			pw[ 2 ] = x + 1 + ( ( y + 1 ) * mesh->width );
			pw[ 3 ] = x + 1 + ( y * mesh->width );
			pw[ 4 ] = x + ( y * mesh->width );    /* same as pw[ 0 ] */

			/* set radix */
			r = ( x + y ) & 1;

			/* generate decal for first triangle */
			w = AllocWinding( 3 );
			w->numpoints = 3;
			VectorCopy( mesh->verts[ pw[ r + 0 ] ].xyz, w->p[ 0 ] );
			VectorCopy( mesh->verts[ pw[ r + 1 ] ].xyz, w->p[ 1 ] );
			VectorCopy( mesh->verts[ pw[ r + 2 ] ].xyz, w->p[ 2 ] );
			ProjectDecalOntoWinding( dp, ds, w );

			/* generate decal for second triangle */
			w = AllocWinding( 3 );
			w->numpoints = 3;
			VectorCopy( mesh->verts[ pw[ r + 0 ] ].xyz, w->p[ 0 ] );
			VectorCopy( mesh->verts[ pw[ r + 2 ] ].xyz, w->p[ 1 ] );
			VectorCopy( mesh->verts[ pw[ r + 3 ] ].xyz, w->p[ 2 ] );
			ProjectDecalOntoWinding( dp, ds, w );
		}
	}

	/* clean up */
	free( mesh );
}