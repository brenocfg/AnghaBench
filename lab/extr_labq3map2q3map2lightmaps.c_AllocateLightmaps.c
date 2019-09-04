#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int surfaceFlags; } ;
typedef  TYPE_1__ shaderInfo_t ;
struct TYPE_9__ {scalar_t__ numVerts; scalar_t__ type; int lightmapNum; struct TYPE_9__* nextOnShader; TYPE_1__* shaderInfo; int /*<<< orphan*/  lightmapAxis; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_10__ {int firstDrawSurf; } ;
typedef  TYPE_3__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateLightmapForSurface (TYPE_2__*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int LIGHTMAP_HEIGHT ; 
 int LIGHTMAP_WIDTH ; 
 int MAX_MAP_SHADERS ; 
 scalar_t__ SURF_FACE ; 
 scalar_t__ SURF_META ; 
 int SURF_NOLIGHTMAP ; 
 scalar_t__ SURF_PATCH ; 
 int SURF_POINTLIGHT ; 
 scalar_t__ SURF_TERRAIN ; 
 int SURF_VERTEXLIT ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_exactLightmap ; 
 int /*<<< orphan*/  c_nonplanarLightmap ; 
 int /*<<< orphan*/  c_planarPatch ; 
 TYPE_2__* mapDrawSurfs ; 
 int numLightmaps ; 
 int numMapDrawSurfs ; 
 int numSortShaders ; 
 TYPE_2__** surfsOnShader ; 

void AllocateLightmaps( entity_t *e ){
	int i, j;
	mapDrawSurface_t    *ds;
	shaderInfo_t        *si;


	/* note it */
	Sys_FPrintf( SYS_VRB,"--- AllocateLightmaps ---\n" );


	/* sort all surfaces by shader so common shaders will usually be in the same lightmap */
	/* ydnar: this is done in two passes, because of an odd bug with lightmapped terrain */
	numSortShaders = 0;
	for ( i = e->firstDrawSurf; i < numMapDrawSurfs; i++ )
	{
		/* get surface and early out if possible */
		ds = &mapDrawSurfs[ i ];
		si = ds->shaderInfo;
		if ( si->surfaceFlags & SURF_VERTEXLIT ) {
			continue;
		}
		if ( ds->numVerts <= 0 ) {
			continue;
		}

		/* ydnar: handle brush faces and patches first */
		if ( ds->type != SURF_FACE && ds->type != SURF_PATCH ) {
			continue;
		}

		/* ydnar: this is unecessary because it should already be set */
		//% VectorCopy( ds->plane.normal, ds->lightmapVecs[ 2 ] );

		/* search for this shader */
		for ( j = 0 ; j < numSortShaders; j++ )
		{
			if ( ds->shaderInfo == surfsOnShader[ j ]->shaderInfo ) {
				ds->nextOnShader = surfsOnShader[ j ];
				surfsOnShader[ j ] = ds;
				break;
			}
		}

		/* new shader */
		if ( j == numSortShaders ) {
			if ( numSortShaders >= MAX_MAP_SHADERS ) {
				Error( "MAX_MAP_SHADERS" );
			}
			surfsOnShader[ j ] = ds;
			ds->nextOnShader = NULL;
			numSortShaders++;
		}
	}

	/* second pass, to allocate lightmapped terrain last */
	for ( i = e->firstDrawSurf; i < numMapDrawSurfs; i++ )
	{
		/* get surface and early out if possible */
		ds = &mapDrawSurfs[ i ];
		si = ds->shaderInfo;
		if ( si->surfaceFlags & SURF_VERTEXLIT ) {
			continue;
		}
		if ( ds->numVerts <= 0 ) {
			continue;
		}

		/* ydnar: this only handles metasurfaces and terrain */
		if ( ds->type != SURF_TERRAIN && ds->type != SURF_META ) {
			continue;
		}

		/* ydnar: a lightmap projection should be pre-stored for anything but excessively curved patches */
		if ( VectorLength( ds->lightmapAxis ) <= 0 ) {
			continue;
		}

		/* search for this shader */
		for ( j = 0; j < numSortShaders; j++ )
		{
			if ( ds->shaderInfo == surfsOnShader[ j ]->shaderInfo ) {
				ds->nextOnShader = surfsOnShader[ j ];
				surfsOnShader[ j ] = ds;
				break;
			}
		}

		/* new shader */
		if ( j == numSortShaders ) {
			if ( numSortShaders >= MAX_MAP_SHADERS ) {
				Error( "MAX_MAP_SHADERS" );
			}
			surfsOnShader[ j ] = ds;
			ds->nextOnShader = NULL;
			numSortShaders++;
		}
	}

	/* tot up shader count */
	Sys_FPrintf( SYS_VRB, "%9d unique shaders\n", numSortShaders );

	/* for each shader, allocate lightmaps for each surface */
	for ( i = 0; i < numSortShaders; i++ )
	{
		si = surfsOnShader[ i ]->shaderInfo;
		for ( ds = surfsOnShader[ i ]; ds; ds = ds->nextOnShader )
		{
			/* ydnar: promoting pointlight above nolightmap */
			if ( si->surfaceFlags & SURF_POINTLIGHT ) {
				ds->lightmapNum = -3;
			}
			else if ( si->surfaceFlags & SURF_NOLIGHTMAP ) {
				ds->lightmapNum = -1;
			}
			else{
				AllocateLightmapForSurface( ds );
			}
		}
	}

	/* emit some statistics */
	Sys_FPrintf( SYS_VRB, "%9d exact lightmap texels\n", c_exactLightmap );
	Sys_FPrintf( SYS_VRB, "%9d block lightmap texels\n", numLightmaps * LIGHTMAP_WIDTH * LIGHTMAP_HEIGHT );
	Sys_FPrintf( SYS_VRB, "%9d non-planar or terrain lightmap texels\n", c_nonplanarLightmap );
	Sys_FPrintf( SYS_VRB, "%9d planar patch lightmaps\n", c_planarPatch );
	Sys_FPrintf( SYS_VRB, "%9d lightmap textures, size: %d Kbytes\n", numLightmaps, ( numLightmaps * LIGHTMAP_WIDTH * LIGHTMAP_HEIGHT * 3 ) / 1024 );
}