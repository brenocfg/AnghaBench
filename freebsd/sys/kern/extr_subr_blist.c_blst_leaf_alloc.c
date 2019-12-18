#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_daddr_t ;
typedef  int daddr_t ;
struct TYPE_4__ {int bm_bitmap; int bm_bighint; } ;
typedef  TYPE_1__ blmeta_t ;

/* Variables and functions */
 int BLIST_BMAP_MASK ; 
 int BLIST_BMAP_RADIX ; 
 int BLIST_MAX_ALLOC ; 
 int SWAPBLK_NONE ; 
 int bitpos (int) ; 
 int bitrange (int,int) ; 
 int blst_next_leaf_alloc (TYPE_1__*,int,int,int) ; 
 int flip_hibits (int) ; 
 int fls (int) ; 

__attribute__((used)) static daddr_t
blst_leaf_alloc(blmeta_t *scan, daddr_t blk, int *count, int maxcount)
{
	u_daddr_t cursor_mask, mask;
	int count1, hi, lo, num_shifts, range1, range_ext;

	range1 = 0;
	count1 = *count - 1;
	num_shifts = fls(count1);
	mask = scan->bm_bitmap;
	while (flip_hibits(mask) != 0 && num_shifts > 0) {
		/*
		 * If bit i is set in mask, then bits in [i, i+range1] are set
		 * in scan->bm_bitmap.  The value of range1 is equal to count1
		 * >> num_shifts.  Grow range1 and reduce num_shifts to 0,
		 * while preserving these invariants.  The updates to mask
		 * leave fewer bits set, but each bit that remains set
		 * represents a longer string of consecutive bits set in
		 * scan->bm_bitmap.  If more updates to mask cannot clear more
		 * bits, because mask is partitioned with all 0 bits preceding
		 * all 1 bits, the loop terminates immediately.
		 */
		num_shifts--;
		range_ext = range1 + ((count1 >> num_shifts) & 1);
		/*
		 * mask is a signed quantity for the shift because when it is
		 * shifted right, the sign bit should copied; when the last
		 * block of the leaf is free, pretend, for a while, that all the
		 * blocks that follow it are also free.
		 */
		mask &= (daddr_t)mask >> range_ext;
		range1 += range_ext;
	}
	if (mask == 0) {
		/*
		 * Update bighint.  There is no allocation bigger than range1
		 * starting in this leaf.
		 */
		scan->bm_bighint = range1;
		return (SWAPBLK_NONE);
	}

	/* Discard any candidates that appear before blk. */
	if ((blk & BLIST_BMAP_MASK) != 0) {
		cursor_mask = mask & bitrange(0, blk & BLIST_BMAP_MASK);
		if (cursor_mask != 0) {
			mask ^= cursor_mask;
			if (mask == 0)
				return (SWAPBLK_NONE);

			/*
			 * Bighint change for last block allocation cannot
			 * assume that any other blocks are allocated, so the
			 * bighint cannot be reduced much.
			 */
			range1 = BLIST_MAX_ALLOC - 1;
		}
		blk &= ~BLIST_BMAP_MASK;
	}

	/*
	 * The least significant set bit in mask marks the start of the first
	 * available range of sufficient size.  Find its position.
	 */
	lo = bitpos(mask);

	/*
	 * Find how much space is available starting at that position.
	 */
	if (flip_hibits(mask) != 0) {
		/* Count the 1 bits starting at position lo. */
		hi = bitpos(flip_hibits(mask)) + count1;
		if (maxcount < hi - lo)
			hi = lo + maxcount;
		*count = hi - lo;
		mask = bitrange(lo, *count);
	} else if (maxcount <= BLIST_BMAP_RADIX - lo) {
		/* All the blocks we can use are available here. */
		hi = lo + maxcount;
		*count = maxcount;
		mask = bitrange(lo, *count);
	} else {
		/* Check next leaf for some of the blocks we want or need. */
		count1 = *count - (BLIST_BMAP_RADIX - lo);
		maxcount -= BLIST_BMAP_RADIX - lo;
		hi = blst_next_leaf_alloc(scan, blk, count1, maxcount);
		if (hi < count1)
			/*
			 * The next leaf cannot supply enough blocks to reach
			 * the minimum required allocation.  The hint cannot be
			 * updated, because the same allocation request could
			 * be satisfied later, by this leaf, if the state of
			 * the next leaf changes, and without any changes to
			 * this leaf.
			 */
			return (SWAPBLK_NONE);
		*count = BLIST_BMAP_RADIX - lo + hi;
		hi = BLIST_BMAP_RADIX;
	}

	if (hi == BLIST_BMAP_RADIX) {
		/*
		 * Update bighint.  There is no allocation bigger than range1
		 * available in this leaf after this allocation completes.
		 */
		scan->bm_bighint = range1;
	}
	/* Clear the allocated bits from this leaf. */
	scan->bm_bitmap &= ~mask;
	return (blk + lo);
}