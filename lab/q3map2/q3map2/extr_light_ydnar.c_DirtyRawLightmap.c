#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int numSurfaces; size_t* surfaces; int cluster; int /*<<< orphan*/  normal; int /*<<< orphan*/  origin; void* twoSided; void* testAll; int /*<<< orphan*/  inhibitRadius; int /*<<< orphan*/  recvShadows; void* forceSunlight; void* testOcclusion; } ;
typedef  TYPE_2__ trace_t ;
struct TYPE_10__ {TYPE_1__* si; } ;
typedef  TYPE_3__ surfaceInfo_t ;
struct TYPE_11__ {int numLightSurfaces; size_t firstLightSurface; int sh; int sw; int /*<<< orphan*/  recvShadows; } ;
typedef  TYPE_4__ rawLightmap_t ;
struct TYPE_8__ {scalar_t__ twoSided; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_INHIBIT_RADIUS ; 
 float DirtForSample (TYPE_2__*) ; 
 int* SUPER_CLUSTER (int,int) ; 
 float* SUPER_DIRT (int,int) ; 
 float* SUPER_NORMAL (int,int) ; 
 float* SUPER_ORIGIN (int,int) ; 
 int /*<<< orphan*/  VectorCopy (float*,int /*<<< orphan*/ ) ; 
 size_t* lightSurfaces ; 
 int numRawLightmaps ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_4__* rawLightmaps ; 
 TYPE_3__* surfaceInfos ; 

void DirtyRawLightmap( int rawLightmapNum ){
	int i, x, y, sx, sy, *cluster;
	float               *origin, *normal, *dirt, *dirt2, average, samples;
	rawLightmap_t       *lm;
	surfaceInfo_t       *info;
	trace_t trace;


	/* bail if this number exceeds the number of raw lightmaps */
	if ( rawLightmapNum >= numRawLightmaps ) {
		return;
	}

	/* get lightmap */
	lm = &rawLightmaps[ rawLightmapNum ];

	/* setup trace */
	trace.testOcclusion = qtrue;
	trace.forceSunlight = qfalse;
	trace.recvShadows = lm->recvShadows;
	trace.numSurfaces = lm->numLightSurfaces;
	trace.surfaces = &lightSurfaces[ lm->firstLightSurface ];
	trace.inhibitRadius = DEFAULT_INHIBIT_RADIUS;
	trace.testAll = qfalse;

	/* twosided lighting (may or may not be a good idea for lightmapped stuff) */
	trace.twoSided = qfalse;
	for ( i = 0; i < trace.numSurfaces; i++ )
	{
		/* get surface */
		info = &surfaceInfos[ trace.surfaces[ i ] ];

		/* check twosidedness */
		if ( info->si->twoSided ) {
			trace.twoSided = qtrue;
			break;
		}
	}

	/* gather dirt */
	for ( y = 0; y < lm->sh; y++ )
	{
		for ( x = 0; x < lm->sw; x++ )
		{
			/* get luxel */
			cluster = SUPER_CLUSTER( x, y );
			origin = SUPER_ORIGIN( x, y );
			normal = SUPER_NORMAL( x, y );
			dirt = SUPER_DIRT( x, y );

			/* set default dirt */
			*dirt = 0.0f;

			/* only look at mapped luxels */
			if ( *cluster < 0 ) {
				continue;
			}

			/* copy to trace */
			trace.cluster = *cluster;
			VectorCopy( origin, trace.origin );
			VectorCopy( normal, trace.normal );

			/* get dirt */
			*dirt = DirtForSample( &trace );
		}
	}

	/* testing no filtering */
	//%	return;

	/* filter dirt */
	for ( y = 0; y < lm->sh; y++ )
	{
		for ( x = 0; x < lm->sw; x++ )
		{
			/* get luxel */
			cluster = SUPER_CLUSTER( x, y );
			dirt = SUPER_DIRT( x, y );

			/* filter dirt by adjacency to unmapped luxels */
			average = *dirt;
			samples = 1.0f;
			for ( sy = ( y - 1 ); sy <= ( y + 1 ); sy++ )
			{
				if ( sy < 0 || sy >= lm->sh ) {
					continue;
				}

				for ( sx = ( x - 1 ); sx <= ( x + 1 ); sx++ )
				{
					if ( sx < 0 || sx >= lm->sw || ( sx == x && sy == y ) ) {
						continue;
					}

					/* get neighboring luxel */
					cluster = SUPER_CLUSTER( sx, sy );
					dirt2 = SUPER_DIRT( sx, sy );
					if ( *cluster < 0 || *dirt2 <= 0.0f ) {
						continue;
					}

					/* add it */
					average += *dirt2;
					samples += 1.0f;
				}

				/* bail */
				if ( samples <= 0.0f ) {
					break;
				}
			}

			/* bail */
			if ( samples <= 0.0f ) {
				continue;
			}

			/* scale dirt */
			*dirt = average / samples;
		}
	}
}