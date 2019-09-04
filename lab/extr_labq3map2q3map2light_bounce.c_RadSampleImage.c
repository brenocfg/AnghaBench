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
typedef  int /*<<< orphan*/  qboolean ;
typedef  float byte ;

/* Variables and functions */
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean RadSampleImage( byte *pixels, int width, int height, float st[ 2 ], float color[ 4 ] ){
	float sto[ 2 ];
	int x, y;


	/* clear color first */
	color[ 0 ] = color[ 1 ] = color[ 2 ] = color[ 3 ] = 255;

	/* dummy check */
	if ( pixels == NULL || width < 1 || height < 1 ) {
		return qfalse;
	}

	/* bias st */
	sto[ 0 ] = st[ 0 ];
	while ( sto[ 0 ] < 0.0f )
		sto[ 0 ] += 1.0f;
	sto[ 1 ] = st[ 1 ];
	while ( sto[ 1 ] < 0.0f )
		sto[ 1 ] += 1.0f;

	/* get offsets */
	x = ( (float) width * sto[ 0 ] ) + 0.5f;
	x %= width;
	y = ( (float) height * sto[ 1 ] )  + 0.5f;
	y %= height;

	/* get pixel */
	pixels += ( y * width * 4 ) + ( x * 4 );
	VectorCopy( pixels, color );
	color[ 3 ] = pixels[ 3 ];
	return qtrue;
}