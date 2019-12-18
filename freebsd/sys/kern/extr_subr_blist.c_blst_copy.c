#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_daddr_t ;
typedef  scalar_t__ daddr_t ;
struct TYPE_3__ {int bm_bitmap; } ;
typedef  TYPE_1__ blmeta_t ;
typedef  int /*<<< orphan*/  blist_t ;

/* Variables and functions */
 scalar_t__ BLIST_BMAP_RADIX ; 
 scalar_t__ BLIST_META_RADIX ; 
 int /*<<< orphan*/  blist_free (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ radix_to_skip (scalar_t__) ; 

__attribute__((used)) static void
blst_copy(blmeta_t *scan, daddr_t blk, daddr_t radix, blist_t dest,
    daddr_t count)
{
	daddr_t endBlk, i, skip;

	/*
	 * Leaf node
	 */

	if (radix == BLIST_BMAP_RADIX) {
		u_daddr_t v = scan->bm_bitmap;

		if (v == (u_daddr_t)-1) {
			blist_free(dest, blk, count);
		} else if (v != 0) {
			int i;

			for (i = 0; i < count; ++i) {
				if (v & ((u_daddr_t)1 << i))
					blist_free(dest, blk + i, 1);
			}
		}
		return;
	}

	/*
	 * Meta node
	 */

	if (scan->bm_bitmap == 0) {
		/*
		 * Source all allocated, leave dest allocated
		 */
		return;
	}

	endBlk = blk + count;
	radix /= BLIST_META_RADIX;
	skip = radix_to_skip(radix);
	for (i = 1; blk < endBlk; i += skip) {
		blk += radix;
		count = radix;
		if (blk >= endBlk)
			count -= blk - endBlk;
		blst_copy(&scan[i], blk - radix, radix, dest, count);
	}
}