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
typedef  int uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  integer; } ;
struct TYPE_8__ {int rdflags; unsigned long long num_dlights; unsigned long long num_pshadows; int /*<<< orphan*/  dlightMask; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/ * visBounds; } ;
struct TYPE_9__ {int currentEntityNum; int shiftedEntityNum; scalar_t__ viewCount; TYPE_3__ refdef; TYPE_2__* world; TYPE_1__ viewParms; } ;
struct TYPE_7__ {int numWorldSurfaces; scalar_t__* surfacesViewCount; int /*<<< orphan*/ * surfacesDlightBits; int /*<<< orphan*/ * surfacesPshadowBits; scalar_t__ surfaces; int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long MAX_DLIGHTS ; 
 unsigned long long MAX_DRAWN_PSHADOWS ; 
 int QSORT_REFENTITYNUM_SHIFT ; 
 int RDF_NOWORLDMODEL ; 
 int REFENTITYNUM_WORLD ; 
 int /*<<< orphan*/  R_AddWorldSurface (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_MarkLeaves () ; 
 int /*<<< orphan*/  R_RecursiveWorldNode (int /*<<< orphan*/ ,int,int,int) ; 
 int VPF_DEPTHSHADOW ; 
 int VPF_FARPLANEFRUSTUM ; 
 int VPF_SHADOWMAP ; 
 TYPE_5__* r_drawworld ; 
 TYPE_4__ tr ; 

void R_AddWorldSurfaces (void) {
	uint32_t planeBits, dlightBits, pshadowBits;

	if ( !r_drawworld->integer ) {
		return;
	}

	if ( tr.refdef.rdflags & RDF_NOWORLDMODEL ) {
		return;
	}

	tr.currentEntityNum = REFENTITYNUM_WORLD;
	tr.shiftedEntityNum = tr.currentEntityNum << QSORT_REFENTITYNUM_SHIFT;

	// determine which leaves are in the PVS / areamask
	if (!(tr.viewParms.flags & VPF_DEPTHSHADOW))
		R_MarkLeaves ();

	// clear out the visible min/max
	ClearBounds( tr.viewParms.visBounds[0], tr.viewParms.visBounds[1] );

	// perform frustum culling and flag all the potentially visible surfaces
	if ( tr.refdef.num_dlights > MAX_DLIGHTS ) {
		tr.refdef.num_dlights = MAX_DLIGHTS ;
	}

	if ( tr.refdef.num_pshadows > MAX_DRAWN_PSHADOWS ) {
		tr.refdef.num_pshadows = MAX_DRAWN_PSHADOWS;
	}

	planeBits = (tr.viewParms.flags & VPF_FARPLANEFRUSTUM) ? 31 : 15;

	if ( tr.viewParms.flags & VPF_DEPTHSHADOW )
	{
		dlightBits = 0;
		pshadowBits = 0;
	}
	else if ( !(tr.viewParms.flags & VPF_SHADOWMAP) )
	{
		dlightBits = ( 1ULL << tr.refdef.num_dlights ) - 1;
		pshadowBits = ( 1ULL << tr.refdef.num_pshadows ) - 1;
	}
	else
	{
		dlightBits = ( 1ULL << tr.refdef.num_dlights ) - 1;
		pshadowBits = 0;
	}

	R_RecursiveWorldNode( tr.world->nodes, planeBits, dlightBits, pshadowBits);

	// now add all the potentially visible surfaces
	// also mask invisible dlights for next frame
	{
		int i;

		tr.refdef.dlightMask = 0;

		for (i = 0; i < tr.world->numWorldSurfaces; i++)
		{
			if (tr.world->surfacesViewCount[i] != tr.viewCount)
				continue;

			R_AddWorldSurface( tr.world->surfaces + i, tr.world->surfacesDlightBits[i], tr.world->surfacesPshadowBits[i] );
			tr.refdef.dlightMask |= tr.world->surfacesDlightBits[i];
		}

		tr.refdef.dlightMask = ~tr.refdef.dlightMask;
	}
}