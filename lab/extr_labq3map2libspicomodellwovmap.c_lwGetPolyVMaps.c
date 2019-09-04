#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lwVMapPt ;
struct TYPE_9__ {int nverts; size_t* pindex; scalar_t__* vindex; struct TYPE_9__* next; scalar_t__ perpoly; } ;
typedef  TYPE_2__ lwVMap ;
struct TYPE_10__ {int count; TYPE_1__* pol; } ;
typedef  TYPE_3__ lwPolygonList ;
struct TYPE_11__ {scalar_t__ index; int nvmaps; TYPE_7__* vm; } ;
typedef  TYPE_4__ lwPolVert ;
struct TYPE_12__ {int index; TYPE_2__* vmap; } ;
struct TYPE_8__ {int nverts; TYPE_4__* v; } ;

/* Variables and functions */
 TYPE_7__* _pico_calloc (int,int) ; 

int lwGetPolyVMaps( lwPolygonList *polygon, lwVMap *vmap ){
	lwVMap *vm;
	lwPolVert *pv;
	int i, j;

	/* count the number of vmap values for each polygon vertex */

	vm = vmap;
	while ( vm ) {
		if ( vm->perpoly ) {
			for ( i = 0; i < vm->nverts; i++ ) {
				for ( j = 0; j < polygon->pol[ vm->pindex[ i ]].nverts; j++ ) {
					pv = &polygon->pol[ vm->pindex[ i ]].v[ j ];
					if ( vm->vindex[ i ] == pv->index ) {
						++pv->nvmaps;
						break;
					}
				}
			}
		}
		vm = vm->next;
	}

	/* allocate vmap references for each mapped vertex */

	for ( i = 0; i < polygon->count; i++ ) {
		for ( j = 0; j < polygon->pol[ i ].nverts; j++ ) {
			pv = &polygon->pol[ i ].v[ j ];
			if ( pv->nvmaps ) {
				pv->vm = _pico_calloc( pv->nvmaps, sizeof( lwVMapPt ) );
				if ( !pv->vm ) {
					return 0;
				}
				pv->nvmaps = 0;
			}
		}
	}

	/* fill in vmap references for each mapped point */

	vm = vmap;
	while ( vm ) {
		if ( vm->perpoly ) {
			for ( i = 0; i < vm->nverts; i++ ) {
				for ( j = 0; j < polygon->pol[ vm->pindex[ i ]].nverts; j++ ) {
					pv = &polygon->pol[ vm->pindex[ i ]].v[ j ];
					if ( vm->vindex[ i ] == pv->index ) {
						pv->vm[ pv->nvmaps ].vmap = vm;
						pv->vm[ pv->nvmaps ].index = i;
						++pv->nvmaps;
						break;
					}
				}
			}
		}
		vm = vm->next;
	}

	return 1;
}