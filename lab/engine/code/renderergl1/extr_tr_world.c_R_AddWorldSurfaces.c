#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  integer; } ;
struct TYPE_8__ {int rdflags; unsigned long long num_dlights; } ;
struct TYPE_6__ {int /*<<< orphan*/ * visBounds; } ;
struct TYPE_9__ {int currentEntityNum; int shiftedEntityNum; TYPE_3__ refdef; TYPE_2__* world; TYPE_1__ viewParms; } ;
struct TYPE_7__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long MAX_DLIGHTS ; 
 int QSORT_REFENTITYNUM_SHIFT ; 
 int RDF_NOWORLDMODEL ; 
 int REFENTITYNUM_WORLD ; 
 int /*<<< orphan*/  R_MarkLeaves () ; 
 int /*<<< orphan*/  R_RecursiveWorldNode (int /*<<< orphan*/ ,int,unsigned long long) ; 
 TYPE_5__* r_drawworld ; 
 TYPE_4__ tr ; 

void R_AddWorldSurfaces (void) {
	if ( !r_drawworld->integer ) {
		return;
	}

	if ( tr.refdef.rdflags & RDF_NOWORLDMODEL ) {
		return;
	}

	tr.currentEntityNum = REFENTITYNUM_WORLD;
	tr.shiftedEntityNum = tr.currentEntityNum << QSORT_REFENTITYNUM_SHIFT;

	// determine which leaves are in the PVS / areamask
	R_MarkLeaves ();

	// clear out the visible min/max
	ClearBounds( tr.viewParms.visBounds[0], tr.viewParms.visBounds[1] );

	// perform frustum culling and add all the potentially visible surfaces
	if ( tr.refdef.num_dlights > MAX_DLIGHTS ) {
		tr.refdef.num_dlights = MAX_DLIGHTS ;
	}
	R_RecursiveWorldNode( tr.world->nodes, 15, ( 1ULL << tr.refdef.num_dlights ) - 1 );
}