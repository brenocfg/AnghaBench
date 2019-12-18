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
typedef  int /*<<< orphan*/  u_long ;
struct namedobj_instance {int max_blocks; int /*<<< orphan*/ * idx_mask; } ;

/* Variables and functions */

void
ipfw_objhash_bitmap_swap(struct namedobj_instance *ni, void **idx, int *blocks)
{
	int old_blocks;
	u_long *old_idx;

	old_idx = ni->idx_mask;
	old_blocks = ni->max_blocks;

	ni->idx_mask = *idx;
	ni->max_blocks = *blocks;

	/* Save old values */
	*idx = old_idx;
	*blocks = old_blocks;
}