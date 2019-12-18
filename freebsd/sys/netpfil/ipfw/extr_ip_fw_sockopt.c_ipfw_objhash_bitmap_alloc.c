#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int BLOCK_ITEMS ; 
 size_t IPFW_MAX_SETS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/ * malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,size_t) ; 

void
ipfw_objhash_bitmap_alloc(uint32_t items, void **idx, int *pblocks)
{
	size_t size;
	int max_blocks;
	u_long *idx_mask;

	KASSERT((items % BLOCK_ITEMS) == 0,
	   ("bitmask size needs to power of 2 and greater or equal to %zu",
	    BLOCK_ITEMS));

	max_blocks = items / BLOCK_ITEMS;
	size = items / 8;
	idx_mask = malloc(size * IPFW_MAX_SETS, M_IPFW, M_WAITOK);
	/* Mark all as free */
	memset(idx_mask, 0xFF, size * IPFW_MAX_SETS);
	*idx_mask &= ~(u_long)1; /* Skip index 0 */

	*idx = idx_mask;
	*pblocks = max_blocks;
}