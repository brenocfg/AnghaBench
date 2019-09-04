#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numSurfaceClusters; int firstSurfaceCluster; } ;
typedef  TYPE_1__ surfaceInfo_t ;
struct TYPE_6__ {size_t firstLightSurface; int numLightSurfaces; int numLightClusters; int sw; int w; int sh; int h; int* superClusters; int /*<<< orphan*/ * bspDeluxels; int /*<<< orphan*/ * superDeluxels; int /*<<< orphan*/ * superNormals; int /*<<< orphan*/ * superOrigins; int /*<<< orphan*/ ** superLuxels; int /*<<< orphan*/ ** radLuxels; int /*<<< orphan*/ ** bspLuxels; int /*<<< orphan*/  origin; int /*<<< orphan*/ * vecs; int /*<<< orphan*/ * styles; int /*<<< orphan*/ * lightClusters; } ;
typedef  TYPE_2__ rawLightmap_t ;

/* Variables and functions */
 int BSP_DELUXEL_SIZE ; 
 int BSP_LUXEL_SIZE ; 
 int /*<<< orphan*/  CLUSTER_UNMAPPED ; 
 int /*<<< orphan*/  CompareLightSurface ; 
 int /*<<< orphan*/  LS_NONE ; 
 int /*<<< orphan*/  LS_NORMAL ; 
 int MAX_LIGHTMAPS ; 
 int RAD_LUXEL_SIZE ; 
 int SUPER_DELUXEL_SIZE ; 
 int SUPER_LUXEL_SIZE ; 
 int SUPER_NORMAL_SIZE ; 
 int SUPER_ORIGIN_SIZE ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 scalar_t__ bounce ; 
 scalar_t__ deluxemap ; 
 size_t* lightSurfaces ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int numLuxels ; 
 int numRawSuperLuxels ; 
 int /*<<< orphan*/  qsort (size_t*,int,int,int /*<<< orphan*/ ) ; 
 void* safe_malloc (int) ; 
 int superSample ; 
 int /*<<< orphan*/ * surfaceClusters ; 
 TYPE_1__* surfaceInfos ; 

