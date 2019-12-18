#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_13__ {int fogNum; int numVerts; int type; TYPE_2__* verts; TYPE_1__* shaderInfo; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_14__ {TYPE_8__* brush; } ;
typedef  TYPE_4__ fog_t ;
typedef  int /*<<< orphan*/  entity_t ;
struct TYPE_15__ {scalar_t__* maxs; scalar_t__* mins; } ;
struct TYPE_12__ {int /*<<< orphan*/  xyz; } ;
struct TYPE_11__ {scalar_t__ noFog; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int ChopFaceSurfaceByBrush (int /*<<< orphan*/ *,TYPE_3__*,TYPE_8__*) ; 
 int ChopPatchSurfaceByBrush (int /*<<< orphan*/ *,TYPE_3__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ClearBounds (scalar_t__*,scalar_t__*) ; 
#define  SURFACE_FACE 132 
#define  SURFACE_FORCED_META 131 
#define  SURFACE_META 130 
#define  SURFACE_PATCH 129 
#define  SURFACE_TRIANGLES 128 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* mapDrawSurfs ; 
 TYPE_4__* mapFogs ; 
 int numFogFragments ; 
 int numFogPatchFragments ; 
 int numMapDrawSurfs ; 
 int numMapFogs ; 

void FogDrawSurfaces( entity_t *e ){
	int i, j, k, fogNum;
	fog_t               *fog;
	mapDrawSurface_t    *ds;
	vec3_t mins, maxs;
	int fogged, numFogged;
	int numBaseDrawSurfs;


	/* note it */
	Sys_FPrintf( SYS_VRB, "----- FogDrawSurfs -----\n" );

	/* reset counters */
	numFogged = 0;
	numFogFragments = 0;

	/* walk fog list */
	for ( fogNum = 0; fogNum < numMapFogs; fogNum++ )
	{
		/* get fog */
		fog = &mapFogs[ fogNum ];

		/* clip each surface into this, but don't clip any of the resulting fragments to the same brush */
		numBaseDrawSurfs = numMapDrawSurfs;
		for ( i = 0; i < numBaseDrawSurfs; i++ )
		{
			/* get the drawsurface */
			ds = &mapDrawSurfs[ i ];

			/* no fog? */
			if ( ds->shaderInfo->noFog ) {
				continue;
			}

			/* global fog doesn't have a brush */
			if ( fog->brush == NULL ) {
				/* don't re-fog already fogged surfaces */
				if ( ds->fogNum >= 0 ) {
					continue;
				}
				fogged = 1;
			}
			else
			{
				/* find drawsurface bounds */
				ClearBounds( mins, maxs );
				for ( j = 0; j < ds->numVerts; j++ )
					AddPointToBounds( ds->verts[ j ].xyz, mins, maxs );

				/* check against the fog brush */
				for ( k = 0; k < 3; k++ )
				{
					if ( mins[ k ] > fog->brush->maxs[ k ] ) {
						break;
					}
					if ( maxs[ k ] < fog->brush->mins[ k ] ) {
						break;
					}
				}

				/* no intersection? */
				if ( k < 3 ) {
					continue;
				}

				/* ydnar: gs mods: handle the various types of surfaces */
				switch ( ds->type )
				{
				/* handle brush faces */
				case SURFACE_FACE:
					fogged = ChopFaceSurfaceByBrush( e, ds, fog->brush );
					break;

				/* handle patches */
				case SURFACE_PATCH:
					fogged = ChopPatchSurfaceByBrush( e, ds, fog->brush );
					break;

				/* handle triangle surfaces (fixme: split triangle surfaces) */
				case SURFACE_TRIANGLES:
				case SURFACE_FORCED_META:
				case SURFACE_META:
					fogged = 1;
					break;

				/* no fogging */
				default:
					fogged = 0;
					break;
				}
			}

			/* is this surface fogged? */
			if ( fogged ) {
				numFogged += fogged;
				ds->fogNum = fogNum;
			}
		}
	}

	/* emit some statistics */
	Sys_FPrintf( SYS_VRB, "%9d fog polygon fragments\n", numFogFragments );
	Sys_FPrintf( SYS_VRB, "%9d fog patch fragments\n", numFogPatchFragments );
	Sys_FPrintf( SYS_VRB, "%9d fogged drawsurfs\n", numFogged );
}