#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* si; } ;
typedef  TYPE_2__ surfaceInfo_t ;
struct TYPE_8__ {int numLightSurfaces; int firstLightSurface; int w; int h; scalar_t__* styles; } ;
typedef  TYPE_3__ rawLightmap_t ;
struct TYPE_6__ {int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 int MAX_LIGHTMAPS ; 
 size_t* lightSurfaces ; 
 TYPE_3__* rawLightmaps ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* surfaceInfos ; 

__attribute__((used)) static int CompareRawLightmap( const void *a, const void *b ){
	rawLightmap_t   *alm, *blm;
	surfaceInfo_t   *aInfo, *bInfo;
	int i, min, diff;


	/* get lightmaps */
	alm = &rawLightmaps[ *( (int*) a ) ];
	blm = &rawLightmaps[ *( (int*) b ) ];

	/* get min number of surfaces */
	min = ( alm->numLightSurfaces < blm->numLightSurfaces ? alm->numLightSurfaces : blm->numLightSurfaces );

	/* iterate */
	for ( i = 0; i < min; i++ )
	{
		/* get surface info */
		aInfo = &surfaceInfos[ lightSurfaces[ alm->firstLightSurface + i ] ];
		bInfo = &surfaceInfos[ lightSurfaces[ blm->firstLightSurface + i ] ];

		/* compare shader names */
		diff = strcmp( aInfo->si->shader, bInfo->si->shader );
		if ( diff != 0 ) {
			return diff;
		}
	}

	/* test style count */
	diff = 0;
	for ( i = 0; i < MAX_LIGHTMAPS; i++ )
		diff += blm->styles[ i ] - alm->styles[ i ];
	if ( diff ) {
		return diff;
	}

	/* compare size */
	diff = ( blm->w * blm->h ) - ( alm->w * alm->h );
	if ( diff != 0 ) {
		return diff;
	}

	/* must be equivalent */
	return 0;
}