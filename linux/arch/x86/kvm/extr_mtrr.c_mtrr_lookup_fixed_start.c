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
struct mtrr_iter {int fixed; int index; int seg; int /*<<< orphan*/  start; int /*<<< orphan*/  mtrr_state; } ;

/* Variables and functions */
 int fixed_mtrr_addr_seg_to_range_index (int /*<<< orphan*/ ,int) ; 
 int fixed_mtrr_addr_to_seg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_mtrr_is_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mtrr_lookup_fixed_start(struct mtrr_iter *iter)
{
	int seg, index;

	if (!fixed_mtrr_is_enabled(iter->mtrr_state))
		return false;

	seg = fixed_mtrr_addr_to_seg(iter->start);
	if (seg < 0)
		return false;

	iter->fixed = true;
	index = fixed_mtrr_addr_seg_to_range_index(iter->start, seg);
	iter->index = index;
	iter->seg = seg;
	return true;
}