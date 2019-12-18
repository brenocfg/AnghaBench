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
struct namedobj_instance {int max_blocks; int* idx_mask; int* free_off; } ;

/* Variables and functions */
 int BLOCK_ITEMS ; 

int
ipfw_objhash_free_idx(struct namedobj_instance *ni, uint16_t idx)
{
	u_long *mask;
	int i, v;

	i = idx / BLOCK_ITEMS;
	v = idx % BLOCK_ITEMS;

	if (i >= ni->max_blocks)
		return (1);

	mask = &ni->idx_mask[i];

	if ((*mask & ((u_long)1 << v)) != 0)
		return (1);

	/* Mark as free */
	*mask |= (u_long)1 << v;

	/* Update free offset */
	if (ni->free_off[0] > i)
		ni->free_off[0] = i;
	
	return (0);
}