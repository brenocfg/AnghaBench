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
 int MTRR_TO_PHYS_WC_OFFSET ; 
 int /*<<< orphan*/  MTRR_TYPE_WRCOMB ; 
 int mtrr_add (unsigned long,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtrr_enabled () ; 
 scalar_t__ pat_enabled () ; 
 int /*<<< orphan*/  pr_warn (char*,void*,void*) ; 

int arch_phys_wc_add(unsigned long base, unsigned long size)
{
	int ret;

	if (pat_enabled() || !mtrr_enabled())
		return 0;  /* Success!  (We don't need to do anything.) */

	ret = mtrr_add(base, size, MTRR_TYPE_WRCOMB, true);
	if (ret < 0) {
		pr_warn("Failed to add WC MTRR for [%p-%p]; performance may suffer.",
			(void *)base, (void *)(base + size - 1));
		return ret;
	}
	return ret + MTRR_TO_PHYS_WC_OFFSET;
}