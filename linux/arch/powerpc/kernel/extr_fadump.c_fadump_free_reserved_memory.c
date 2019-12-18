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
 unsigned long HZ ; 
 int /*<<< orphan*/  PFN_PHYS (unsigned long) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  free_reserved_page (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void fadump_free_reserved_memory(unsigned long start_pfn,
					unsigned long end_pfn)
{
	unsigned long pfn;
	unsigned long time_limit = jiffies + HZ;

	pr_info("freeing reserved memory (0x%llx - 0x%llx)\n",
		PFN_PHYS(start_pfn), PFN_PHYS(end_pfn));

	for (pfn = start_pfn; pfn < end_pfn; pfn++) {
		free_reserved_page(pfn_to_page(pfn));

		if (time_after(jiffies, time_limit)) {
			cond_resched();
			time_limit = jiffies + HZ;
		}
	}
}