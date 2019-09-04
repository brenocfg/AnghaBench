#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int contents; scalar_t__ fraction; scalar_t__ allsolid; scalar_t__ startsolid; } ;
struct TYPE_14__ {int contents; TYPE_1__ trace; } ;
typedef  TYPE_2__ traceWork_t ;
struct TYPE_15__ {scalar_t__ checkcount; int contents; } ;
typedef  TYPE_3__ cbrush_t ;
struct TYPE_16__ {scalar_t__ checkcount; int contents; int /*<<< orphan*/  pc; } ;
typedef  TYPE_4__ cPatch_t ;
struct TYPE_17__ {int numLeafBrushes; int firstLeafBrush; int numLeafSurfaces; int firstLeafSurface; } ;
typedef  TYPE_5__ cLeaf_t ;
struct TYPE_19__ {int* leafbrushes; scalar_t__ checkcount; size_t* leafsurfaces; TYPE_4__** surfaces; TYPE_3__* brushes; } ;
struct TYPE_18__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 scalar_t__ CM_PositionTestInPatchCollide (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CM_TestBoxInBrush (TYPE_2__*,TYPE_3__*) ; 
 TYPE_7__ cm ; 
 TYPE_6__* cm_noCurves ; 
 scalar_t__ qtrue ; 

void CM_TestInLeaf( traceWork_t *tw, cLeaf_t *leaf ) {
	int			k;
	int			brushnum;
	cbrush_t	*b;
	cPatch_t	*patch;

	// test box position against all brushes in the leaf
	for (k=0 ; k<leaf->numLeafBrushes ; k++) {
		brushnum = cm.leafbrushes[leaf->firstLeafBrush+k];
		b = &cm.brushes[brushnum];
		if (b->checkcount == cm.checkcount) {
			continue;	// already checked this brush in another leaf
		}
		b->checkcount = cm.checkcount;

		if ( !(b->contents & tw->contents)) {
			continue;
		}
		
		CM_TestBoxInBrush( tw, b );
		if ( tw->trace.allsolid ) {
			return;
		}
	}

	// test against all patches
#ifdef BSPC
	if (1) {
#else
	if ( !cm_noCurves->integer ) {
#endif //BSPC
		for ( k = 0 ; k < leaf->numLeafSurfaces ; k++ ) {
			patch = cm.surfaces[ cm.leafsurfaces[ leaf->firstLeafSurface + k ] ];
			if ( !patch ) {
				continue;
			}
			if ( patch->checkcount == cm.checkcount ) {
				continue;	// already checked this brush in another leaf
			}
			patch->checkcount = cm.checkcount;

			if ( !(patch->contents & tw->contents)) {
				continue;
			}
			
			if ( CM_PositionTestInPatchCollide( tw, patch->pc ) ) {
				tw->trace.startsolid = tw->trace.allsolid = qtrue;
				tw->trace.fraction = 0;
				tw->trace.contents = patch->contents;
				return;
			}
		}
	}
}