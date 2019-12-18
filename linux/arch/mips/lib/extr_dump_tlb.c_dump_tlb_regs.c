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
#define  CPU_R10000 131 
#define  CPU_R12000 130 
#define  CPU_R14000 129 
#define  CPU_R16000 128 
 scalar_t__ cpu_has_guestid ; 
 scalar_t__ cpu_has_htw ; 
 scalar_t__ cpu_has_rixi ; 
 scalar_t__ cpu_has_small_pages ; 
 scalar_t__ cpu_has_xpa ; 
 int current_cpu_type () ; 
 int /*<<< orphan*/  pr_info (char*,int const,...) ; 
 int /*<<< orphan*/  read_c0_entryhi () ; 
 int /*<<< orphan*/  read_c0_entrylo0 () ; 
 int /*<<< orphan*/  read_c0_entrylo1 () ; 
 int /*<<< orphan*/  read_c0_framemask () ; 
 int /*<<< orphan*/  read_c0_guestctl1 () ; 
 int /*<<< orphan*/  read_c0_index () ; 
 int /*<<< orphan*/  read_c0_pagegrain () ; 
 int /*<<< orphan*/  read_c0_pagemask () ; 
 int /*<<< orphan*/  read_c0_pwctl () ; 
 int /*<<< orphan*/  read_c0_pwfield () ; 
 int /*<<< orphan*/  read_c0_pwsize () ; 
 int /*<<< orphan*/  read_c0_wired () ; 

void dump_tlb_regs(void)
{
	const int field = 2 * sizeof(unsigned long);

	pr_info("Index    : %0x\n", read_c0_index());
	pr_info("PageMask : %0x\n", read_c0_pagemask());
	if (cpu_has_guestid)
		pr_info("GuestCtl1: %0x\n", read_c0_guestctl1());
	pr_info("EntryHi  : %0*lx\n", field, read_c0_entryhi());
	pr_info("EntryLo0 : %0*lx\n", field, read_c0_entrylo0());
	pr_info("EntryLo1 : %0*lx\n", field, read_c0_entrylo1());
	pr_info("Wired    : %0x\n", read_c0_wired());
	switch (current_cpu_type()) {
	case CPU_R10000:
	case CPU_R12000:
	case CPU_R14000:
	case CPU_R16000:
		pr_info("FrameMask: %0x\n", read_c0_framemask());
		break;
	}
	if (cpu_has_small_pages || cpu_has_rixi || cpu_has_xpa)
		pr_info("PageGrain: %0x\n", read_c0_pagegrain());
	if (cpu_has_htw) {
		pr_info("PWField  : %0*lx\n", field, read_c0_pwfield());
		pr_info("PWSize   : %0*lx\n", field, read_c0_pwsize());
		pr_info("PWCtl    : %0x\n", read_c0_pwctl());
	}
}