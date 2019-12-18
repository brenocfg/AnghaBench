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
 scalar_t__ PARAVIRT_LAZY_MMU ; 
 int /*<<< orphan*/  arch_enter_lazy_mmu_mode () ; 
 int /*<<< orphan*/  arch_leave_lazy_mmu_mode () ; 
 scalar_t__ paravirt_get_lazy_mode () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void paravirt_flush_lazy_mmu(void)
{
	preempt_disable();

	if (paravirt_get_lazy_mode() == PARAVIRT_LAZY_MMU) {
		arch_leave_lazy_mmu_mode();
		arch_enter_lazy_mmu_mode();
	}

	preempt_enable();
}