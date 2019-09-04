#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  fraction; } ;
struct TYPE_15__ {int contents; TYPE_1__ trace; int /*<<< orphan*/ * bounds; } ;
typedef  TYPE_2__ traceWork_t ;
struct TYPE_16__ {scalar_t__ checkcount; int contents; int /*<<< orphan*/ * bounds; } ;
typedef  TYPE_3__ cbrush_t ;
struct TYPE_17__ {scalar_t__ checkcount; int contents; } ;
typedef  TYPE_4__ cPatch_t ;
struct TYPE_18__ {int numLeafBrushes; int firstLeafBrush; int numLeafSurfaces; int firstLeafSurface; } ;
typedef  TYPE_5__ cLeaf_t ;
struct TYPE_20__ {int* leafbrushes; scalar_t__ checkcount; size_t* leafsurfaces; TYPE_4__** surfaces; TYPE_3__* brushes; } ;
struct TYPE_19__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_BoundsIntersect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CM_TraceThroughBrush (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  CM_TraceThroughPatch (TYPE_2__*,TYPE_4__*) ; 
 TYPE_7__ cm ; 
 TYPE_6__* cm_noCurves ; 

void CM_TraceThroughLeaf( traceWork_t *tw, cLeaf_t *leaf ) {
	int			k;
	int			brushnum;
	cbrush_t	*b;
	cPatch_t	*patch;

	// trace line against all brushes in the leaf
	for ( k = 0 ; k < leaf->numLeafBrushes ; k++ ) {
		brushnum = cm.leafbrushes[leaf->firstLeafBrush+k];

		b = &cm.brushes[brushnum];
		if ( b->checkcount == cm.checkcount ) {
			continue;	// already checked this brush in another leaf
		}
		b->checkcount = cm.checkcount;

		if ( !(b->contents & tw->contents) ) {
			continue;
		}

		if ( !CM_BoundsIntersect( tw->bounds[0], tw->bounds[1],
					b->bounds[0], b->bounds[1] ) ) {
			continue;
		}

		CM_TraceThroughBrush( tw, b );
		if ( !tw->trace.fraction ) {
			return;
		}
	}

	// trace line against all patches in the leaf
#ifdef BSPC
	if (1) {
#else
	if ( !cm_noCurves->integer ) {
#endif
		for ( k = 0 ; k < leaf->numLeafSurfaces ; k++ ) {
			patch = cm.surfaces[ cm.leafsurfaces[ leaf->firstLeafSurface + k ] ];
			if ( !patch ) {
				continue;
			}
			if ( patch->checkcount == cm.checkcount ) {
				continue;	// already checked this patch in another leaf
			}
			patch->checkcount = cm.checkcount;

			if ( !(patch->contents & tw->contents) ) {
				continue;
			}
			
			CM_TraceThroughPatch( tw, patch );
			if ( !tw->trace.fraction ) {
				return;
			}
		}
	}
}