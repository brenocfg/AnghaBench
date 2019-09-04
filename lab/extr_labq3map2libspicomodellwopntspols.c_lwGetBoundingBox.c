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
struct TYPE_5__ {int count; TYPE_1__* pt; } ;
typedef  TYPE_2__ lwPointList ;
struct TYPE_4__ {float* pos; } ;

/* Variables and functions */

void lwGetBoundingBox( lwPointList *point, float bbox[] ){
	int i, j;

	if ( point->count == 0 ) {
		return;
	}

	for ( i = 0; i < 6; i++ )
		if ( bbox[ i ] != 0.0f ) {
			return;
		}

	bbox[ 0 ] = bbox[ 1 ] = bbox[ 2 ] = 1e20f;
	bbox[ 3 ] = bbox[ 4 ] = bbox[ 5 ] = -1e20f;
	for ( i = 0; i < point->count; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			if ( bbox[ j ] > point->pt[ i ].pos[ j ] ) {
				bbox[ j ] = point->pt[ i ].pos[ j ];
			}
			if ( bbox[ j + 3 ] < point->pt[ i ].pos[ j ] ) {
				bbox[ j + 3 ] = point->pt[ i ].pos[ j ];
			}
		}
	}
}