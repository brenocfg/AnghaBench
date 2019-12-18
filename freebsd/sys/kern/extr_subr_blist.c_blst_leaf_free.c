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
typedef  int uintmax_t ;
typedef  int u_daddr_t ;
typedef  int daddr_t ;
struct TYPE_3__ {int bm_bitmap; } ;
typedef  TYPE_1__ blmeta_t ;

/* Variables and functions */
 int BLIST_BMAP_MASK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int bitrange (int,int) ; 

__attribute__((used)) static void
blst_leaf_free(blmeta_t *scan, daddr_t blk, int count)
{
	u_daddr_t mask;

	/*
	 * free some data in this bitmap
	 * mask=0000111111111110000
	 *          \_________/\__/
	 *		count   n
	 */
	mask = bitrange(blk & BLIST_BMAP_MASK, count);
	KASSERT((scan->bm_bitmap & mask) == 0,
	    ("freeing free block: %jx, size %d, mask %jx",
	    (uintmax_t)blk, count, (uintmax_t)scan->bm_bitmap & mask));
	scan->bm_bitmap |= mask;
}