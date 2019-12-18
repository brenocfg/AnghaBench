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
struct TYPE_8__ {int /*<<< orphan*/  lightmapAxis; int /*<<< orphan*/  sampleSize; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  recvShadows; int /*<<< orphan*/  castShadows; int /*<<< orphan*/  planeNum; int /*<<< orphan*/  surfaceNum; int /*<<< orphan*/  entityNum; int /*<<< orphan*/ * side; int /*<<< orphan*/  si; } ;
typedef  TYPE_2__ metaTriangle_t ;
struct TYPE_9__ {scalar_t__ type; int numVerts; int numIndexes; size_t* indexes; int /*<<< orphan*/  planeNum; int /*<<< orphan*/ * verts; int /*<<< orphan*/  lightmapAxis; int /*<<< orphan*/  sampleSize; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  recvShadows; int /*<<< orphan*/  castShadows; int /*<<< orphan*/  surfaceNum; int /*<<< orphan*/  entityNum; TYPE_1__* sideRef; int /*<<< orphan*/  shaderInfo; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
typedef  int /*<<< orphan*/  c ;
typedef  int /*<<< orphan*/  bspDrawVert_t ;
typedef  int /*<<< orphan*/  b ;
typedef  int /*<<< orphan*/  a ;
struct TYPE_7__ {int /*<<< orphan*/ * side; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearSurface (TYPE_3__*) ; 
 int /*<<< orphan*/  FindMetaTriangle (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SURFACE_BAD ; 
 scalar_t__ SURFACE_DECAL ; 
 scalar_t__ SURFACE_FACE ; 
 scalar_t__ SURFACE_FORCED_META ; 
 scalar_t__ SURFACE_META ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firstSearchMetaVert ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  numMetaSurfaces ; 
 int /*<<< orphan*/  numMetaVerts ; 

__attribute__((used)) static void SurfaceToMetaTriangles( mapDrawSurface_t *ds ){
	int i;
	metaTriangle_t src;
	bspDrawVert_t a, b, c;


	/* only handle certain types of surfaces */
	if ( ds->type != SURFACE_FACE &&
		 ds->type != SURFACE_META &&
		 ds->type != SURFACE_FORCED_META &&
		 ds->type != SURFACE_DECAL ) {
		return;
	}

	/* speed at the expense of memory */
	firstSearchMetaVert = numMetaVerts;

	/* only handle valid surfaces */
	if ( ds->type != SURFACE_BAD && ds->numVerts >= 3 && ds->numIndexes >= 3 ) {
		/* walk the indexes and create triangles */
		for ( i = 0; i < ds->numIndexes; i += 3 )
		{
			/* sanity check the indexes */
			if ( ds->indexes[ i ] == ds->indexes[ i + 1 ] ||
				 ds->indexes[ i ] == ds->indexes[ i + 2 ] ||
				 ds->indexes[ i + 1 ] == ds->indexes[ i + 2 ] ) {
				//%	Sys_Printf( "%d! ", ds->numVerts );
				continue;
			}

			/* build a metatriangle */
			src.si = ds->shaderInfo;
			src.side = ( ds->sideRef != NULL ? ds->sideRef->side : NULL );
			src.entityNum = ds->entityNum;
			src.surfaceNum = ds->surfaceNum;
			src.planeNum = ds->planeNum;
			src.castShadows = ds->castShadows;
			src.recvShadows = ds->recvShadows;
			src.fogNum = ds->fogNum;
			src.sampleSize = ds->sampleSize;
			VectorCopy( ds->lightmapAxis, src.lightmapAxis );

			/* copy drawverts */
			memcpy( &a, &ds->verts[ ds->indexes[ i ] ], sizeof( a ) );
			memcpy( &b, &ds->verts[ ds->indexes[ i + 1 ] ], sizeof( b ) );
			memcpy( &c, &ds->verts[ ds->indexes[ i + 2 ] ], sizeof( c ) );
			FindMetaTriangle( &src, &a, &b, &c, ds->planeNum );
		}

		/* add to count */
		numMetaSurfaces++;
	}

	/* clear the surface (free verts and indexes, sets it to SURFACE_BAD) */
	ClearSurface( ds );
}