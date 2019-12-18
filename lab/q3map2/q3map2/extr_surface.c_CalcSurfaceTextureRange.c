#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_7__ {int numVerts; float* bias; int* texMins; int* texMaxs; int* texRange; TYPE_2__* verts; TYPE_1__* shaderInfo; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_6__ {float* st; } ;
struct TYPE_5__ {int shaderWidth; int shaderHeight; } ;

/* Variables and functions */
 float floor (float) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int texRange ; 

qboolean CalcSurfaceTextureRange( mapDrawSurface_t *ds ){
	int i, j, v, size[ 2 ];
	float mins[ 2 ], maxs[ 2 ];


	/* try to early out */
	if ( ds->numVerts <= 0 ) {
		return qtrue;
	}

	/* walk the verts and determine min/max st values */
	mins[ 0 ] = 999999;
	mins[ 1 ] = 999999;
	maxs[ 0 ] = -999999;
	maxs[ 1 ] = -999999;
	for ( i = 0; i < ds->numVerts; i++ )
	{
		for ( j = 0; j < 2; j++ )
		{
			if ( ds->verts[ i ].st[ j ] < mins[ j ] ) {
				mins[ j ] = ds->verts[ i ].st[ j ];
			}
			if ( ds->verts[ i ].st[ j ] > maxs[ j ] ) {
				maxs[ j ] = ds->verts[ i ].st[ j ];
			}
		}
	}

	/* clamp to integer range and calculate surface bias values */
	for ( j = 0; j < 2; j++ )
		ds->bias[ j ] = -floor( 0.5f * ( mins[ j ] + maxs[ j ] ) );

	/* find biased texture coordinate mins/maxs */
	size[ 0 ] = ds->shaderInfo->shaderWidth;
	size[ 1 ] = ds->shaderInfo->shaderHeight;
	ds->texMins[ 0 ] = 999999;
	ds->texMins[ 1 ] = 999999;
	ds->texMaxs[ 0 ] = -999999;
	ds->texMaxs[ 1 ] = -999999;
	for ( i = 0; i < ds->numVerts; i++ )
	{
		for ( j = 0; j < 2; j++ )
		{
			v = ( (float) ds->verts[ i ].st[ j ] + ds->bias[ j ] ) * size[ j ];
			if ( v < ds->texMins[ j ] ) {
				ds->texMins[ j ] = v;
			}
			if ( v > ds->texMaxs[ j ] ) {
				ds->texMaxs[ j ] = v;
			}
		}
	}

	/* calc ranges */
	for ( j = 0; j < 2; j++ )
		ds->texRange[ j ] = ( ds->texMaxs[ j ] - ds->texMins[ j ] );

	/* if range is zero, then assume unlimited precision */
	if ( texRange == 0 ) {
		return qtrue;
	}

	/* within range? */
	for ( j = 0; j < 2; j++ )
	{
		if ( ds->texMins[ j ] < -texRange || ds->texMaxs[ j ] > texRange ) {
			return qfalse;
		}
	}

	/* within range */
	return qtrue;
}