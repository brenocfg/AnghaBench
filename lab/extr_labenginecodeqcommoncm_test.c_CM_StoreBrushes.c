#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__** bounds; scalar_t__ count; scalar_t__ maxcount; scalar_t__ list; int /*<<< orphan*/  overflowed; } ;
typedef  TYPE_1__ leafList_t ;
struct TYPE_7__ {scalar_t__ checkcount; scalar_t__** bounds; } ;
typedef  TYPE_2__ cbrush_t ;
struct TYPE_8__ {int numLeafBrushes; int firstLeafBrush; } ;
typedef  TYPE_3__ cLeaf_t ;
struct TYPE_9__ {int* leafbrushes; scalar_t__ checkcount; TYPE_2__* brushes; TYPE_3__* leafs; } ;

/* Variables and functions */
 TYPE_4__ cm ; 
 int /*<<< orphan*/  qtrue ; 

void CM_StoreBrushes( leafList_t *ll, int nodenum ) {
	int			i, k;
	int			leafnum;
	int			brushnum;
	cLeaf_t		*leaf;
	cbrush_t	*b;

	leafnum = -1 - nodenum;

	leaf = &cm.leafs[leafnum];

	for ( k = 0 ; k < leaf->numLeafBrushes ; k++ ) {
		brushnum = cm.leafbrushes[leaf->firstLeafBrush+k];
		b = &cm.brushes[brushnum];
		if ( b->checkcount == cm.checkcount ) {
			continue;	// already checked this brush in another leaf
		}
		b->checkcount = cm.checkcount;
		for ( i = 0 ; i < 3 ; i++ ) {
			if ( b->bounds[0][i] >= ll->bounds[1][i] || b->bounds[1][i] <= ll->bounds[0][i] ) {
				break;
			}
		}
		if ( i != 3 ) {
			continue;
		}
		if ( ll->count >= ll->maxcount) {
			ll->overflowed = qtrue;
			return;
		}
		((cbrush_t **)ll->list)[ ll->count++ ] = b;
	}
#if 0
	// store patches?
	for ( k = 0 ; k < leaf->numLeafSurfaces ; k++ ) {
		patch = cm.surfaces[ cm.leafsurfaces[ leaf->firstleafsurface + k ] ];
		if ( !patch ) {
			continue;
		}
	}
#endif
}