#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_8__ {int /*<<< orphan*/ * si; int /*<<< orphan*/  side; int /*<<< orphan*/  lightmapAxis; int /*<<< orphan*/  sampleSize; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  planeNum; int /*<<< orphan*/  recvShadows; int /*<<< orphan*/  castShadows; int /*<<< orphan*/  surfaceNum; int /*<<< orphan*/  entityNum; } ;
typedef  TYPE_1__ metaTriangle_t ;
struct TYPE_9__ {int* verts; int* indexes; int numVerts; int numIndexes; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  sideRef; int /*<<< orphan*/  lightmapAxis; int /*<<< orphan*/  sampleSize; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  planeNum; int /*<<< orphan*/ * shaderInfo; int /*<<< orphan*/  recvShadows; int /*<<< orphan*/  castShadows; int /*<<< orphan*/  surfaceNum; int /*<<< orphan*/  entityNum; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
typedef  int bspDrawVert_t ;

/* Variables and functions */
 int ADEQUATE_SCORE ; 
 int AddMetaTriangleToSurface (TYPE_2__*,TYPE_1__*,scalar_t__) ; 
 TYPE_2__* AllocDrawSurface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AllocSideRef (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClassifySurfaces (int,TYPE_2__*) ; 
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GOOD_SCORE ; 
 int /*<<< orphan*/  SURFACE_META ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 int maxSurfaceIndexes ; 
 int maxSurfaceVerts ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numMergedSurfaces ; 
 int numMetaTriangles ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 void* safe_malloc (int) ; 

__attribute__((used)) static void MetaTrianglesToSurface( int numPossibles, metaTriangle_t *possibles, int *fOld, int *numAdded ){
	int i, j, f, best, score, bestScore;
	metaTriangle_t      *seed, *test;
	mapDrawSurface_t    *ds;
	bspDrawVert_t       *verts;
	int                 *indexes;
	qboolean added;


	/* allocate arrays */
	verts = safe_malloc( sizeof( *verts ) * maxSurfaceVerts );
	indexes = safe_malloc( sizeof( *indexes ) * maxSurfaceIndexes );

	/* walk the list of triangles */
	for ( i = 0, seed = possibles; i < numPossibles; i++, seed++ )
	{
		/* skip this triangle if it has already been merged */
		if ( seed->si == NULL ) {
			continue;
		}

		/* -----------------------------------------------------------------
		   initial drawsurf construction
		   ----------------------------------------------------------------- */

		/* start a new drawsurface */
		ds = AllocDrawSurface( SURFACE_META );
		ds->entityNum = seed->entityNum;
		ds->surfaceNum = seed->surfaceNum;
		ds->castShadows = seed->castShadows;
		ds->recvShadows = seed->recvShadows;

		ds->shaderInfo = seed->si;
		ds->planeNum = seed->planeNum;
		ds->fogNum = seed->fogNum;
		ds->sampleSize = seed->sampleSize;
		ds->verts = verts;
		ds->indexes = indexes;
		VectorCopy( seed->lightmapAxis, ds->lightmapAxis );
		ds->sideRef = AllocSideRef( seed->side, NULL );

		ClearBounds( ds->mins, ds->maxs );

		/* clear verts/indexes */
		memset( verts, 0, sizeof( *verts ) * maxSurfaceVerts );
		memset( indexes, 0, sizeof( *indexes ) * maxSurfaceIndexes );

		/* add the first triangle */
		if ( AddMetaTriangleToSurface( ds, seed, qfalse ) ) {
			( *numAdded )++;
		}

		/* -----------------------------------------------------------------
		   add triangles
		   ----------------------------------------------------------------- */

		/* progressively walk the list until no more triangles can be added */
		added = qtrue;
		while ( added )
		{
			/* print pacifier */
			f = 10 * *numAdded / numMetaTriangles;
			if ( f > *fOld ) {
				*fOld = f;
				Sys_FPrintf( SYS_VRB, "%d...", f );
			}

			/* reset best score */
			best = -1;
			bestScore = 0;
			added = qfalse;

			/* walk the list of possible candidates for merging */
			for ( j = i + 1, test = &possibles[ j ]; j < numPossibles; j++, test++ )
			{
				/* skip this triangle if it has already been merged */
				if ( test->si == NULL ) {
					continue;
				}

				/* score this triangle */
				score = AddMetaTriangleToSurface( ds, test, qtrue );
				if ( score > bestScore ) {
					best = j;
					bestScore = score;

					/* if we have a score over a certain threshold, just use it */
					if ( bestScore >= GOOD_SCORE ) {
						if ( AddMetaTriangleToSurface( ds, &possibles[ best ], qfalse ) ) {
							( *numAdded )++;
						}

						/* reset */
						best = -1;
						bestScore = 0;
						added = qtrue;
					}
				}
			}

			/* add best candidate */
			if ( best >= 0 && bestScore > ADEQUATE_SCORE ) {
				if ( AddMetaTriangleToSurface( ds, &possibles[ best ], qfalse ) ) {
					( *numAdded )++;
				}

				/* reset */
				added = qtrue;
			}
		}

		/* copy the verts and indexes to the new surface */
		ds->verts = safe_malloc( ds->numVerts * sizeof( bspDrawVert_t ) );
		memcpy( ds->verts, verts, ds->numVerts * sizeof( bspDrawVert_t ) );
		ds->indexes = safe_malloc( ds->numIndexes * sizeof( int ) );
		memcpy( ds->indexes, indexes, ds->numIndexes * sizeof( int ) );

		/* classify the surface */
		ClassifySurfaces( 1, ds );

		/* add to count */
		numMergedSurfaces++;
	}

	/* free arrays */
	free( verts );
	free( indexes );
}