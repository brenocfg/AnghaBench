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
 unsigned long GET_HIGH_SLICE_INDEX (unsigned long) ; 
 unsigned long GET_LOW_SLICE_INDEX (unsigned long) ; 
 unsigned long SLICE_HIGH_SHIFT ; 
 unsigned long SLICE_LOW_SHIFT ; 
 unsigned long SLICE_LOW_TOP ; 
 scalar_t__ slice_addr_is_low (unsigned long) ; 
 int /*<<< orphan*/  test_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool slice_scan_available(unsigned long addr,
				 const struct slice_mask *available,
				 int end, unsigned long *boundary_addr)
{
	unsigned long slice;
	if (slice_addr_is_low(addr)) {
		slice = GET_LOW_SLICE_INDEX(addr);
		*boundary_addr = (slice + end) << SLICE_LOW_SHIFT;
		return !!(available->low_slices & (1u << slice));
	} else {
		slice = GET_HIGH_SLICE_INDEX(addr);
		*boundary_addr = (slice + end) ?
			((slice + end) << SLICE_HIGH_SHIFT) : SLICE_LOW_TOP;
		return !!test_bit(slice, available->high_slices);
	}
}