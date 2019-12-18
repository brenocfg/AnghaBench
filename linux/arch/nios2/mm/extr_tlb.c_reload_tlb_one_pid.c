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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_tlb_one_pid (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reload_tlb_one_pid(unsigned long addr, unsigned long mmu_pid, pte_t pte)
{
	pr_debug("Reload tlb-entry for vaddr=%#lx\n", addr);

	replace_tlb_one_pid(addr, mmu_pid, pte_val(pte));
}