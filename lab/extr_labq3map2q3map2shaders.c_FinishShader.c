#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec4_t ;
struct TYPE_5__ {float shaderWidth; float shaderHeight; scalar_t__ tcGen; float* averageColor; float* stFlat; void* finished; TYPE_1__* shaderImage; int /*<<< orphan*/ * vecs; scalar_t__ legacyTerrain; } ;
typedef  TYPE_2__ shaderInfo_t ;
typedef  float byte ;
struct TYPE_4__ {float width; float height; float* pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 
 scalar_t__ qfalse ; 
 void* qtrue ; 

void FinishShader( shaderInfo_t *si ){
	int x, y;
	float dist, bestDist;
	vec4_t color, bestColor, delta, average;
	int image_width, image_height;
	byte *current_pixel;

	/* don't double-dip */
	if ( si->finished ) {
		return;
	}

	/* if they're explicitly set, copy from image size */
	if ( si->shaderWidth == 0 && si->shaderHeight == 0 ) {
		si->shaderWidth = si->shaderImage->width;
		si->shaderHeight = si->shaderImage->height;
	}

	/* legacy terrain has explicit image-sized texture projection */
	if ( si->legacyTerrain && si->tcGen == qfalse ) {
		/* set xy texture projection */
		si->tcGen = qtrue;
		VectorSet( si->vecs[ 0 ], ( 1.0f / ( si->shaderWidth * 0.5f ) ), 0, 0 );
		VectorSet( si->vecs[ 1 ], 0, ( 1.0f / ( si->shaderHeight * 0.5f ) ), 0 );
	}

	current_pixel = si->shaderImage->pixels;
	image_width = si->shaderImage->width;
	image_height = si->shaderImage->height;

	/* find pixel coordinates best matching the average color of the image */
	bestDist = 99999999;
	VectorCopy( si->averageColor, average );
	average[ 3 ] = si->averageColor[ 3 ];

	for ( y = 0; y < image_height; y++ )
	{
		for ( x = 0; x < image_width; x++ )
		{
			/* sample the shader image */
			VectorCopy( current_pixel, color );
			color[ 3 ] = current_pixel[ 3 ];
			current_pixel += 4;

			/* determine error squared */
			VectorSubtract( color, average, delta );
			delta[ 3 ] = color[ 3 ] - average[ 3 ];
			dist = delta[ 0 ] * delta[ 0 ] + delta[ 1 ] * delta[ 1 ] + delta[ 2 ] * delta[ 2 ] + delta[ 3 ] * delta[ 3 ];
			if ( dist < bestDist ) {
				VectorCopy( color, bestColor );
				bestColor[ 3 ] = color[ 3 ];
				si->stFlat[ 0 ] = (float) x / image_width;
				si->stFlat[ 1 ] = (float) y / image_height;
			}
		}
	}

	/* set to finished */
	si->finished = qtrue;
}