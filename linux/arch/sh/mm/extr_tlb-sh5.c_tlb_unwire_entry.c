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
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long long* dtlb_entries ; 
 int /*<<< orphan*/  dtlb_entry ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sh64_put_wired_dtlb_entry (unsigned long long) ; 
 int /*<<< orphan*/  sh64_teardown_tlb_slot (unsigned long long) ; 

void tlb_unwire_entry(void)
{
	unsigned long long entry;
	unsigned long flags;

	BUG_ON(!dtlb_entry);

	local_irq_save(flags);
	entry = dtlb_entries[dtlb_entry--];

	sh64_teardown_tlb_slot(entry);
	sh64_put_wired_dtlb_entry(entry);

	local_irq_restore(flags);
}