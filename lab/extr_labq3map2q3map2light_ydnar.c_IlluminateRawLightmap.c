#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_15__ {int testOcclusion; int numSurfaces; size_t* surfaces; int numLights; int cluster; float* origin; float* normal; float* color; float* direction; TYPE_2__* light; TYPE_2__** lights; void* twoSided; int /*<<< orphan*/  inhibitRadius; int /*<<< orphan*/  recvShadows; void* forceSunlight; } ;
typedef  TYPE_3__ trace_t ;
struct TYPE_16__ {TYPE_1__* si; } ;
typedef  TYPE_4__ surfaceInfo_t ;
struct TYPE_17__ {int numLightSurfaces; size_t firstLightSurface; float* mins; float* maxs; int sw; int sh; float* axis; float** superLuxels; scalar_t__* styles; float filterRadius; float sampleSize; scalar_t__ splotchFix; int /*<<< orphan*/  lightClusters; int /*<<< orphan*/  numLightClusters; int /*<<< orphan*/  plane; int /*<<< orphan*/  recvShadows; } ;
typedef  TYPE_5__ rawLightmap_t ;
typedef  void* qboolean ;
struct TYPE_14__ {scalar_t__ style; float filterRadius; int flags; } ;
struct TYPE_13__ {scalar_t__ twoSided; } ;

