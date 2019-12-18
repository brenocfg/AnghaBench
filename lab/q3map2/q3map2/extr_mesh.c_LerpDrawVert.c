#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double* xyz; double* st; float** lightmap; int** color; float* normal; } ;
typedef  TYPE_1__ bspDrawVert_t ;

/* Variables and functions */
 int MAX_LIGHTMAPS ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 scalar_t__ VectorNormalize (float*,float*) ; 

void LerpDrawVert( bspDrawVert_t *a, bspDrawVert_t *b, bspDrawVert_t *out ){
	int k;


	out->xyz[ 0 ] = 0.5 * ( a->xyz[ 0 ] + b->xyz[ 0 ] );
	out->xyz[ 1 ] = 0.5 * ( a->xyz[ 1 ] + b->xyz[ 1 ] );
	out->xyz[ 2 ] = 0.5 * ( a->xyz[ 2 ] + b->xyz[ 2 ] );

	out->st[ 0 ] = 0.5 * ( a->st[ 0 ] + b->st[ 0 ] );
	out->st[ 1 ] = 0.5 * ( a->st[ 1 ] + b->st[ 1 ] );

	for ( k = 0; k < MAX_LIGHTMAPS; k++ )
	{
		out->lightmap[ k ][ 0 ] = 0.5f * ( a->lightmap[ k ][ 0 ] + b->lightmap[ k ][ 0 ] );
		out->lightmap[ k ][ 1 ] = 0.5f * ( a->lightmap[ k ][ 1 ] + b->lightmap[ k ][ 1 ] );
		out->color[ k ][ 0 ] = ( a->color[ k ][ 0 ] + b->color[ k ][ 0 ] ) >> 1;
		out->color[ k ][ 1 ] = ( a->color[ k ][ 1 ] + b->color[ k ][ 1 ] ) >> 1;
		out->color[ k ][ 2 ] = ( a->color[ k ][ 2 ] + b->color[ k ][ 2 ] ) >> 1;
		out->color[ k ][ 3 ] = ( a->color[ k ][ 3 ] + b->color[ k ][ 3 ] ) >> 1;
	}

	/* ydnar: added normal interpolation */
	out->normal[ 0 ] = 0.5f * ( a->normal[ 0 ] + b->normal[ 0 ] );
	out->normal[ 1 ] = 0.5f * ( a->normal[ 1 ] + b->normal[ 1 ] );
	out->normal[ 2 ] = 0.5f * ( a->normal[ 2 ] + b->normal[ 2 ] );

	/* if the interpolant created a bogus normal, just copy the normal from a */
	if ( VectorNormalize( out->normal, out->normal ) == 0 ) {
		VectorCopy( a->normal, out->normal );
	}
}