void FinishRawLightmap( rawLightmap_t *lm ){
	int i, j, c, size, *sc;
	float is;
	surfaceInfo_t       *info;


	/* sort light surfaces by shader name */
	qsort( &lightSurfaces[ lm->firstLightSurface ], lm->numLightSurfaces, sizeof( int ), CompareLightSurface );

	/* count clusters */
	lm->numLightClusters = 0;
	for ( i = 0; i < lm->numLightSurfaces; i++ )
	{
		/* get surface info */
		info = &surfaceInfos[ lightSurfaces[ lm->firstLightSurface + i ] ];

		/* add surface clusters */
		lm->numLightClusters += info->numSurfaceClusters;
	}

	/* allocate buffer for clusters and copy */
	lm->lightClusters = safe_malloc( lm->numLightClusters * sizeof( *lm->lightClusters ) );
	c = 0;
	for ( i = 0; i < lm->numLightSurfaces; i++ )
	{
		/* get surface info */
		info = &surfaceInfos[ lightSurfaces[ lm->firstLightSurface + i ] ];

		/* add surface clusters */
		for ( j = 0; j < info->numSurfaceClusters; j++ )
			lm->lightClusters[ c++ ] = surfaceClusters[ info->firstSurfaceCluster + j ];
	}

	/* set styles */
	lm->styles[ 0 ] = LS_NORMAL;
	for ( i = 1; i < MAX_LIGHTMAPS; i++ )
		lm->styles[ i ] = LS_NONE;

	/* set supersampling size */
	lm->sw = lm->w * superSample;
	lm->sh = lm->h * superSample;

	/* add to super luxel count */
	numRawSuperLuxels += ( lm->sw * lm->sh );

	/* manipulate origin/vecs for supersampling */
	if ( superSample > 1 && lm->vecs != NULL ) {
		/* calc inverse supersample */
		is = 1.0f / superSample;

		/* scale the vectors and shift the origin */
		#if 1
		/* new code that works for arbitrary supersampling values */
		VectorMA( lm->origin, -0.5, lm->vecs[ 0 ], lm->origin );
		VectorMA( lm->origin, -0.5, lm->vecs[ 1 ], lm->origin );
		VectorScale( lm->vecs[ 0 ], is, lm->vecs[ 0 ] );
		VectorScale( lm->vecs[ 1 ], is, lm->vecs[ 1 ] );
		VectorMA( lm->origin, is, lm->vecs[ 0 ], lm->origin );
		VectorMA( lm->origin, is, lm->vecs[ 1 ], lm->origin );
		#else
		/* old code that only worked with a value of 2 */
		VectorScale( lm->vecs[ 0 ], is, lm->vecs[ 0 ] );
		VectorScale( lm->vecs[ 1 ], is, lm->vecs[ 1 ] );
		VectorMA( lm->origin, -is, lm->vecs[ 0 ], lm->origin );
		VectorMA( lm->origin, -is, lm->vecs[ 1 ], lm->origin );
		#endif
	}

	/* allocate bsp lightmap storage */
	size = lm->w * lm->h * BSP_LUXEL_SIZE * sizeof( float );
	if ( lm->bspLuxels[ 0 ] == NULL ) {
		lm->bspLuxels[ 0 ] = safe_malloc( size );
	}
	memset( lm->bspLuxels[ 0 ], 0, size );

	/* allocate radiosity lightmap storage */
	if ( bounce ) {
		size = lm->w * lm->h * RAD_LUXEL_SIZE * sizeof( float );
		if ( lm->radLuxels[ 0 ] == NULL ) {
			lm->radLuxels[ 0 ] = safe_malloc( size );
		}
		memset( lm->radLuxels[ 0 ], 0, size );
	}

	/* allocate sampling lightmap storage */
	size = lm->sw * lm->sh * SUPER_LUXEL_SIZE * sizeof( float );
	if ( lm->superLuxels[ 0 ] == NULL ) {
		lm->superLuxels[ 0 ] = safe_malloc( size );
	}
	memset( lm->superLuxels[ 0 ], 0, size );

	/* allocate origin map storage */
	size = lm->sw * lm->sh * SUPER_ORIGIN_SIZE * sizeof( float );
	if ( lm->superOrigins == NULL ) {
		lm->superOrigins = safe_malloc( size );
	}
	memset( lm->superOrigins, 0, size );

	/* allocate normal map storage */
	size = lm->sw * lm->sh * SUPER_NORMAL_SIZE * sizeof( float );
	if ( lm->superNormals == NULL ) {
		lm->superNormals = safe_malloc( size );
	}
	memset( lm->superNormals, 0, size );

	/* allocate cluster map storage */
	size = lm->sw * lm->sh * sizeof( int );
	if ( lm->superClusters == NULL ) {
		lm->superClusters = safe_malloc( size );
	}
	size = lm->sw * lm->sh;
	sc = lm->superClusters;
	for ( i = 0; i < size; i++ )
		( *sc++ ) = CLUSTER_UNMAPPED;

	/* deluxemap allocation */
	if ( deluxemap ) {
		/* allocate sampling deluxel storage */
		size = lm->sw * lm->sh * SUPER_DELUXEL_SIZE * sizeof( float );
		if ( lm->superDeluxels == NULL ) {
			lm->superDeluxels = safe_malloc( size );
		}
		memset( lm->superDeluxels, 0, size );

		/* allocate bsp deluxel storage */
		size = lm->w * lm->h * BSP_DELUXEL_SIZE * sizeof( float );
		if ( lm->bspDeluxels == NULL ) {
			lm->bspDeluxels = safe_malloc( size );
		}
		memset( lm->bspDeluxels, 0, size );
	}

	/* add to count */
	numLuxels += ( lm->sw * lm->sh );
}