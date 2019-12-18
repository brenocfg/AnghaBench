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
typedef  scalar_t__ int64_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPA_MAXBLOCKSIZE ; 
 scalar_t__ aggsum_lower_bound (int /*<<< orphan*/ *) ; 
 int arc_c ; 
 int /*<<< orphan*/  arc_size ; 
 int zfs_arc_overflow_shift ; 

__attribute__((used)) static boolean_t
arc_is_overflowing(void)
{
	/* Always allow at least one block of overflow */
	int64_t overflow = MAX(SPA_MAXBLOCKSIZE,
	    arc_c >> zfs_arc_overflow_shift);

	/*
	 * We just compare the lower bound here for performance reasons. Our
	 * primary goals are to make sure that the arc never grows without
	 * bound, and that it can reach its maximum size. This check
	 * accomplishes both goals. The maximum amount we could run over by is
	 * 2 * aggsum_borrow_multiplier * NUM_CPUS * the average size of a block
	 * in the ARC. In practice, that's in the tens of MB, which is low
	 * enough to be safe.
	 */
	return (aggsum_lower_bound(&arc_size) >= (int64_t)arc_c + overflow);
}