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
struct TYPE_4__ {scalar_t__ bm_bitmap; } ;
typedef  TYPE_1__ blmeta_t ;

/* Variables and functions */
 int BLIST_BMAP_RADIX ; 
 int BLIST_META_MASK ; 
 int BLIST_META_RADIX ; 
 int blst_leaf_fill (TYPE_1__*,int,int) ; 
 int radix_to_skip (int) ; 
 int ummin (int,int) ; 

__attribute__((used)) static daddr_t
blst_meta_fill(blmeta_t *scan, daddr_t allocBlk, daddr_t count, u_daddr_t radix)
{
	daddr_t blk, endBlk, i, nblks, skip;
	int digit;

	if (radix == BLIST_BMAP_RADIX)
		return (blst_leaf_fill(scan, allocBlk, count));

	endBlk = ummin(allocBlk + count, (allocBlk + radix) & -radix);
	radix /= BLIST_META_RADIX;
	skip = radix_to_skip(radix);
	blk = allocBlk & -radix;
	nblks = 0;
	while (blk < endBlk) {
		digit = (blk / radix) & BLIST_META_MASK;
		i = 1 + digit * skip;
		blk += radix;
		count = ummin(blk, endBlk) - allocBlk;
		nblks += blst_meta_fill(&scan[i], allocBlk, count, radix);
		if (scan[i].bm_bitmap == 0)
			scan->bm_bitmap &= ~((u_daddr_t)1 << digit);
		allocBlk = blk;
	}
	return (nblks);
}