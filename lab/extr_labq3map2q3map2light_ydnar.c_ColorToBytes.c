#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  float* vec3_t ;
typedef  float byte ;

/* Variables and functions */
 int /*<<< orphan*/  VectorScale (float const*,float,float*) ; 
 float lightmapCompensate ; 
 float lightmapGamma ; 
 float pow (float,float) ; 

void ColorToBytes( const float *color, byte *colorBytes, float scale ){
	int i;
	float max, gamma;
	vec3_t sample;


	/* ydnar: scaling necessary for simulating r_overbrightBits on external lightmaps */
	if ( scale <= 0.0f ) {
		scale = 1.0f;
	}

	/* make a local copy */
	VectorScale( color, scale, sample );

	/* muck with it */
	gamma = 1.0f / lightmapGamma;
	for ( i = 0; i < 3; i++ )
	{
		/* handle negative light */
		if ( sample[ i ] < 0.0f ) {
			sample[ i ] = 0.0f;
			continue;
		}

		/* gamma */
		sample[ i ] = pow( sample[ i ] / 255.0f, gamma ) * 255.0f;
	}

	/* clamp with color normalization */
	max = sample[ 0 ];
	if ( sample[ 1 ] > max ) {
		max = sample[ 1 ];
	}
	if ( sample[ 2 ] > max ) {
		max = sample[ 2 ];
	}
	if ( max > 255.0f ) {
		VectorScale( sample, ( 255.0f / max ), sample );
	}

	/* compensate for ingame overbrighting/bitshifting */
	VectorScale( sample, ( 1.0f / lightmapCompensate ), sample );

	/* store it off */
	colorBytes[ 0 ] = sample[ 0 ];
	colorBytes[ 1 ] = sample[ 1 ];
	colorBytes[ 2 ] = sample[ 2 ];
}