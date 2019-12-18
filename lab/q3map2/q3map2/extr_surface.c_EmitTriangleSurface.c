#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_14__ {int numIndexes; int* indexes; int numVerts; size_t outputNum; size_t type; scalar_t__ planar; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; TYPE_3__* verts; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  patchHeight; int /*<<< orphan*/  patchWidth; TYPE_1__* shaderInfo; int /*<<< orphan*/  lightmapAxis; scalar_t__ backSide; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_15__ {int /*<<< orphan*/  xyz; int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ bspDrawVert_t ;
struct TYPE_16__ {int* lightmapNum; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; void** vertexStyles; void** lightmapStyles; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  patchHeight; int /*<<< orphan*/  patchWidth; void* shaderNum; int /*<<< orphan*/  surfaceType; } ;
typedef  TYPE_4__ bspDrawSurface_t ;
struct TYPE_13__ {char* shader; int /*<<< orphan*/  surfaceFlags; int /*<<< orphan*/  contentFlags; scalar_t__ invert; } ;

/* Variables and functions */
 int /*<<< orphan*/  EmitDrawIndexes (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  EmitDrawVerts (TYPE_2__*,TYPE_4__*) ; 
 void* EmitShader (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Error (char*) ; 
 void* LS_NONE ; 
 void* LS_NORMAL ; 
 int MAX_LIGHTMAPS ; 
 size_t MAX_MAP_DRAW_SURFS ; 
 int /*<<< orphan*/  MST_FOLIAGE ; 
 int /*<<< orphan*/  MST_PLANAR ; 
 int /*<<< orphan*/  MST_TRIANGLE_SOUP ; 
 int /*<<< orphan*/  OptimizeTriangleSurface (TYPE_2__*) ; 
 size_t SURFACE_FOGHULL ; 
 size_t SURFACE_FOLIAGE ; 
 size_t SURFACE_TRIANGLES ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* bspDrawSurfaces ; 
 scalar_t__ debugInset ; 
 scalar_t__ debugSurfaces ; 
 int maxLMSurfaceVerts ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 size_t numBSPDrawSurfaces ; 
 int /*<<< orphan*/ * numSurfacesByType ; 
 scalar_t__ qfalse ; 

__attribute__((used)) static void EmitTriangleSurface( mapDrawSurface_t *ds ){
	int i, temp;
	bspDrawSurface_t        *out;


	/* invert the surface if necessary */
	if ( ds->backSide || ds->shaderInfo->invert ) {
		/* walk the indexes, reverse the triangle order */
		for ( i = 0; i < ds->numIndexes; i += 3 )
		{
			temp = ds->indexes[ i ];
			ds->indexes[ i ] = ds->indexes[ i + 1 ];
			ds->indexes[ i + 1 ] = temp;
		}

		/* walk the verts, flip the normal */
		for ( i = 0; i < ds->numVerts; i++ )
			VectorScale( ds->verts[ i ].normal, -1.0f, ds->verts[ i ].normal );

		/* invert facing */
		VectorScale( ds->lightmapVecs[ 2 ], -1.0f, ds->lightmapVecs[ 2 ] );
	}

	/* allocate a new surface */
	if ( numBSPDrawSurfaces == MAX_MAP_DRAW_SURFS ) {
		Error( "MAX_MAP_DRAW_SURFS" );
	}
	out = &bspDrawSurfaces[ numBSPDrawSurfaces ];
	ds->outputNum = numBSPDrawSurfaces;
	numBSPDrawSurfaces++;
	memset( out, 0, sizeof( *out ) );

	/* ydnar/sd: handle wolf et foliage surfaces */
	if ( ds->type == SURFACE_FOLIAGE ) {
		out->surfaceType = MST_FOLIAGE;
	}

	/* ydnar: gs mods: handle lightmapped terrain (force to planar type) */
	//%	else if( VectorLength( ds->lightmapAxis ) <= 0.0f || ds->type == SURFACE_TRIANGLES || ds->type == SURFACE_FOGHULL || debugSurfaces )
	else if ( ( VectorLength( ds->lightmapAxis ) <= 0.0f && ds->planar == qfalse ) ||
			  ds->type == SURFACE_TRIANGLES ||
			  ds->type == SURFACE_FOGHULL ||
			  ds->numVerts > maxLMSurfaceVerts ||
			  debugSurfaces ) {
		out->surfaceType = MST_TRIANGLE_SOUP;
	}

	/* set to a planar face */
	else{
		out->surfaceType = MST_PLANAR;
	}

	/* set it up */
	if ( debugSurfaces ) {
		out->shaderNum = EmitShader( "debugsurfaces", NULL, NULL );
	}
	else{
		out->shaderNum = EmitShader( ds->shaderInfo->shader, &ds->shaderInfo->contentFlags, &ds->shaderInfo->surfaceFlags );
	}
	out->patchWidth = ds->patchWidth;
	out->patchHeight = ds->patchHeight;
	out->fogNum = ds->fogNum;

	/* debug inset (push each triangle vertex towards the center of each triangle it is on */
	if ( debugInset ) {
		bspDrawVert_t   *a, *b, *c;
		vec3_t cent, dir;


		/* walk triangle list */
		for ( i = 0; i < ds->numIndexes; i += 3 )
		{
			/* get verts */
			a = &ds->verts[ ds->indexes[ i ] ];
			b = &ds->verts[ ds->indexes[ i + 1 ] ];
			c = &ds->verts[ ds->indexes[ i + 2 ] ];

			/* calculate centroid */
			VectorCopy( a->xyz, cent );
			VectorAdd( cent, b->xyz, cent );
			VectorAdd( cent, c->xyz, cent );
			VectorScale( cent, 1.0f / 3.0f, cent );

			/* offset each vertex */
			VectorSubtract( cent, a->xyz, dir );
			VectorNormalize( dir, dir );
			VectorAdd( a->xyz, dir, a->xyz );
			VectorSubtract( cent, b->xyz, dir );
			VectorNormalize( dir, dir );
			VectorAdd( b->xyz, dir, b->xyz );
			VectorSubtract( cent, c->xyz, dir );
			VectorNormalize( dir, dir );
			VectorAdd( c->xyz, dir, c->xyz );
		}
	}

	/* RBSP */
	for ( i = 0; i < MAX_LIGHTMAPS; i++ )
	{
		out->lightmapNum[ i ] = -3;
		out->lightmapStyles[ i ] = LS_NONE;
		out->vertexStyles[ i ] = LS_NONE;
	}
	out->lightmapStyles[ 0 ] = LS_NORMAL;
	out->vertexStyles[ 0 ] = LS_NORMAL;

	/* lightmap vectors (lod bounds for patches */
	VectorCopy( ds->lightmapOrigin, out->lightmapOrigin );
	VectorCopy( ds->lightmapVecs[ 0 ], out->lightmapVecs[ 0 ] );
	VectorCopy( ds->lightmapVecs[ 1 ], out->lightmapVecs[ 1 ] );
	VectorCopy( ds->lightmapVecs[ 2 ], out->lightmapVecs[ 2 ] );

	/* ydnar: gs mods: clear out the plane normal */
	if ( ds->planar == qfalse ) {
		VectorClear( out->lightmapVecs[ 2 ] );
	}

	/* optimize the surface's triangles */
	OptimizeTriangleSurface( ds );

	/* emit the verts and indexes */
	EmitDrawVerts( ds, out );
	EmitDrawIndexes( ds, out );

	/* add to count */
	numSurfacesByType[ ds->type ]++;
}