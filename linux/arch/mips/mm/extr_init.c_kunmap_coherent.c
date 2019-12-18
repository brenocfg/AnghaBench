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
 unsigned long UNIQUE_ENTRYHI (unsigned int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 unsigned int num_wired_entries () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 unsigned long read_c0_entryhi () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_entrylo1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_index (unsigned int) ; 
 int /*<<< orphan*/  write_c0_wired (unsigned int) ; 

void kunmap_coherent(void)
{
	unsigned int wired;
	unsigned long flags, old_ctx;

	local_irq_save(flags);
	old_ctx = read_c0_entryhi();
	wired = num_wired_entries() - 1;
	write_c0_wired(wired);
	write_c0_index(wired);
	write_c0_entryhi(UNIQUE_ENTRYHI(wired));
	write_c0_entrylo0(0);
	write_c0_entrylo1(0);
	mtc0_tlbw_hazard();
	tlb_write_indexed();
	tlbw_use_hazard();
	write_c0_entryhi(old_ctx);
	local_irq_restore(flags);
	pagefault_enable();
	preempt_enable();
}