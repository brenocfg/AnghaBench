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
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_3__* vm_object_t ;
struct swdevt {int dummy; } ;
struct swblk {scalar_t__* d; scalar_t__ p; } ;
typedef  scalar_t__ daddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  swp_blks; } ;
struct TYPE_7__ {TYPE_1__ swp; } ;
struct TYPE_8__ {TYPE_2__ un_pager; } ;

/* Variables and functions */
 scalar_t__ MAXPHYS ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ SWAPBLK_NONE ; 
 int SWAP_META_PAGES ; 
 struct swblk* SWAP_PCTRIE_LOOKUP_GE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  swp_pager_force_pagein (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  swp_pager_isondev (scalar_t__,struct swdevt*) ; 

__attribute__((used)) static void
swap_pager_swapoff_object(struct swdevt *sp, vm_object_t object)
{
	struct swblk *sb;
	vm_pindex_t pi, s_pindex;
	daddr_t blk, n_blks, s_blk;
	int i;

	n_blks = 0;
	for (pi = 0; (sb = SWAP_PCTRIE_LOOKUP_GE(
	    &object->un_pager.swp.swp_blks, pi)) != NULL; ) {
		for (i = 0; i < SWAP_META_PAGES; i++) {
			blk = sb->d[i];
			if (!swp_pager_isondev(blk, sp))
				blk = SWAPBLK_NONE;

			/*
			 * If there are no blocks/pages accumulated, start a new
			 * accumulation here.
			 */
			if (n_blks == 0) {
				if (blk != SWAPBLK_NONE) {
					s_blk = blk;
					s_pindex = sb->p + i;
					n_blks = 1;
				}
				continue;
			}

			/*
			 * If the accumulation can be extended without breaking
			 * the sequence of consecutive blocks and pages that
			 * swp_pager_force_pagein() depends on, do so.
			 */
			if (n_blks < MAXPHYS / PAGE_SIZE &&
			    s_blk + n_blks == blk &&
			    s_pindex + n_blks == sb->p + i) {
				++n_blks;
				continue;
			}

			/*
			 * The sequence of consecutive blocks and pages cannot
			 * be extended, so page them all in here.  Then,
			 * because doing so involves releasing and reacquiring
			 * a lock that protects the swap block pctrie, do not
			 * rely on the current swap block.  Break this loop and
			 * re-fetch the same pindex from the pctrie again.
			 */
			swp_pager_force_pagein(object, s_pindex, n_blks);
			n_blks = 0;
			break;
		}
		if (i == SWAP_META_PAGES)
			pi = sb->p + SWAP_META_PAGES;
	}
	if (n_blks > 0)
		swp_pager_force_pagein(object, s_pindex, n_blks);
}