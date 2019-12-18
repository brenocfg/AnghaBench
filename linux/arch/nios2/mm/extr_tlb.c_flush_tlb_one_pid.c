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
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  replace_tlb_one_pid (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_tlb_one_pid(unsigned long addr, unsigned long mmu_pid)
{
	pr_debug("Flush tlb-entry for vaddr=%#lx\n", addr);

	replace_tlb_one_pid(addr, mmu_pid, 0);
}