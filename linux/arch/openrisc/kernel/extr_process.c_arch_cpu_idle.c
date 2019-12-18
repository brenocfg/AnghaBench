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
 int /*<<< orphan*/  SPR_PMR ; 
 int SPR_PMR_DME ; 
 int /*<<< orphan*/  SPR_UPR ; 
 int SPR_UPR_PMP ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

void arch_cpu_idle(void)
{
	local_irq_enable();
	if (mfspr(SPR_UPR) & SPR_UPR_PMP)
		mtspr(SPR_PMR, mfspr(SPR_PMR) | SPR_PMR_DME);
}