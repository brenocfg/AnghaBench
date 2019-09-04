#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int width; int height; int /*<<< orphan*/  verts; } ;
typedef  TYPE_2__ mesh_t ;
struct TYPE_19__ {int numVerts; scalar_t__ type; int patchWidth; int patchHeight; int* indexes; scalar_t__ numIndexes; int /*<<< orphan*/  verts; TYPE_1__* shaderInfo; int /*<<< orphan*/  longestCurve; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_17__ {int compileFlags; } ;

/* Variables and functions */
 TYPE_3__* AllocDrawSurface (scalar_t__) ; 
 int C_SOLID ; 
 int /*<<< orphan*/  ClassifySurfaces (int,TYPE_3__*) ; 
 int /*<<< orphan*/  ClearSurface (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeMesh (TYPE_2__*) ; 
 int IterationsForCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PutMeshOnCurve (TYPE_2__) ; 
 TYPE_2__* RemoveLinearMeshColumnsRows (TYPE_2__*) ; 
 scalar_t__ SURFACE_META ; 
 scalar_t__ SURFACE_PATCH ; 
 TYPE_2__* SubdivideMesh2 (TYPE_2__,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  numPatchMetaSurfaces ; 
 scalar_t__ patchMeta ; 
 int /*<<< orphan*/  patchSubdivisions ; 
 scalar_t__ qfalse ; 
 int* safe_malloc (int) ; 

void TriangulatePatchSurface( mapDrawSurface_t *ds ){
	int iterations, x, y, pw[ 5 ], r;
	mapDrawSurface_t    *dsNew;
	mesh_t src, *subdivided, *mesh;


	/* try to early out */
	if ( ds->numVerts == 0 || ds->type != SURFACE_PATCH || patchMeta == qfalse ) {
		return;
	}

	/* make a mesh from the drawsurf */
	src.width = ds->patchWidth;
	src.height = ds->patchHeight;
	src.verts = ds->verts;
	//%	subdivided = SubdivideMesh( src, 8, 999 );
	iterations = IterationsForCurve( ds->longestCurve, patchSubdivisions );
	subdivided = SubdivideMesh2( src, iterations ); //%	ds->maxIterations

	/* fit it to the curve and remove colinear verts on rows/columns */
	PutMeshOnCurve( *subdivided );
	mesh = RemoveLinearMeshColumnsRows( subdivided );
	FreeMesh( subdivided );
	//% MakeMeshNormals( mesh );

	/* make a copy of the drawsurface */
	dsNew = AllocDrawSurface( SURFACE_META );
	memcpy( dsNew, ds, sizeof( *ds ) );

	/* if the patch is nonsolid, then discard it */
	if ( !( ds->shaderInfo->compileFlags & C_SOLID ) ) {
		ClearSurface( ds );
	}

	/* set new pointer */
	ds = dsNew;

	/* basic transmogrification */
	ds->type = SURFACE_META;
	ds->numIndexes = 0;
	ds->indexes = safe_malloc( mesh->width * mesh->height * 6 * sizeof( int ) );

	/* copy the verts in */
	ds->numVerts = ( mesh->width * mesh->height );
	ds->verts = mesh->verts;

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

			/* make first triangle */
			ds->indexes[ ds->numIndexes++ ] = pw[ r + 0 ];
			ds->indexes[ ds->numIndexes++ ] = pw[ r + 1 ];
			ds->indexes[ ds->numIndexes++ ] = pw[ r + 2 ];

			/* make second triangle */
			ds->indexes[ ds->numIndexes++ ] = pw[ r + 0 ];
			ds->indexes[ ds->numIndexes++ ] = pw[ r + 2 ];
			ds->indexes[ ds->numIndexes++ ] = pw[ r + 3 ];
		}
	}

	/* free the mesh, but not the verts */
	free( mesh );

	/* add to count */
	numPatchMetaSurfaces++;

	/* classify it */
	ClassifySurfaces( 1, ds );
}