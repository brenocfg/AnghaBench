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
struct TYPE_8__ {size_t type; size_t outputNum; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; void* lightStyle; int /*<<< orphan*/  fogNum; TYPE_1__* shaderInfo; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_9__ {int* lightmapNum; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; void** vertexStyles; void** lightmapStyles; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  shaderNum; int /*<<< orphan*/  surfaceType; } ;
typedef  TYPE_3__ bspDrawSurface_t ;
struct TYPE_7__ {int /*<<< orphan*/  surfaceFlags; int /*<<< orphan*/  contentFlags; int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  EmitShader (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Error (char*) ; 
 void* LS_NONE ; 
 int MAX_LIGHTMAPS ; 
 size_t MAX_MAP_DRAW_SURFS ; 
 int /*<<< orphan*/  MST_FLARE ; 
 size_t SURFACE_SHADER ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* bspDrawSurfaces ; 
 scalar_t__ emitFlares ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 size_t numBSPDrawSurfaces ; 
 int /*<<< orphan*/ * numSurfacesByType ; 
 scalar_t__ qfalse ; 

void EmitFlareSurface( mapDrawSurface_t *ds ){
	int i;
	bspDrawSurface_t        *out;


	/* ydnar: nuking useless flare drawsurfaces */
	if ( emitFlares == qfalse && ds->type != SURFACE_SHADER ) {
		return;
	}

	/* limit check */
	if ( numBSPDrawSurfaces == MAX_MAP_DRAW_SURFS ) {
		Error( "MAX_MAP_DRAW_SURFS" );
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
	out->surfaceType = MST_FLARE;
	out->shaderNum = EmitShader( ds->shaderInfo->shader, &ds->shaderInfo->contentFlags, &ds->shaderInfo->surfaceFlags );
	out->fogNum = ds->fogNum;

	/* RBSP */
	for ( i = 0; i < MAX_LIGHTMAPS; i++ )
	{
		out->lightmapNum[ i ] = -3;
		out->lightmapStyles[ i ] = LS_NONE;
		out->vertexStyles[ i ] = LS_NONE;
	}
	out->lightmapStyles[ 0 ] = ds->lightStyle;
	out->vertexStyles[ 0 ] = ds->lightStyle;

	VectorCopy( ds->lightmapOrigin, out->lightmapOrigin );          /* origin */
	VectorCopy( ds->lightmapVecs[ 0 ], out->lightmapVecs[ 0 ] );    /* color */
	VectorCopy( ds->lightmapVecs[ 1 ], out->lightmapVecs[ 1 ] );
	VectorCopy( ds->lightmapVecs[ 2 ], out->lightmapVecs[ 2 ] );    /* normal */

	/* add to count */
	numSurfacesByType[ ds->type ]++;
}