#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float* mins; float* maxs; int sh; int sw; float actualSampleSize; } ;
typedef  TYPE_1__ rawLightmap_t ;

/* Variables and functions */
 int CLUSTER_UNMAPPED ; 
 float DotProduct (float*,float*) ; 
 int I_FloatTime () ; 
 int MAX_STITCH_CANDIDATES ; 
 int MAX_STITCH_LUXELS ; 
 int* SUPER_CLUSTER (int,int) ; 
 float* SUPER_LUXEL (int /*<<< orphan*/ ,int,int) ; 
 float* SUPER_NORMAL (int,int) ; 
 float* SUPER_ORIGIN (int,int) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  Sys_Printf (char*,...) ; 
 int /*<<< orphan*/  VectorAdd (float*,float*,float*) ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 
 int abs (int) ; 
 float fabs (float) ; 
 int numRawLightmaps ; 
 TYPE_1__* rawLightmaps ; 

void StitchSurfaceLightmaps( void ){
	int i, j, x, y, x2, y2, *cluster, *cluster2,
		numStitched, numCandidates, numLuxels, f, fOld, start;
	rawLightmap_t   *lm, *a, *b, *c[ MAX_STITCH_CANDIDATES ];
	float           *luxel, *luxel2, *origin, *origin2, *normal, *normal2,
					 sampleSize, average[ 3 ], totalColor, ootc, *luxels[ MAX_STITCH_LUXELS ];


	/* disabled for now */
	return;

	/* note it */
	Sys_Printf( "--- StitchSurfaceLightmaps ---\n" );

	/* init pacifier */
	fOld = -1;
	start = I_FloatTime();

	/* walk the list of raw lightmaps */
	numStitched = 0;
	for ( i = 0; i < numRawLightmaps; i++ )
	{
		/* print pacifier */
		f = 10 * i / numRawLightmaps;
		if ( f != fOld ) {
			fOld = f;
			Sys_Printf( "%i...", f );
		}

		/* get lightmap a */
		a = &rawLightmaps[ i ];

		/* walk rest of lightmaps */
		numCandidates = 0;
		for ( j = i + 1; j < numRawLightmaps && numCandidates < MAX_STITCH_CANDIDATES; j++ )
		{
			/* get lightmap b */
			b = &rawLightmaps[ j ];

			/* test bounding box */
			if ( a->mins[ 0 ] > b->maxs[ 0 ] || a->maxs[ 0 ] < b->mins[ 0 ] ||
				 a->mins[ 1 ] > b->maxs[ 1 ] || a->maxs[ 1 ] < b->mins[ 1 ] ||
				 a->mins[ 2 ] > b->maxs[ 2 ] || a->maxs[ 2 ] < b->mins[ 2 ] ) {
				continue;
			}

			/* add candidate */
			c[ numCandidates++ ] = b;
		}

		/* walk luxels */
		for ( y = 0; y < a->sh; y++ )
		{
			for ( x = 0; x < a->sw; x++ )
			{
				/* ignore unmapped/unlit luxels */
				lm = a;
				cluster = SUPER_CLUSTER( x, y );
				if ( *cluster == CLUSTER_UNMAPPED ) {
					continue;
				}
				luxel = SUPER_LUXEL( 0, x, y );
				if ( luxel[ 3 ] <= 0.0f ) {
					continue;
				}

				/* get particulars */
				origin = SUPER_ORIGIN( x, y );
				normal = SUPER_NORMAL( x, y );

				/* walk candidate list */
				for ( j = 0; j < numCandidates; j++ )
				{
					/* get candidate */
					b = c[ j ];
					lm = b;

					/* set samplesize to the smaller of the pair */
					sampleSize = 0.5f * ( a->actualSampleSize < b->actualSampleSize ? a->actualSampleSize : b->actualSampleSize );

					/* test bounding box */
					if ( origin[ 0 ] < ( b->mins[ 0 ] - sampleSize ) || ( origin[ 0 ] > b->maxs[ 0 ] + sampleSize ) ||
						 origin[ 1 ] < ( b->mins[ 1 ] - sampleSize ) || ( origin[ 1 ] > b->maxs[ 1 ] + sampleSize ) ||
						 origin[ 2 ] < ( b->mins[ 2 ] - sampleSize ) || ( origin[ 2 ] > b->maxs[ 2 ] + sampleSize ) ) {
						continue;
					}

					/* walk candidate luxels */
					VectorClear( average );
					numLuxels = 0;
					totalColor = 0.0f;
					for ( y2 = 0; y2 < b->sh && numLuxels < MAX_STITCH_LUXELS; y2++ )
					{
						for ( x2 = 0; x2 < b->sw && numLuxels < MAX_STITCH_LUXELS; x2++ )
						{
							/* ignore same luxels */
							if ( a == b && abs( x - x2 ) <= 1 && abs( y - y2 ) <= 1 ) {
								continue;
							}

							/* ignore unmapped/unlit luxels */
							cluster2 = SUPER_CLUSTER( x2, y2 );
							if ( *cluster2 == CLUSTER_UNMAPPED ) {
								continue;
							}
							luxel2 = SUPER_LUXEL( 0, x2, y2 );
							if ( luxel2[ 3 ] <= 0.0f ) {
								continue;
							}

							/* get particulars */
							origin2 = SUPER_ORIGIN( x2, y2 );
							normal2 = SUPER_NORMAL( x2, y2 );

							/* test normal */
							if ( DotProduct( normal, normal2 ) < 0.5f ) {
								continue;
							}

							/* test bounds */
							if ( fabs( origin[ 0 ] - origin2[ 0 ] ) > sampleSize ||
								 fabs( origin[ 1 ] - origin2[ 1 ] ) > sampleSize ||
								 fabs( origin[ 2 ] - origin2[ 2 ] ) > sampleSize ) {
								continue;
							}

							/* add luxel */
							//%	VectorSet( luxel2, 255, 0, 255 );
							luxels[ numLuxels++ ] = luxel2;
							VectorAdd( average, luxel2, average );
							totalColor += luxel2[ 3 ];
						}
					}

					/* early out */
					if ( numLuxels == 0 ) {
						continue;
					}

					/* scale average */
					ootc = 1.0f / totalColor;
					VectorScale( average, ootc, luxel );
					luxel[ 3 ] = 1.0f;
					numStitched++;
				}
			}
		}
	}

	/* emit statistics */
	Sys_Printf( " (%i)\n", (int) ( I_FloatTime() - start ) );
	Sys_FPrintf( SYS_VRB, "%9d luxels stitched\n", numStitched );
}