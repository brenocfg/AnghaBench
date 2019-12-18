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
typedef  int u64 ;
struct kvm_mtrr_range {int base; int mask; } ;

/* Variables and functions */
 int PAGE_MASK ; 

__attribute__((used)) static void var_mtrr_range(struct kvm_mtrr_range *range, u64 *start, u64 *end)
{
	u64 mask;

	*start = range->base & PAGE_MASK;

	mask = range->mask & PAGE_MASK;

	/* This cannot overflow because writing to the reserved bits of
	 * variable MTRRs causes a #GP.
	 */
	*end = (*start | ~mask) + 1;
}