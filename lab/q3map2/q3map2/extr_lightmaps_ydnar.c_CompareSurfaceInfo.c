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
struct TYPE_3__ {scalar_t__ model; scalar_t__ hasLightmap; scalar_t__ sampleSize; scalar_t__* axis; scalar_t__* plane; scalar_t__* mins; } ;
typedef  TYPE_1__ surfaceInfo_t ;

/* Variables and functions */
 TYPE_1__* surfaceInfos ; 

__attribute__((used)) static int CompareSurfaceInfo( const void *a, const void *b ){
	surfaceInfo_t   *aInfo, *bInfo;
	int i;


	/* get surface info */
	aInfo = &surfaceInfos[ *( (int*) a ) ];
	bInfo = &surfaceInfos[ *( (int*) b ) ];

	/* model first */
	if ( aInfo->model < bInfo->model ) {
		return 1;
	}
	else if ( aInfo->model > bInfo->model ) {
		return -1;
	}

	/* then lightmap status */
	if ( aInfo->hasLightmap < bInfo->hasLightmap ) {
		return 1;
	}
	else if ( aInfo->hasLightmap > bInfo->hasLightmap ) {
		return -1;
	}

	/* then lightmap sample size */
	if ( aInfo->sampleSize < bInfo->sampleSize ) {
		return 1;
	}
	else if ( aInfo->sampleSize > bInfo->sampleSize ) {
		return -1;
	}

	/* then lightmap axis */
	for ( i = 0; i < 3; i++ )
	{
		if ( aInfo->axis[ i ] < bInfo->axis[ i ] ) {
			return 1;
		}
		else if ( aInfo->axis[ i ] > bInfo->axis[ i ] ) {
			return -1;
		}
	}

	/* then plane */
	if ( aInfo->plane == NULL && bInfo->plane != NULL ) {
		return 1;
	}
	else if ( aInfo->plane != NULL && bInfo->plane == NULL ) {
		return -1;
	}
	else if ( aInfo->plane != NULL && bInfo->plane != NULL ) {
		for ( i = 0; i < 4; i++ )
		{
			if ( aInfo->plane[ i ] < bInfo->plane[ i ] ) {
				return 1;
			}
			else if ( aInfo->plane[ i ] > bInfo->plane[ i ] ) {
				return -1;
			}
		}
	}

	/* then position in world */
	for ( i = 0; i < 3; i++ )
	{
		if ( aInfo->mins[ i ] < bInfo->mins[ i ] ) {
			return 1;
		}
		else if ( aInfo->mins[ i ] > bInfo->mins[ i ] ) {
			return -1;
		}
	}

	/* these are functionally identical (this should almost never happen) */
	return 0;
}