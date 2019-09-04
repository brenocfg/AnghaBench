#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_15__ {int testOcclusion; int numSurfaces; int* surfaces; int testAll; scalar_t__ cluster; float* origin; float* normal; int /*<<< orphan*/  twoSided; int /*<<< orphan*/  inhibitRadius; int /*<<< orphan*/  recvShadows; int /*<<< orphan*/  forceSunlight; } ;
typedef  TYPE_2__ trace_t ;
struct TYPE_16__ {float* maxs; float* mins; size_t firstSurfaceCluster; TYPE_1__* si; int /*<<< orphan*/  numSurfaceClusters; int /*<<< orphan*/  recvShadows; TYPE_4__* lm; } ;
typedef  TYPE_3__ surfaceInfo_t ;
struct TYPE_17__ {float* mins; int sw; int sh; int /*<<< orphan*/ ** superLuxels; int /*<<< orphan*/ * styles; } ;
typedef  TYPE_4__ rawLightmap_t ;
struct TYPE_18__ {float* normal; float* xyz; int** lightmap; int /*<<< orphan*/ * color; } ;
typedef  TYPE_5__ bspDrawVert_t ;
struct TYPE_19__ {int firstVert; int numVerts; int /*<<< orphan*/ * vertexStyles; } ;
typedef  TYPE_6__ bspDrawSurface_t ;
typedef  int /*<<< orphan*/  avgColors ;
struct TYPE_14__ {float vertexScale; int /*<<< orphan*/  noVertexLight; int /*<<< orphan*/  twoSided; int /*<<< orphan*/  forceSunlight; } ;

