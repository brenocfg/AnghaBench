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
 int /*<<< orphan*/  local_irq_disable () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_cpu_online (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void stop_this_cpu(void *dummy)
{
	/* Remove this CPU */
	set_cpu_online(smp_processor_id(), false);

	local_irq_disable();
	/* CPU Doze */
	if (mfspr(SPR_UPR) & SPR_UPR_PMP)
		mtspr(SPR_PMR, mfspr(SPR_PMR) | SPR_PMR_DME);
	/* If that didn't work, infinite loop */
	while (1)
		;
}