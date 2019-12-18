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
typedef  scalar_t__ daddr_t ;
typedef  TYPE_1__* blist_t ;
struct TYPE_3__ {scalar_t__ bl_cursor; int bl_avail; scalar_t__ bl_blocks; int /*<<< orphan*/  bl_radix; int /*<<< orphan*/  bl_root; } ;

/* Variables and functions */
 int BLIST_MAX_ALLOC ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SWAPBLK_NONE ; 
 scalar_t__ blst_meta_alloc (int /*<<< orphan*/ ,scalar_t__,int*,int,int /*<<< orphan*/ ) ; 

daddr_t
blist_alloc(blist_t bl, int *count, int maxcount)
{
	daddr_t blk, cursor;

	KASSERT(*count <= maxcount,
	    ("invalid parameters %d > %d", *count, maxcount));
	KASSERT(*count <= BLIST_MAX_ALLOC,
	    ("minimum allocation too large: %d", *count));

	/*
	 * This loop iterates at most twice.  An allocation failure in the
	 * first iteration leads to a second iteration only if the cursor was
	 * non-zero.  When the cursor is zero, an allocation failure will
	 * stop further iterations.
	 */
	for (cursor = bl->bl_cursor;; cursor = 0) {
		blk = blst_meta_alloc(bl->bl_root, cursor, count, maxcount,
		    bl->bl_radix);
		if (blk != SWAPBLK_NONE) {
			bl->bl_avail -= *count;
			bl->bl_cursor = blk + *count;
			if (bl->bl_cursor == bl->bl_blocks)
				bl->bl_cursor = 0;
			return (blk);
		}
		if (cursor == 0)
			return (SWAPBLK_NONE);
	}
}