/* Variables and functions */
 void* ClusterForPointExtFilter (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ColorToBytes (float*,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  CreateTraceLightsForSurface (int,TYPE_2__*) ; 
 int /*<<< orphan*/  DEFAULT_INHIBIT_RADIUS ; 
 float DirtForSample (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeTraceLights (TYPE_2__*) ; 
 int /*<<< orphan*/  LightingAtSample (TYPE_2__*,int /*<<< orphan*/ *,float**) ; 
 int MAX_LIGHTMAPS ; 
 float* RAD_VERTEX_LUXEL (int,int) ; 
 int* SUPER_CLUSTER (int,int) ; 
 float* SUPER_LUXEL (int,int,int) ; 
 int /*<<< orphan*/  VERTEX_EPSILON ; 
 float* VERTEX_LUXEL (int,int) ; 
 int VERTEX_NUDGE ; 
 int /*<<< orphan*/  VectorAdd (float*,float*,float*) ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  VectorDivide (float*,float,float*) ; 
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 
 int /*<<< orphan*/  VectorSet (float*,float,float,float) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 
 float* ambientColor ; 
 scalar_t__ bounce ; 
 int /*<<< orphan*/  bounceOnly ; 
 scalar_t__ bouncing ; 
 TYPE_6__* bspDrawSurfaces ; 
 scalar_t__ cpmaHack ; 
 float** debugColors ; 
 scalar_t__ debugOrigin ; 
 scalar_t__ debugSurfaces ; 
 scalar_t__ dirty ; 
 int /*<<< orphan*/  master_mutex ; 
 int /*<<< orphan*/  memset (float**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  noTrace ; 
 scalar_t__ normalmap ; 
 int /*<<< orphan*/  numVertsIlluminated ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int qfalse ; 
 int /*<<< orphan*/ * surfaceClusters ; 
 TYPE_3__* surfaceInfos ; 
 TYPE_5__* yDrawVerts ; 

void IlluminateVertexes( int num ){
	int i, x, y, z, x1, y1, z1, sx, sy, radius, maxRadius, *cluster;
	int lightmapNum, numAvg;
	float samples, *vertLuxel, *radVertLuxel, *luxel, dirt = 0.0f;
	vec3_t origin = {0, 0, 0}, temp, temp2, colors[ MAX_LIGHTMAPS ], avgColors[ MAX_LIGHTMAPS ];
	bspDrawSurface_t    *ds;
	surfaceInfo_t       *info;
	rawLightmap_t       *lm;
	bspDrawVert_t       *verts;
	trace_t             trace = {};

	/* get surface, info, and raw lightmap */
	ds = &bspDrawSurfaces[ num ];
	info = &surfaceInfos[ num ];
	lm = info->lm;

	/* -----------------------------------------------------------------
	   illuminate the vertexes
	   ----------------------------------------------------------------- */

	/* calculate vertex lighting for surfaces without lightmaps */
	if ( lm == NULL || cpmaHack ) {
		/* setup trace */
		trace.testOcclusion = ( cpmaHack && lm != NULL ) ? qfalse : !noTrace;
		trace.forceSunlight = info->si->forceSunlight;
		trace.recvShadows = info->recvShadows;
		trace.numSurfaces = 1;
		trace.surfaces = &num;
		trace.inhibitRadius = DEFAULT_INHIBIT_RADIUS;
		trace.testAll = qfalse;

		/* twosided lighting */
		trace.twoSided = info->si->twoSided;

		/* make light list for this surface */
		CreateTraceLightsForSurface( num, &trace );

		/* setup */
		verts = yDrawVerts + ds->firstVert;
		numAvg = 0;
		memset( avgColors, 0, sizeof( avgColors ) );

		/* walk the surface verts */
		for ( i = 0; i < ds->numVerts; i++ )
		{
			/* get vertex luxel */
			radVertLuxel = RAD_VERTEX_LUXEL( 0, ds->firstVert + i );

			/* color the luxel with raw lightmap num? */
			if ( debugSurfaces ) {
				VectorCopy( debugColors[ num % 12 ], radVertLuxel );
			}

			/* color the luxel with luxel origin? */
			else if ( debugOrigin ) {
				VectorSubtract( info->maxs, info->mins, temp );
				VectorScale( temp, ( 1.0f / 255.0f ), temp );
				VectorSubtract( origin, lm->mins, temp2 );
				radVertLuxel[ 0 ] = info->mins[ 0 ] + ( temp[ 0 ] * temp2[ 0 ] );
				radVertLuxel[ 1 ] = info->mins[ 1 ] + ( temp[ 1 ] * temp2[ 1 ] );
				radVertLuxel[ 2 ] = info->mins[ 2 ] + ( temp[ 2 ] * temp2[ 2 ] );
			}

			/* color the luxel with the normal */
			else if ( normalmap ) {
				radVertLuxel[ 0 ] = ( verts[ i ].normal[ 0 ] + 1.0f ) * 127.5f;
				radVertLuxel[ 1 ] = ( verts[ i ].normal[ 1 ] + 1.0f ) * 127.5f;
				radVertLuxel[ 2 ] = ( verts[ i ].normal[ 2 ] + 1.0f ) * 127.5f;
			}

			/* illuminate the vertex */
			else
			{
				/* clear vertex luxel */
				VectorSet( radVertLuxel, -1.0f, -1.0f, -1.0f );

				/* try at initial origin */
				trace.cluster = ClusterForPointExtFilter( verts[ i ].xyz, VERTEX_EPSILON, info->numSurfaceClusters, &surfaceClusters[ info->firstSurfaceCluster ] );
				if ( trace.cluster >= 0 ) {
					/* setup trace */
					VectorCopy( verts[ i ].xyz, trace.origin );
					VectorCopy( verts[ i ].normal, trace.normal );

					/* r7 dirt */
					if ( dirty ) {
						dirt = DirtForSample( &trace );
					}
					else{
						dirt = 1.0f;
					}

					/* trace */
					LightingAtSample( &trace, ds->vertexStyles, colors );

					/* store */
					for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
					{
						/* r7 dirt */
						VectorScale( colors[ lightmapNum ], dirt, colors[ lightmapNum ] );

						/* store */
						radVertLuxel = RAD_VERTEX_LUXEL( lightmapNum, ds->firstVert + i );
						VectorCopy( colors[ lightmapNum ], radVertLuxel );
						VectorAdd( avgColors[ lightmapNum ], colors[ lightmapNum ], colors[ lightmapNum ] );
					}
				}

				/* is this sample bright enough? */
				radVertLuxel = RAD_VERTEX_LUXEL( 0, ds->firstVert + i );
				if ( radVertLuxel[ 0 ] <= ambientColor[ 0 ] &&
					 radVertLuxel[ 1 ] <= ambientColor[ 1 ] &&
					 radVertLuxel[ 2 ] <= ambientColor[ 2 ] ) {
					/* nudge the sample point around a bit */
					for ( x = 0; x < 4; x++ )
					{
						/* two's complement 0, 1, -1, 2, -2, etc */
						x1 = ( ( x >> 1 ) ^ ( x & 1 ? -1 : 0 ) ) + ( x & 1 );

						for ( y = 0; y < 4; y++ )
						{
							y1 = ( ( y >> 1 ) ^ ( y & 1 ? -1 : 0 ) ) + ( y & 1 );

							for ( z = 0; z < 4; z++ )
							{
								z1 = ( ( z >> 1 ) ^ ( z & 1 ? -1 : 0 ) ) + ( z & 1 );

								/* nudge origin */
								trace.origin[ 0 ] = verts[ i ].xyz[ 0 ] + ( VERTEX_NUDGE * x1 );
								trace.origin[ 1 ] = verts[ i ].xyz[ 1 ] + ( VERTEX_NUDGE * y1 );
								trace.origin[ 2 ] = verts[ i ].xyz[ 2 ] + ( VERTEX_NUDGE * z1 );

								/* try at nudged origin */
								trace.cluster = ClusterForPointExtFilter( origin, VERTEX_EPSILON, info->numSurfaceClusters, &surfaceClusters[ info->firstSurfaceCluster ] );
								if ( trace.cluster < 0 ) {
									continue;
								}

								/* trace */
								LightingAtSample( &trace, ds->vertexStyles, colors );

								/* store */
								for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
								{
									/* r7 dirt */
									VectorScale( colors[ lightmapNum ], dirt, colors[ lightmapNum ] );

									/* store */
									radVertLuxel = RAD_VERTEX_LUXEL( lightmapNum, ds->firstVert + i );
									VectorCopy( colors[ lightmapNum ], radVertLuxel );
								}

								/* bright enough? */
								radVertLuxel = RAD_VERTEX_LUXEL( 0, ds->firstVert + i );
								if ( radVertLuxel[ 0 ] > ambientColor[ 0 ] ||
									 radVertLuxel[ 1 ] > ambientColor[ 1 ] ||
									 radVertLuxel[ 2 ] > ambientColor[ 2 ] ) {
									x = y = z = 1000;
								}
							}
						}
					}
				}

				/* add to average? */
				radVertLuxel = RAD_VERTEX_LUXEL( 0, ds->firstVert + i );
				if ( radVertLuxel[ 0 ] > ambientColor[ 0 ] ||
					 radVertLuxel[ 1 ] > ambientColor[ 1 ] ||
					 radVertLuxel[ 2 ] > ambientColor[ 2 ] ) {
					numAvg++;
					for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
					{
						radVertLuxel = RAD_VERTEX_LUXEL( lightmapNum, ds->firstVert + i );
						VectorAdd( avgColors[ lightmapNum ], radVertLuxel, avgColors[ lightmapNum ] );
					}
				}
			}

			/* another happy customer */
			pthread_mutex_lock( &master_mutex );
			numVertsIlluminated++;
			pthread_mutex_unlock( &master_mutex );
		}

		/* set average color */
		if ( numAvg > 0 ) {
			for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
				VectorScale( avgColors[ lightmapNum ], ( 1.0f / numAvg ), avgColors[ lightmapNum ] );
		}
		else
		{
			VectorCopy( ambientColor, avgColors[ 0 ] );
		}

		/* clean up and store vertex color */
		for ( i = 0; i < ds->numVerts; i++ )
		{
			/* get vertex luxel */
			radVertLuxel = RAD_VERTEX_LUXEL( 0, ds->firstVert + i );

			/* store average in occluded vertexes */
			if ( radVertLuxel[ 0 ] < 0.0f ) {
				for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
				{
					radVertLuxel = RAD_VERTEX_LUXEL( lightmapNum, ds->firstVert + i );
					VectorCopy( avgColors[ lightmapNum ], radVertLuxel );

					/* debug code */
					//%	VectorSet( radVertLuxel, 255.0f, 0.0f, 0.0f );
				}
			}

			/* store it */
			for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
			{
				/* get luxels */
				vertLuxel = VERTEX_LUXEL( lightmapNum, ds->firstVert + i );
				radVertLuxel = RAD_VERTEX_LUXEL( lightmapNum, ds->firstVert + i );

				/* store */
				if ( bouncing || bounce == 0 || !bounceOnly ) {
					VectorAdd( vertLuxel, radVertLuxel, vertLuxel );
				}
				if ( !info->si->noVertexLight ) {
					ColorToBytes( vertLuxel, verts[ i ].color[ lightmapNum ], info->si->vertexScale );
				}
			}
		}

		/* free light list */
		FreeTraceLights( &trace );

		/* return to sender */
		return;
	}

	/* -----------------------------------------------------------------
	   reconstitute vertex lighting from the luxels
	   ----------------------------------------------------------------- */

	/* set styles from lightmap */
	for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
		ds->vertexStyles[ lightmapNum ] = lm->styles[ lightmapNum ];

	/* get max search radius */
	maxRadius = lm->sw;
	maxRadius = maxRadius > lm->sh ? maxRadius : lm->sh;

	/* walk the surface verts */
	verts = yDrawVerts + ds->firstVert;
	for ( i = 0; i < ds->numVerts; i++ )
	{
		/* do each lightmap */
		for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
		{
			/* early out */
			if ( lm->superLuxels[ lightmapNum ] == NULL ) {
				continue;
			}

			/* get luxel coords */
			x = verts[ i ].lightmap[ lightmapNum ][ 0 ];
			y = verts[ i ].lightmap[ lightmapNum ][ 1 ];
			if ( x < 0 ) {
				x = 0;
			}
			else if ( x >= lm->sw ) {
				x = lm->sw - 1;
			}
			if ( y < 0 ) {
				y = 0;
			}
			else if ( y >= lm->sh ) {
				y = lm->sh - 1;
			}

			/* get vertex luxels */
			vertLuxel = VERTEX_LUXEL( lightmapNum, ds->firstVert + i );
			radVertLuxel = RAD_VERTEX_LUXEL( lightmapNum, ds->firstVert + i );

			/* color the luxel with the normal? */
			if ( normalmap ) {
				radVertLuxel[ 0 ] = ( verts[ i ].normal[ 0 ] + 1.0f ) * 127.5f;
				radVertLuxel[ 1 ] = ( verts[ i ].normal[ 1 ] + 1.0f ) * 127.5f;
				radVertLuxel[ 2 ] = ( verts[ i ].normal[ 2 ] + 1.0f ) * 127.5f;
			}

			/* color the luxel with surface num? */
			else if ( debugSurfaces ) {
				VectorCopy( debugColors[ num % 12 ], radVertLuxel );
			}

			/* divine color from the superluxels */
			else
			{
				/* increasing radius */
				VectorClear( radVertLuxel );
				samples = 0.0f;
				for ( radius = 0; radius < maxRadius && samples <= 0.0f; radius++ )
				{
					/* sample within radius */
					for ( sy = ( y - radius ); sy <= ( y + radius ); sy++ )
					{
						if ( sy < 0 || sy >= lm->sh ) {
							continue;
						}

						for ( sx = ( x - radius ); sx <= ( x + radius ); sx++ )
						{
							if ( sx < 0 || sx >= lm->sw ) {
								continue;
							}

							/* get luxel particulars */
							luxel = SUPER_LUXEL( lightmapNum, sx, sy );
							cluster = SUPER_CLUSTER( sx, sy );
							if ( *cluster < 0 ) {
								continue;
							}

							/* testing: must be brigher than ambient color */
							//%	if( luxel[ 0 ] <= ambientColor[ 0 ] || luxel[ 1 ] <= ambientColor[ 1 ] || luxel[ 2 ] <= ambientColor[ 2 ] )
							//%		continue;

							/* add its distinctiveness to our own */
							VectorAdd( radVertLuxel, luxel, radVertLuxel );
							samples += luxel[ 3 ];
						}
					}
				}

				/* any color? */
				if ( samples > 0.0f ) {
					VectorDivide( radVertLuxel, samples, radVertLuxel );
				}
				else{
					VectorCopy( ambientColor, radVertLuxel );
				}
			}

			/* store into floating point storage */
			VectorAdd( vertLuxel, radVertLuxel, vertLuxel );
			pthread_mutex_lock( &master_mutex );
			numVertsIlluminated++;
			pthread_mutex_unlock( &master_mutex );

			/* store into bytes (for vertex approximation) */
			if ( !info->si->noVertexLight ) {
				ColorToBytes( vertLuxel, verts[ i ].color[ lightmapNum ], 1.0f );
			}
		}
	}
}