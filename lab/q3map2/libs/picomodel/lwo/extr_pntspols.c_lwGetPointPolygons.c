#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int count; TYPE_2__* pol; } ;
typedef  TYPE_4__ lwPolygonList ;
struct TYPE_12__ {int count; TYPE_3__* pt; } ;
typedef  TYPE_5__ lwPointList ;
struct TYPE_10__ {size_t npols; int* pol; } ;
struct TYPE_9__ {int nverts; TYPE_1__* v; } ;
struct TYPE_8__ {size_t index; } ;

/* Variables and functions */
 int* _pico_calloc (size_t,int) ; 

int lwGetPointPolygons( lwPointList *point, lwPolygonList *polygon ){
	int i, j, k;

	/* count the number of polygons per point */

	for ( i = 0; i < polygon->count; i++ )
		for ( j = 0; j < polygon->pol[ i ].nverts; j++ )
			++point->pt[ polygon->pol[ i ].v[ j ].index ].npols;

	/* alloc per-point polygon arrays */

	for ( i = 0; i < point->count; i++ ) {
		if ( point->pt[ i ].npols == 0 ) {
			continue;
		}
		point->pt[ i ].pol = _pico_calloc( point->pt[ i ].npols, sizeof( int ) );
		if ( !point->pt[ i ].pol ) {
			return 0;
		}
		point->pt[ i ].npols = 0;
	}

	/* fill in polygon array for each point */

	for ( i = 0; i < polygon->count; i++ ) {
		for ( j = 0; j < polygon->pol[ i ].nverts; j++ ) {
			k = polygon->pol[ i ].v[ j ].index;
			point->pt[ k ].pol[ point->pt[ k ].npols ] = i;
			++point->pt[ k ].npols;
		}
	}

	return 1;
}