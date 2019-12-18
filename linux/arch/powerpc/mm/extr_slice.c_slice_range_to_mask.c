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
struct slice_mask {unsigned int low_slices; int /*<<< orphan*/  high_slices; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,unsigned long) ; 
 unsigned long GET_HIGH_SLICE_INDEX (unsigned long) ; 
 unsigned int GET_LOW_SLICE_INDEX (unsigned long) ; 
 unsigned long SLICE_HIGH_SHIFT ; 
 int SLICE_LOW_TOP ; 
 scalar_t__ SLICE_NUM_HIGH ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 scalar_t__ slice_addr_is_low (unsigned long) ; 

__attribute__((used)) static void slice_range_to_mask(unsigned long start, unsigned long len,
				struct slice_mask *ret)
{
	unsigned long end = start + len - 1;

	ret->low_slices = 0;
	if (SLICE_NUM_HIGH)
		bitmap_zero(ret->high_slices, SLICE_NUM_HIGH);

	if (slice_addr_is_low(start)) {
		unsigned long mend = min(end,
					 (unsigned long)(SLICE_LOW_TOP - 1));

		ret->low_slices = (1u << (GET_LOW_SLICE_INDEX(mend) + 1))
			- (1u << GET_LOW_SLICE_INDEX(start));
	}

	if (SLICE_NUM_HIGH && !slice_addr_is_low(end)) {
		unsigned long start_index = GET_HIGH_SLICE_INDEX(start);
		unsigned long align_end = ALIGN(end, (1UL << SLICE_HIGH_SHIFT));
		unsigned long count = GET_HIGH_SLICE_INDEX(align_end) - start_index;

		bitmap_set(ret->high_slices, start_index, count);
	}
}