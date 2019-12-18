#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec4_t ;
typedef  double* vec3_t ;
struct TYPE_12__ {int /*<<< orphan*/  averageColor; TYPE_1__* lightImage; } ;
typedef  TYPE_2__ shaderInfo_t ;
struct TYPE_13__ {int w; int h; int /*<<< orphan*/ ** radLuxels; } ;
typedef  TYPE_3__ rawLightmap_t ;
struct TYPE_14__ {int numVerts; TYPE_5__* verts; } ;
typedef  TYPE_4__ radWinding_t ;
struct TYPE_15__ {float* st; float** color; double** lightmap; } ;
typedef  TYPE_5__ radVert_t ;
struct TYPE_16__ {int* vertexStyles; int* lightmapStyles; } ;
typedef  TYPE_6__ bspDrawSurface_t ;
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (double*,double*,double*) ; 
 int /*<<< orphan*/  ClearBounds (double*,double*) ; 
 int MAX_SAMPLES ; 
 float* RAD_LUXEL (int,int,int) ; 
 int /*<<< orphan*/  RadSampleImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int*) ; 
 int SAMPLE_GRANULARITY ; 
 int /*<<< orphan*/  VectorAdd (double*,double*,double*) ; 
 int /*<<< orphan*/  VectorClear (double*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  VectorScale (double*,double,double*) ; 
 scalar_t__ bouncing ; 
 scalar_t__ qfalse ; 
 scalar_t__ superSample ; 

__attribute__((used)) static void RadSample( int lightmapNum, bspDrawSurface_t *ds, rawLightmap_t *lm, shaderInfo_t *si, radWinding_t *rw, vec3_t average, vec3_t gradient, int *style ){
	int i, j, k, l, v, x, y, samples;
	vec3_t color, mins, maxs;
	vec4_t textureColor;
	float alpha, alphaI, bf;
	vec3_t blend;
	float st[ 2 ], lightmap[ 2 ], *radLuxel;
	radVert_t   *rv[ 3 ];


	/* initial setup */
	ClearBounds( mins, maxs );
	VectorClear( average );
	VectorClear( gradient );
	alpha = 0;

	/* dummy check */
	if ( rw == NULL || rw->numVerts < 3 ) {
		return;
	}

	/* start sampling */
	samples = 0;

	/* sample vertex colors if no lightmap or this is the initial pass */
	if ( lm == NULL || lm->radLuxels[ lightmapNum ] == NULL || bouncing == qfalse ) {
		for ( samples = 0; samples < rw->numVerts; samples++ )
		{
			/* multiply by texture color */
			if ( !RadSampleImage( si->lightImage->pixels, si->lightImage->width, si->lightImage->height, rw->verts[ samples ].st, textureColor ) ) {
				VectorCopy( si->averageColor, textureColor );
				textureColor[ 3 ] = 255.0f;
			}
			for ( i = 0; i < 3; i++ )
				color[ i ] = ( textureColor[ i ] / 255 ) * ( rw->verts[ samples ].color[ lightmapNum ][ i ] / 255.0f );

			AddPointToBounds( color, mins, maxs );
			VectorAdd( average, color, average );

			/* get alpha */
			alpha += ( textureColor[ 3 ] / 255.0f ) * ( rw->verts[ samples ].color[ lightmapNum ][ 3 ] / 255.0f );
		}

		/* set style */
		*style = ds->vertexStyles[ lightmapNum ];
	}

	/* sample lightmap */
	else
	{
		/* fracture the winding into a fan (including degenerate tris) */
		for ( v = 1; v < ( rw->numVerts - 1 ) && samples < MAX_SAMPLES; v++ )
		{
			/* get a triangle */
			rv[ 0 ] = &rw->verts[ 0 ];
			rv[ 1 ] = &rw->verts[ v ];
			rv[ 2 ] = &rw->verts[ v + 1 ];

			/* this code is embarassing (really should just rasterize the triangle) */
			for ( i = 1; i < SAMPLE_GRANULARITY && samples < MAX_SAMPLES; i++ )
			{
				for ( j = 1; j < SAMPLE_GRANULARITY && samples < MAX_SAMPLES; j++ )
				{
					for ( k = 1; k < SAMPLE_GRANULARITY && samples < MAX_SAMPLES; k++ )
					{
						/* create a blend vector (barycentric coordinates) */
						blend[ 0 ] = i;
						blend[ 1 ] = j;
						blend[ 2 ] = k;
						bf = ( 1.0 / ( blend[ 0 ] + blend[ 1 ] + blend[ 2 ] ) );
						VectorScale( blend, bf, blend );

						/* create a blended sample */
						st[ 0 ] = st[ 1 ] = 0.0f;
						lightmap[ 0 ] = lightmap[ 1 ] = 0.0f;
						alphaI = 0.0f;
						for ( l = 0; l < 3; l++ )
						{
							st[ 0 ] += ( rv[ l ]->st[ 0 ] * blend[ l ] );
							st[ 1 ] += ( rv[ l ]->st[ 1 ] * blend[ l ] );
							lightmap[ 0 ] += ( rv[ l ]->lightmap[ lightmapNum ][ 0 ] * blend[ l ] );
							lightmap[ 1 ] += ( rv[ l ]->lightmap[ lightmapNum ][ 1 ] * blend[ l ] );
							alphaI += ( rv[ l ]->color[ lightmapNum ][ 3 ] * blend[ l ] );
						}

						/* get lightmap xy coords */
						x = lightmap[ 0 ] / (float) superSample;
						y = lightmap[ 1 ] / (float) superSample;
						if ( x < 0 ) {
							x = 0;
						}
						else if ( x >= lm->w ) {
							x = lm->w - 1;
						}
						if ( y < 0 ) {
							y = 0;
						}
						else if ( y >= lm->h ) {
							y = lm->h - 1;
						}

						/* get radiosity luxel */
						radLuxel = RAD_LUXEL( lightmapNum, x, y );

						/* ignore unlit/unused luxels */
						if ( radLuxel[ 0 ] < 0.0f ) {
							continue;
						}

						/* inc samples */
						samples++;

						/* multiply by texture color */
						if ( !RadSampleImage( si->lightImage->pixels, si->lightImage->width, si->lightImage->height, st, textureColor ) ) {
							VectorCopy( si->averageColor, textureColor );
							textureColor[ 3 ] = 255;
						}
						for ( i = 0; i < 3; i++ )
							color[ i ] = ( textureColor[ i ] / 255 ) * ( radLuxel[ i ] / 255 );

						AddPointToBounds( color, mins, maxs );
						VectorAdd( average, color, average );

						/* get alpha */
						alpha += ( textureColor[ 3 ] / 255 ) * ( alphaI / 255 );
					}
				}
			}
		}

		/* set style */
		*style = ds->lightmapStyles[ lightmapNum ];
	}

	/* any samples? */
	if ( samples <= 0 ) {
		return;
	}

	/* average the color */
	VectorScale( average, ( 1.0 / samples ), average );

	/* create the color gradient */
	//%	VectorSubtract( maxs, mins, delta );

	/* new: color gradient will always be 0-1.0, expressed as the range of light relative to overall light */
	//%	gradient[ 0 ] = maxs[ 0 ] > 0.0f ? (maxs[ 0 ] - mins[ 0 ]) / maxs[ 0 ] : 0.0f;
	//%	gradient[ 1 ] = maxs[ 1 ] > 0.0f ? (maxs[ 1 ] - mins[ 1 ]) / maxs[ 1 ] : 0.0f;
	//%	gradient[ 2 ] = maxs[ 2 ] > 0.0f ? (maxs[ 2 ] - mins[ 2 ]) / maxs[ 2 ] : 0.0f;

	/* newer: another contrast function */
	for ( i = 0; i < 3; i++ )
		gradient[ i ] = ( maxs[ i ] - mins[ i ] ) * maxs[ i ];
}