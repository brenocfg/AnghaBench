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
typedef  int uint16_t ;
typedef  int u_long ;
struct namedobj_instance {int* free_off; int* idx_mask; int max_blocks; } ;

/* Variables and functions */
 int BLOCK_ITEMS ; 
 int ffsl (int) ; 

int
ipfw_objhash_alloc_idx(void *n, uint16_t *pidx)
{
	struct namedobj_instance *ni;
	u_long *mask;
	int i, off, v;

	ni = (struct namedobj_instance *)n;

	off = ni->free_off[0];
	mask = &ni->idx_mask[off];

	for (i = off; i < ni->max_blocks; i++, mask++) {
		if ((v = ffsl(*mask)) == 0)
			continue;

		/* Mark as busy */
		*mask &= ~ ((u_long)1 << (v - 1));

		ni->free_off[0] = i;
		
		v = BLOCK_ITEMS * i + v - 1;

		*pidx = v;
		return (0);
	}

	return (1);
}