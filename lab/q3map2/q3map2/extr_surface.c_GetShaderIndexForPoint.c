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
typedef  float* vec3_t ;
struct TYPE_3__ {int w; int h; int /*<<< orphan*/ * pixels; } ;
typedef  TYPE_1__ indexMap_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 float floor (float) ; 

byte GetShaderIndexForPoint( indexMap_t *im, vec3_t eMins, vec3_t eMaxs, vec3_t point ){
	int i, x, y;
	float s, t;
	vec3_t mins, maxs, size;


	/* early out if no indexmap */
	if ( im == NULL ) {
		return 0;
	}

	/* this code is really broken */
	#if 0
	/* legacy precision fudges for terrain */
	for ( i = 0; i < 3; i++ )
	{
		mins[ i ] = floor( eMins[ i ] + 0.1 );
		maxs[ i ] = floor( eMaxs[ i ] + 0.1 );
		size[ i ] = maxs[ i ] - mins[ i ];
	}

	/* find st (fixme: support more than just z-axis projection) */
	s = floor( point[ 0 ] + 0.1f - mins[ 0 ] ) / size[ 0 ];
	t = floor( maxs[ 1 ] - point[ 1 ] + 0.1f ) / size[ 1 ];
	if ( s < 0.0f ) {
		s = 0.0f;
	}
	else if ( s > 1.0f ) {
		s = 1.0f;
	}
	if ( t < 0.0f ) {
		t = 0.0f;
	}
	else if ( t > 1.0f ) {
		t = 1.0f;
	}

	/* make xy */
	x = ( im->w - 1 ) * s;
	y = ( im->h - 1 ) * t;
	#else
	/* get size */
	for ( i = 0; i < 3; i++ )
	{
		mins[ i ] = eMins[ i ];
		maxs[ i ] = eMaxs[ i ];
		size[ i ] = maxs[ i ] - mins[ i ];
	}

	/* calc st */
	s = ( point[ 0 ] - mins[ 0 ] ) / size[ 0 ];
	t = ( maxs[ 1 ] - point[ 1 ] ) / size[ 1 ];

	/* calc xy */
	x = s * im->w;
	y = t * im->h;
	if ( x < 0 ) {
		x = 0;
	}
	else if ( x > ( im->w - 1 ) ) {
		x = ( im->w - 1 );
	}
	if ( y < 0 ) {
		y = 0;
	}
	else if ( y > ( im->h - 1 ) ) {
		y = ( im->h - 1 );
	}
	#endif

	/* return index */
	return im->pixels[ y * im->w + x ];
}