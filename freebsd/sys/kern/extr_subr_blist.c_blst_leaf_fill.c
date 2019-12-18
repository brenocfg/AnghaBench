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
typedef  int daddr_t ;
struct TYPE_3__ {int bm_bitmap; } ;
typedef  TYPE_1__ blmeta_t ;

/* Variables and functions */
 int BLIST_BMAP_MASK ; 
 int bitcount64 (int) ; 
 int bitrange (int,int) ; 

__attribute__((used)) static daddr_t
blst_leaf_fill(blmeta_t *scan, daddr_t blk, int count)
{
	daddr_t nblks;
	u_daddr_t mask;

	mask = bitrange(blk & BLIST_BMAP_MASK, count);

	/* Count the number of blocks that we are allocating. */
	nblks = bitcount64(scan->bm_bitmap & mask);

	scan->bm_bitmap &= ~mask;
	return (nblks);
}