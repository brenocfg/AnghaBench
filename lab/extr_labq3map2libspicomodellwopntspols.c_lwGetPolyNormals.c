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
struct TYPE_11__ {int count; TYPE_3__* pol; } ;
typedef  TYPE_4__ lwPolygonList ;
struct TYPE_12__ {TYPE_1__* pt; } ;
typedef  TYPE_5__ lwPointList ;
struct TYPE_10__ {int nverts; int /*<<< orphan*/  norm; TYPE_2__* v; } ;
struct TYPE_9__ {size_t index; } ;
struct TYPE_8__ {float* pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  cross (float*,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize (int /*<<< orphan*/ ) ; 

void lwGetPolyNormals( lwPointList *point, lwPolygonList *polygon ){
	int i, j;
	float p1[ 3 ], p2[ 3 ], pn[ 3 ], v1[ 3 ], v2[ 3 ];

	for ( i = 0; i < polygon->count; i++ ) {
		if ( polygon->pol[ i ].nverts < 3 ) {
			continue;
		}
		for ( j = 0; j < 3; j++ ) {
			p1[ j ] = point->pt[ polygon->pol[ i ].v[ 0 ].index ].pos[ j ];
			p2[ j ] = point->pt[ polygon->pol[ i ].v[ 1 ].index ].pos[ j ];
			pn[ j ] = point->pt[ polygon->pol[ i ].v[
									 polygon->pol[ i ].nverts - 1 ].index ].pos[ j ];
		}

		for ( j = 0; j < 3; j++ ) {
			v1[ j ] = p2[ j ] - p1[ j ];
			v2[ j ] = pn[ j ] - p1[ j ];
		}

		cross( v1, v2, polygon->pol[ i ].norm );
		normalize( polygon->pol[ i ].norm );
	}
}