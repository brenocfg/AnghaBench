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
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ r3k_have_wired_reg ; 
 int /*<<< orphan*/  read_c0_entryhi () ; 
 int /*<<< orphan*/  read_c0_entrylo0 () ; 
 int /*<<< orphan*/  read_c0_index () ; 
 int /*<<< orphan*/  read_c0_wired () ; 

void dump_tlb_regs(void)
{
	pr_info("Index    : %0x\n", read_c0_index());
	pr_info("EntryHi  : %0lx\n", read_c0_entryhi());
	pr_info("EntryLo  : %0lx\n", read_c0_entrylo0());
	if (r3k_have_wired_reg)
		pr_info("Wired    : %0x\n", read_c0_wired());
}