/* Variables and functions */
 int CLUSTER_FLOODED ; 
 int /*<<< orphan*/  CreateTraceLightsForBounds (float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  DEFAULT_INHIBIT_RADIUS ; 
 int /*<<< orphan*/  FreeTraceLights (TYPE_3__*) ; 
 float* LIGHT_LUXEL (int,int) ; 
 int LIGHT_NEGATIVE ; 
 int /*<<< orphan*/  LIGHT_SURFACES ; 
 scalar_t__ LS_NONE ; 
 int /*<<< orphan*/  LightContributionToSample (TYPE_3__*) ; 
 int MAX_LIGHTMAPS ; 
 int STACK_LL_SIZE ; 
 int* SUPER_CLUSTER (int,int) ; 
 float* SUPER_DELUXEL (int,int) ; 
 float* SUPER_DIRT (int,int) ; 
 float* SUPER_LUXEL (int,int,int) ; 
 int SUPER_LUXEL_SIZE ; 
 float* SUPER_NORMAL (int,int) ; 
 float* SUPER_ORIGIN (int,int) ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  SubsampleRawLuxel_r (TYPE_5__*,TYPE_3__*,float*,int,int,float,float*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  VectorAdd (float*,float*,float*) ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 scalar_t__ VectorCompare (float*,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  VectorDivide (float*,float,float*) ; 
 int /*<<< orphan*/  VectorMA (float*,float,float*,float*) ; 
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 
 int /*<<< orphan*/  VectorSet (float*,float,float,float) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 
 int abs (int) ; 
 float* ambientColor ; 
 scalar_t__ dark ; 
 scalar_t__ debugAxis ; 
 scalar_t__ debugCluster ; 
 float** debugColors ; 
 scalar_t__ debugOrigin ; 
 scalar_t__ debugSurfaces ; 
 scalar_t__ deluxemap ; 
 scalar_t__ dirtDebug ; 
 scalar_t__ dirty ; 
 scalar_t__ filter ; 
 int /*<<< orphan*/  free (float*) ; 
 int lightSamples ; 
 size_t* lightSurfaces ; 
 int /*<<< orphan*/  master_mutex ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  noTrace ; 
 scalar_t__ normalmap ; 
 int numLuxelsIlluminated ; 
 int numRawLightmaps ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_5__* rawLightmaps ; 
 void* safe_malloc (int) ; 
 float superSample ; 
 TYPE_4__* surfaceInfos ; 

void IlluminateRawLightmap( int rawLightmapNum ){
	int i, t, x, y, sx, sy, size, llSize, luxelFilterRadius, lightmapNum;
	int                 *cluster, *cluster2, mapped, lighted, totalLighted;
	rawLightmap_t       *lm;
	surfaceInfo_t       *info;
	qboolean filterColor, filterDir;
	float brightness;
	float               *origin, *normal, *dirt, *luxel, *luxel2, *deluxel, *deluxel2;
	float               *lightLuxels, *lightLuxel, samples, filterRadius, weight;
	vec3_t color, averageColor, averageDir, total, temp, temp2;
	float tests[ 4 ][ 2 ] = { { 0.0f, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } };
	trace_t trace;
	float stackLightLuxels[ STACK_LL_SIZE ];


	/* bail if this number exceeds the number of raw lightmaps */
	if ( rawLightmapNum >= numRawLightmaps ) {
		return;
	}

	/* get lightmap */
	lm = &rawLightmaps[ rawLightmapNum ];

	/* setup trace */
	trace.testOcclusion = !noTrace;
	trace.forceSunlight = qfalse;
	trace.recvShadows = lm->recvShadows;
	trace.numSurfaces = lm->numLightSurfaces;
	trace.surfaces = &lightSurfaces[ lm->firstLightSurface ];
	trace.inhibitRadius = DEFAULT_INHIBIT_RADIUS;

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

	/* create a culled light list for this raw lightmap */
	CreateTraceLightsForBounds( lm->mins, lm->maxs, lm->plane, lm->numLightClusters, lm->lightClusters, LIGHT_SURFACES, &trace );

	/* -----------------------------------------------------------------
	   fill pass
	   ----------------------------------------------------------------- */

	/* set counts */
	pthread_mutex_lock( &master_mutex );
	numLuxelsIlluminated += ( lm->sw * lm->sh );
	pthread_mutex_unlock( &master_mutex );

	/* test debugging state */
	if ( debugSurfaces || debugAxis || debugCluster || debugOrigin || dirtDebug || normalmap ) {
		/* debug fill the luxels */
		for ( y = 0; y < lm->sh; y++ )
		{
			for ( x = 0; x < lm->sw; x++ )
			{
				/* get cluster */
				cluster = SUPER_CLUSTER( x, y );

				/* only fill mapped luxels */
				if ( *cluster < 0 ) {
					continue;
				}

				/* get particulars */
				luxel = SUPER_LUXEL( 0, x, y );
				origin = SUPER_ORIGIN( x, y );
				normal = SUPER_NORMAL( x, y );

				/* color the luxel with raw lightmap num? */
				if ( debugSurfaces ) {
					VectorCopy( debugColors[ rawLightmapNum % 12 ], luxel );
				}

				/* color the luxel with lightmap axis? */
				else if ( debugAxis ) {
					luxel[ 0 ] = ( lm->axis[ 0 ] + 1.0f ) * 127.5f;
					luxel[ 1 ] = ( lm->axis[ 1 ] + 1.0f ) * 127.5f;
					luxel[ 2 ] = ( lm->axis[ 2 ] + 1.0f ) * 127.5f;
				}

				/* color the luxel with luxel cluster? */
				else if ( debugCluster ) {
					VectorCopy( debugColors[ *cluster % 12 ], luxel );
				}

				/* color the luxel with luxel origin? */
				else if ( debugOrigin ) {
					VectorSubtract( lm->maxs, lm->mins, temp );
					VectorScale( temp, ( 1.0f / 255.0f ), temp );
					VectorSubtract( origin, lm->mins, temp2 );
					luxel[ 0 ] = lm->mins[ 0 ] + ( temp[ 0 ] * temp2[ 0 ] );
					luxel[ 1 ] = lm->mins[ 1 ] + ( temp[ 1 ] * temp2[ 1 ] );
					luxel[ 2 ] = lm->mins[ 2 ] + ( temp[ 2 ] * temp2[ 2 ] );
				}

				/* color the luxel with the normal */
				else if ( normalmap ) {
					luxel[ 0 ] = ( normal[ 0 ] + 1.0f ) * 127.5f;
					luxel[ 1 ] = ( normal[ 1 ] + 1.0f ) * 127.5f;
					luxel[ 2 ] = ( normal[ 2 ] + 1.0f ) * 127.5f;
				}

				/* otherwise clear it */
				else{
					VectorClear( luxel );
				}

				/* add to counts */
				luxel[ 3 ] = 1.0f;
			}
		}
	}
	else
	{
		/* allocate temporary per-light luxel storage */
		llSize = lm->sw * lm->sh * SUPER_LUXEL_SIZE * sizeof( float );
		if ( llSize <= ( STACK_LL_SIZE * sizeof( float ) ) ) {
			lightLuxels = stackLightLuxels;
		}
		else{
			lightLuxels = safe_malloc( llSize );
		}

		/* clear luxels */
		//%	memset( lm->superLuxels[ 0 ], 0, llSize );

		/* set ambient color */
		for ( y = 0; y < lm->sh; y++ )
		{
			for ( x = 0; x < lm->sw; x++ )
			{
				/* get cluster */
				cluster = SUPER_CLUSTER( x, y );
				luxel = SUPER_LUXEL( 0, x, y );
				normal = SUPER_NORMAL( x, y );
				deluxel = SUPER_DELUXEL( x, y );

				/* blacken unmapped clusters */
				if ( *cluster < 0 ) {
					VectorClear( luxel );
				}

				/* set ambient */
				else
				{
					VectorCopy( ambientColor, luxel );
					if ( deluxemap ) {
						VectorScale( normal, 0.00390625f, deluxel );
					}
					luxel[ 3 ] = 1.0f;
				}
			}
		}

		/* clear styled lightmaps */
		size = lm->sw * lm->sh * SUPER_LUXEL_SIZE * sizeof( float );
		for ( lightmapNum = 1; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
		{
			if ( lm->superLuxels[ lightmapNum ] != NULL ) {
				memset( lm->superLuxels[ lightmapNum ], 0, size );
			}
		}

		/* debugging code */
		//%	if( trace.numLights <= 0 )
		//%		Sys_Printf( "Lightmap %9d: 0 lights, axis: %.2f, %.2f, %.2f\n", rawLightmapNum, lm->axis[ 0 ], lm->axis[ 1 ], lm->axis[ 2 ] );

		/* walk light list */
		for ( i = 0; i < trace.numLights; i++ )
		{
			/* setup trace */
			trace.light = trace.lights[ i ];

			/* style check */
			for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
			{
				if ( lm->styles[ lightmapNum ] == trace.light->style ||
					 lm->styles[ lightmapNum ] == LS_NONE ) {
					break;
				}
			}

			/* max of MAX_LIGHTMAPS (4) styles allowed to hit a surface/lightmap */
			if ( lightmapNum >= MAX_LIGHTMAPS ) {
				Sys_FPrintf( SYS_WRN, "WARNING: Hit per-surface style limit (%d)\n", MAX_LIGHTMAPS );
				continue;
			}

			/* setup */
			memset( lightLuxels, 0, llSize );
			totalLighted = 0;

			/* initial pass, one sample per luxel */
			for ( y = 0; y < lm->sh; y++ )
			{
				for ( x = 0; x < lm->sw; x++ )
				{
					/* get cluster */
					cluster = SUPER_CLUSTER( x, y );
					if ( *cluster < 0 ) {
						continue;
					}

					/* get particulars */
					lightLuxel = LIGHT_LUXEL( x, y );
					deluxel = SUPER_DELUXEL( x, y );
					origin = SUPER_ORIGIN( x, y );
					normal = SUPER_NORMAL( x, y );

					/* set contribution count */
					lightLuxel[ 3 ] = 1.0f;

					/* setup trace */
					trace.cluster = *cluster;
					VectorCopy( origin, trace.origin );
					VectorCopy( normal, trace.normal );

					/* get light for this sample */
					LightContributionToSample( &trace );
					VectorCopy( trace.color, lightLuxel );

					/* add to count */
					if ( trace.color[ 0 ] || trace.color[ 1 ] || trace.color[ 2 ] ) {
						totalLighted++;
					}

					/* add to light direction map (fixme: use luxel normal as starting point for deluxel?) */
					if ( deluxemap ) {
						/* color to grayscale (photoshop rgb weighting) */
						brightness = trace.color[ 0 ] * 0.3f + trace.color[ 1 ] * 0.59f + trace.color[ 2 ] * 0.11f;
						brightness *= ( 1.0 / 255.0 );
						VectorScale( trace.direction, brightness, trace.direction );
						VectorAdd( deluxel, trace.direction, deluxel );
					}
				}
			}

			/* don't even bother with everything else if nothing was lit */
			if ( totalLighted == 0 ) {
				continue;
			}

			/* determine filter radius */
			filterRadius = lm->filterRadius > trace.light->filterRadius
						   ? lm->filterRadius
						   : trace.light->filterRadius;
			if ( filterRadius < 0.0f ) {
				filterRadius = 0.0f;
			}

			/* set luxel filter radius */
			luxelFilterRadius = lm->sampleSize != 0 ? superSample * filterRadius / lm->sampleSize : 0;
			if ( luxelFilterRadius == 0 && ( filterRadius > 0.0f || filter ) ) {
				luxelFilterRadius = 1;
			}

			/* secondary pass, adaptive supersampling (fixme: use a contrast function to determine if subsampling is necessary) */
			/* 2003-09-27: changed it so filtering disamples supersampling, as it would waste time */
			if ( lightSamples > 1 && luxelFilterRadius == 0 ) {
				/* walk luxels */
				for ( y = 0; y < ( lm->sh - 1 ); y++ )
				{
					for ( x = 0; x < ( lm->sw - 1 ); x++ )
					{
						/* setup */
						mapped = 0;
						lighted = 0;
						VectorClear( total );

						/* test 2x2 stamp */
						for ( t = 0; t < 4; t++ )
						{
							/* set sample coords */
							sx = x + tests[ t ][ 0 ];
							sy = y + tests[ t ][ 1 ];

							/* get cluster */
							cluster = SUPER_CLUSTER( sx, sy );
							if ( *cluster < 0 ) {
								continue;
							}
							mapped++;

							/* get luxel */
							lightLuxel = LIGHT_LUXEL( sx, sy );
							VectorAdd( total, lightLuxel, total );
							if ( ( lightLuxel[ 0 ] + lightLuxel[ 1 ] + lightLuxel[ 2 ] ) > 0.0f ) {
								lighted++;
							}
						}

						/* if total color is under a certain amount, then don't bother subsampling */
						if ( total[ 0 ] <= 4.0f && total[ 1 ] <= 4.0f && total[ 2 ] <= 4.0f ) {
							continue;
						}

						/* if all 4 pixels are either in shadow or light, then don't subsample */
						if ( lighted != 0 && lighted != mapped ) {
							for ( t = 0; t < 4; t++ )
							{
								/* set sample coords */
								sx = x + tests[ t ][ 0 ];
								sy = y + tests[ t ][ 1 ];

								/* get luxel */
								cluster = SUPER_CLUSTER( sx, sy );
								if ( *cluster < 0 ) {
									continue;
								}
								lightLuxel = LIGHT_LUXEL( sx, sy );
								origin = SUPER_ORIGIN( sx, sy );

								/* only subsample shadowed luxels */
								//%	if( (lightLuxel[ 0 ] + lightLuxel[ 1 ] + lightLuxel[ 2 ]) <= 0.0f )
								//%		continue;

								/* subsample it */
								SubsampleRawLuxel_r( lm, &trace, origin, sx, sy, 0.25f, lightLuxel );

								/* debug code to colorize subsampled areas to yellow */
								//%	luxel = SUPER_LUXEL( lightmapNum, sx, sy );
								//%	VectorSet( luxel, 255, 204, 0 );
							}
						}
					}
				}
			}

			/* tertiary pass, apply dirt map (ambient occlusion) */
			if ( 0 && dirty ) {
				/* walk luxels */
				for ( y = 0; y < lm->sh; y++ )
				{
					for ( x = 0; x < lm->sw; x++ )
					{
						/* get cluster  */
						cluster = SUPER_CLUSTER( x, y );
						if ( *cluster < 0 ) {
							continue;
						}

						/* get particulars */
						lightLuxel = LIGHT_LUXEL( x, y );
						dirt = SUPER_DIRT( x, y );

						/* scale light value */
						VectorScale( lightLuxel, *dirt, lightLuxel );
					}
				}
			}

			/* allocate sampling lightmap storage */
			if ( lm->superLuxels[ lightmapNum ] == NULL ) {
				/* allocate sampling lightmap storage */
				size = lm->sw * lm->sh * SUPER_LUXEL_SIZE * sizeof( float );
				lm->superLuxels[ lightmapNum ] = safe_malloc( size );
				memset( lm->superLuxels[ lightmapNum ], 0, size );
			}

			/* set style */
			if ( lightmapNum > 0 ) {
				lm->styles[ lightmapNum ] = trace.light->style;
				//%	Sys_Printf( "Surface %6d has lightstyle %d\n", rawLightmapNum, trace.light->style );
			}

			/* copy to permanent luxels */
			for ( y = 0; y < lm->sh; y++ )
			{
				for ( x = 0; x < lm->sw; x++ )
				{
					/* get cluster and origin */
					cluster = SUPER_CLUSTER( x, y );
					if ( *cluster < 0 ) {
						continue;
					}
					origin = SUPER_ORIGIN( x, y );

					/* filter? */
					if ( luxelFilterRadius ) {
						/* setup */
						VectorClear( averageColor );
						samples = 0.0f;

						/* cheaper distance-based filtering */
						for ( sy = ( y - luxelFilterRadius ); sy <= ( y + luxelFilterRadius ); sy++ )
						{
							if ( sy < 0 || sy >= lm->sh ) {
								continue;
							}

							for ( sx = ( x - luxelFilterRadius ); sx <= ( x + luxelFilterRadius ); sx++ )
							{
								if ( sx < 0 || sx >= lm->sw ) {
									continue;
								}

								/* get particulars */
								cluster = SUPER_CLUSTER( sx, sy );
								if ( *cluster < 0 ) {
									continue;
								}
								lightLuxel = LIGHT_LUXEL( sx, sy );

								/* create weight */
								weight = ( abs( sx - x ) == luxelFilterRadius ? 0.5f : 1.0f );
								weight *= ( abs( sy - y ) == luxelFilterRadius ? 0.5f : 1.0f );

								/* scale luxel by filter weight */
								VectorScale( lightLuxel, weight, color );
								VectorAdd( averageColor, color, averageColor );
								samples += weight;
							}
						}

						/* any samples? */
						if ( samples <= 0.0f ) {
							continue;
						}

						/* scale into luxel */
						luxel = SUPER_LUXEL( lightmapNum, x, y );
						luxel[ 3 ] = 1.0f;

						/* handle negative light */
						if ( trace.light->flags & LIGHT_NEGATIVE ) {
							luxel[ 0 ] -= averageColor[ 0 ] / samples;
							luxel[ 1 ] -= averageColor[ 1 ] / samples;
							luxel[ 2 ] -= averageColor[ 2 ] / samples;
						}

						/* handle normal light */
						else
						{
							luxel[ 0 ] += averageColor[ 0 ] / samples;
							luxel[ 1 ] += averageColor[ 1 ] / samples;
							luxel[ 2 ] += averageColor[ 2 ] / samples;
						}
					}

					/* single sample */
					else
					{
						/* get particulars */
						lightLuxel = LIGHT_LUXEL( x, y );
						luxel = SUPER_LUXEL( lightmapNum, x, y );

						/* handle negative light */
						if ( trace.light->flags & LIGHT_NEGATIVE ) {
							VectorScale( averageColor, -1.0f, averageColor );
						}

						/* add color */
						luxel[ 3 ] = 1.0f;

						/* handle negative light */
						if ( trace.light->flags & LIGHT_NEGATIVE ) {
							VectorSubtract( luxel, lightLuxel, luxel );
						}

						/* handle normal light */
						else{
							VectorAdd( luxel, lightLuxel, luxel );
						}
					}
				}
			}
		}

		/* free temporary luxels */
		if ( lightLuxels != stackLightLuxels ) {
			free( lightLuxels );
		}
	}

	/* free light list */
	FreeTraceLights( &trace );

	/*	-----------------------------------------------------------------
	    dirt pass
	    ----------------------------------------------------------------- */

	if ( dirty ) {
		/* walk lightmaps */
		for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
		{
			/* early out */
			if ( lm->superLuxels[ lightmapNum ] == NULL ) {
				continue;
			}

			/* apply dirt to each luxel */
			for ( y = 0; y < lm->sh; y++ )
			{
				for ( x = 0; x < lm->sw; x++ )
				{
					/* get cluster */
					cluster = SUPER_CLUSTER( x, y );
					//%	if( *cluster < 0 )
					//%		continue;

					/* get particulars */
					luxel = SUPER_LUXEL( lightmapNum, x, y );
					dirt = SUPER_DIRT( x, y );

					/* apply dirt */
					VectorScale( luxel, *dirt, luxel );

					/* debugging */
					if ( dirtDebug ) {
						VectorSet( luxel, *dirt * 255.0f, *dirt * 255.0f, *dirt * 255.0f );
					}
				}
			}
		}
	}

	/* -----------------------------------------------------------------
	   filter pass
	   ----------------------------------------------------------------- */

	/* walk lightmaps */
	for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
	{
		/* early out */
		if ( lm->superLuxels[ lightmapNum ] == NULL ) {
			continue;
		}

		/* average occluded luxels from neighbors */
		for ( y = 0; y < lm->sh; y++ )
		{
			for ( x = 0; x < lm->sw; x++ )
			{
				/* get particulars */
				cluster = SUPER_CLUSTER( x, y );
				luxel = SUPER_LUXEL( lightmapNum, x, y );
				deluxel = SUPER_DELUXEL( x, y );
				normal = SUPER_NORMAL( x, y );

				/* determine if filtering is necessary */
				filterColor = qfalse;
				filterDir = qfalse;
				if ( *cluster < 0 ||
					 ( lm->splotchFix && ( luxel[ 0 ] <= ambientColor[ 0 ] || luxel[ 1 ] <= ambientColor[ 1 ] || luxel[ 2 ] <= ambientColor[ 2 ] ) ) ) {
					filterColor = qtrue;
				}
				if ( deluxemap && lightmapNum == 0 && ( *cluster < 0 || filter ) ) {
					filterDir = qtrue;
				}

				if ( !filterColor && !filterDir ) {
					continue;
				}

				/* choose seed amount */
				VectorClear( averageColor );
				VectorClear( averageDir );
				samples = 0.0f;

				/* walk 3x3 matrix */
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

						/* get neighbor's particulars */
						cluster2 = SUPER_CLUSTER( sx, sy );
						luxel2 = SUPER_LUXEL( lightmapNum, sx, sy );
						deluxel2 = SUPER_DELUXEL( sx, sy );

						/* ignore unmapped/unlit luxels */
						if ( *cluster2 < 0 || luxel2[ 3 ] == 0.0f ||
							 ( lm->splotchFix && VectorCompare( luxel2, ambientColor ) ) ) {
							continue;
						}

						/* add its distinctiveness to our own */
						VectorAdd( averageColor, luxel2, averageColor );
						samples += luxel2[ 3 ];
						if ( filterDir ) {
							VectorAdd( averageDir, deluxel2, averageDir );
						}
					}
				}

				/* fall through */
				if ( samples <= 0.0f ) {
					continue;
				}

				/* dark lightmap seams */
				if ( dark ) {
					if ( lightmapNum == 0 ) {
						VectorMA( averageColor, 2.0f, ambientColor, averageColor );
					}
					samples += 2.0f;
				}

				/* average it */
				if ( filterColor ) {
					VectorDivide( averageColor, samples, luxel );
					luxel[ 3 ] = 1.0f;
				}
				if ( filterDir ) {
					VectorDivide( averageDir, samples, deluxel );
				}

				/* set cluster to -3 */
				if ( *cluster < 0 ) {
					*cluster = CLUSTER_FLOODED;
				}
			}
		}
	}
}