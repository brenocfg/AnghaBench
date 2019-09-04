#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int numVerts; int patchHeight; int patchWidth; size_t outputNum; scalar_t__ planar; size_t type; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/ * bounds; int /*<<< orphan*/  lightmapOrigin; int /*<<< orphan*/  fogNum; TYPE_1__* shaderInfo; scalar_t__ sampleSize; int /*<<< orphan*/  lightmapAxis; TYPE_3__* verts; scalar_t__ backSide; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_16__ {int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ bspDrawVert_t ;
struct TYPE_17__ {int patchWidth; int patchHeight; int* lightmapNum; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; void** vertexStyles; void** lightmapStyles; int /*<<< orphan*/  fogNum; void* shaderNum; int /*<<< orphan*/  surfaceType; } ;
typedef  TYPE_4__ bspDrawSurface_t ;
struct TYPE_14__ {int surfaceFlags; int contentFlags; char* shader; scalar_t__ invert; } ;

/* Variables and functions */
 int /*<<< orphan*/  ApplySurfaceParm (char*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EmitDrawIndexes (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  EmitDrawVerts (TYPE_2__*,TYPE_4__*) ; 
 void* EmitShader (char*,int*,int*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 void* LS_NONE ; 
 void* LS_NORMAL ; 
 int MAX_LIGHTMAPS ; 
 size_t MAX_MAP_DRAW_SURFS ; 
 int /*<<< orphan*/  MST_PATCH ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 TYPE_4__* bspDrawSurfaces ; 
 scalar_t__ debugSurfaces ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 size_t numBSPDrawSurfaces ; 
 int /*<<< orphan*/ * numSurfacesByType ; 
 scalar_t__ patchMeta ; 
 scalar_t__ qfalse ; 

void EmitPatchSurface( mapDrawSurface_t *ds ){
	int i, j;
	bspDrawSurface_t    *out;
	int surfaceFlags, contentFlags;


	/* invert the surface if necessary */
	if ( ds->backSide || ds->shaderInfo->invert ) {
		bspDrawVert_t   *dv1, *dv2, temp;


		/* walk the verts, flip the normal */
		for ( i = 0; i < ds->numVerts; i++ )
			VectorScale( ds->verts[ i ].normal, -1.0f, ds->verts[ i ].normal );

		/* walk the verts again, but this time reverse their order */
		for ( j = 0; j < ds->patchHeight; j++ )
		{
			for ( i = 0; i < ( ds->patchWidth / 2 ); i++ )
			{
				dv1 = &ds->verts[ j * ds->patchWidth + i ];
				dv2 = &ds->verts[ j * ds->patchWidth + ( ds->patchWidth - i - 1 ) ];
				memcpy( &temp, dv1, sizeof( bspDrawVert_t ) );
				memcpy( dv1, dv2, sizeof( bspDrawVert_t ) );
				memcpy( dv2, &temp, sizeof( bspDrawVert_t ) );
			}
		}

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

	/* set it up */
	out->surfaceType = MST_PATCH;
	if ( debugSurfaces ) {
		out->shaderNum = EmitShader( "debugsurfaces", NULL, NULL );
	}
	else if ( patchMeta ) {
		/* patch meta requires that we have nodraw patches for collision */
		surfaceFlags = ds->shaderInfo->surfaceFlags;
		contentFlags = ds->shaderInfo->contentFlags;
		ApplySurfaceParm( "nodraw", &contentFlags, &surfaceFlags, NULL );
		ApplySurfaceParm( "pointlight", &contentFlags, &surfaceFlags, NULL );

		/* we don't want this patch getting lightmapped */
		VectorClear( ds->lightmapVecs[ 2 ] );
		VectorClear( ds->lightmapAxis );
		ds->sampleSize = 0;

		/* emit the new fake shader */
		out->shaderNum = EmitShader( ds->shaderInfo->shader, &contentFlags, &surfaceFlags );
	}
	else{
		out->shaderNum = EmitShader( ds->shaderInfo->shader, &ds->shaderInfo->contentFlags, &ds->shaderInfo->surfaceFlags );
	}
	out->patchWidth = ds->patchWidth;
	out->patchHeight = ds->patchHeight;
	out->fogNum = ds->fogNum;

	/* RBSP */
	for ( i = 0; i < MAX_LIGHTMAPS; i++ )
	{
		out->lightmapNum[ i ] = -3;
		out->lightmapStyles[ i ] = LS_NONE;
		out->vertexStyles[ i ] = LS_NONE;
	}
	out->lightmapStyles[ 0 ] = LS_NORMAL;
	out->vertexStyles[ 0 ] = LS_NORMAL;

	/* ydnar: gs mods: previously, the lod bounds were stored in lightmapVecs[ 0 ] and [ 1 ], moved to bounds[ 0 ] and [ 1 ] */
	VectorCopy( ds->lightmapOrigin, out->lightmapOrigin );
	VectorCopy( ds->bounds[ 0 ], out->lightmapVecs[ 0 ] );
	VectorCopy( ds->bounds[ 1 ], out->lightmapVecs[ 1 ] );
	VectorCopy( ds->lightmapVecs[ 2 ], out->lightmapVecs[ 2 ] );

	/* ydnar: gs mods: clear out the plane normal */
	if ( ds->planar == qfalse ) {
		VectorClear( out->lightmapVecs[ 2 ] );
	}

	/* emit the verts and indexes */
	EmitDrawVerts( ds, out );
	EmitDrawIndexes( ds, out );

	/* add to count */
	numSurfacesByType[ ds->type ]++;
}