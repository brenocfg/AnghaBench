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

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NR_SPACE_IDS ; 
 unsigned long SHIFT_PER_LONG ; 
 unsigned long SPACEID_SHIFT ; 
 scalar_t__ dirty_space_ids ; 
 unsigned long find_next_zero_bit (long*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 scalar_t__ free_space_ids ; 
 int /*<<< orphan*/  sid_lock ; 
 long* space_id ; 
 unsigned long space_id_index ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

unsigned long alloc_sid(void)
{
	unsigned long index;

	spin_lock(&sid_lock);

	if (free_space_ids == 0) {
		if (dirty_space_ids != 0) {
			spin_unlock(&sid_lock);
			flush_tlb_all(); /* flush_tlb_all() calls recycle_sids() */
			spin_lock(&sid_lock);
		}
		BUG_ON(free_space_ids == 0);
	}

	free_space_ids--;

	index = find_next_zero_bit(space_id, NR_SPACE_IDS, space_id_index);
	space_id[index >> SHIFT_PER_LONG] |= (1L << (index & (BITS_PER_LONG - 1)));
	space_id_index = index;

	spin_unlock(&sid_lock);

	return index << SPACEID_SHIFT;
}