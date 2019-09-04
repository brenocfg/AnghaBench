#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_3__ {float* mins; float* maxs; } ;
typedef  TYPE_1__ brush_t ;
struct TYPE_4__ {TYPE_1__* brush; } ;

/* Variables and functions */
 int defaultFogNum ; 
 TYPE_2__* mapFogs ; 
 int numMapFogs ; 

int FogForBounds( vec3_t mins, vec3_t maxs, float epsilon ){
	int fogNum, i, j;
	float highMin, lowMax, volume, bestVolume;
	vec3_t fogMins, fogMaxs, overlap;
	brush_t         *brush;


	/* start with bogus fog num */
	fogNum = defaultFogNum;

	/* init */
	bestVolume = 0.0f;

	/* walk the list of fog volumes */
	for ( i = 0; i < numMapFogs; i++ )
	{
		/* sof2: global fog doesn't reference a brush */
		if ( mapFogs[ i ].brush == NULL ) {
			fogNum = i;
			continue;
		}

		/* get fog brush */
		brush = mapFogs[ i ].brush;

		/* get bounds */
		fogMins[ 0 ] = brush->mins[ 0 ] - epsilon;
		fogMins[ 1 ] = brush->mins[ 1 ] - epsilon;
		fogMins[ 2 ] = brush->mins[ 2 ] - epsilon;
		fogMaxs[ 0 ] = brush->maxs[ 0 ] + epsilon;
		fogMaxs[ 1 ] = brush->maxs[ 1 ] + epsilon;
		fogMaxs[ 2 ] = brush->maxs[ 2 ] + epsilon;

		/* check against bounds */
		for ( j = 0; j < 3; j++ )
		{
			if ( mins[ j ] > fogMaxs[ j ] || maxs[ j ] < fogMins[ j ] ) {
				break;
			}
			highMin = mins[ j ] > fogMins[ j ] ? mins[ j ] : fogMins[ j ];
			lowMax = maxs[ j ] < fogMaxs[ j ] ? maxs[ j ] : fogMaxs[ j ];
			overlap[ j ] = lowMax - highMin;
			if ( overlap[ j ] < 1.0f ) {
				overlap[ j ] = 1.0f;
			}
		}

		/* no overlap */
		if ( j < 3 ) {
			continue;
		}

		/* get volume */
		volume = overlap[ 0 ] * overlap[ 1 ] * overlap[ 2 ];

		/* test against best volume */
		if ( volume > bestVolume ) {
			bestVolume = volume;
			fogNum = i;
		}
	}

	/* if the point made it this far, it's not inside any fog volumes (or inside global fog) */
	return fogNum;
}