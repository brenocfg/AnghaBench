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
 int /*<<< orphan*/  cpu_switch_mm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idmap_pgd ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  local_flush_bp_all () ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 

void setup_mm_for_reboot(void)
{
	/* Switch to the identity mapping. */
	cpu_switch_mm(idmap_pgd, &init_mm);
	local_flush_bp_all();

#ifdef CONFIG_CPU_HAS_ASID
	/*
	 * We don't have a clean ASID for the identity mapping, which
	 * may clash with virtual addresses of the previous page tables
	 * and therefore potentially in the TLB.
	 */
	local_flush_tlb_all();
#endif
}