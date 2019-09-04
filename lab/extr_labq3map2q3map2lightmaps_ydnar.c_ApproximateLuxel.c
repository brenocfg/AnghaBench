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
typedef  scalar_t__* vec3_t ;
struct TYPE_5__ {int w; int h; scalar_t__* styles; } ;
typedef  TYPE_1__ rawLightmap_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int byte ;
struct TYPE_6__ {int** lightmap; float** color; } ;
typedef  TYPE_2__ bspDrawVert_t ;

/* Variables and functions */
 float* BSP_LUXEL (int,int,int) ; 
 int /*<<< orphan*/  ColorToBytes (scalar_t__*,int*,float) ; 
 scalar_t__ LS_NONE ; 
 int MAX_LIGHTMAPS ; 
 int /*<<< orphan*/  VectorCopy (float*,scalar_t__*) ; 
 int approximateTolerance ; 
 scalar_t__* minLight ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int superSample ; 

__attribute__((used)) static qboolean ApproximateLuxel( rawLightmap_t *lm, bspDrawVert_t *dv ){
	int i, x, y, d, lightmapNum;
	float   *luxel;
	vec3_t color, vertexColor;
	byte cb[ 4 ], vcb[ 4 ];


	/* find luxel xy coords */
	x = dv->lightmap[ 0 ][ 0 ] / superSample;
	y = dv->lightmap[ 0 ][ 1 ] / superSample;
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

	/* walk list */
	for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
	{
		/* early out */
		if ( lm->styles[ lightmapNum ] == LS_NONE ) {
			continue;
		}

		/* get luxel */
		luxel = BSP_LUXEL( lightmapNum, x, y );

		/* ignore occluded luxels */
		if ( luxel[ 0 ] < 0.0f || luxel[ 1 ] < 0.0f || luxel[ 2 ] < 0.0f ) {
			return qtrue;
		}

		/* copy, set min color and compare */
		VectorCopy( luxel, color );
		VectorCopy( dv->color[ 0 ], vertexColor );

		/* styles are not affected by minlight */
		if ( lightmapNum == 0 ) {
			for ( i = 0; i < 3; i++ )
			{
				/* set min color */
				if ( color[ i ] < minLight[ i ] ) {
					color[ i ] = minLight[ i ];
				}
				if ( vertexColor[ i ] < minLight[ i ] ) { /* note NOT minVertexLight */
					vertexColor[ i ] = minLight[ i ];
				}
			}
		}

		/* set to bytes */
		ColorToBytes( color, cb, 1.0f );
		ColorToBytes( vertexColor, vcb, 1.0f );

		/* compare */
		for ( i = 0; i < 3; i++ )
		{
			d = cb[ i ] - vcb[ i ];
			if ( d < 0 ) {
				d *= -1;
			}
			if ( d > approximateTolerance ) {
				return qfalse;
			}
		}
	}

	/* close enough for the girls i date */
	return qtrue;
}