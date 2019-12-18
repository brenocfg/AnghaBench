#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {TYPE_1__* per_cpu; } ;
struct TYPE_3__ {int /*<<< orphan*/  resume_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_SYSFAB_POWER_CONTROL (unsigned int) ; 
 int ENOSYS ; 
 TYPE_2__* al_cpu_resume_regs ; 
 int /*<<< orphan*/  al_sysfabric ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_supported ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int alpine_cpu_wakeup(unsigned int phys_cpu, uint32_t phys_resume_addr)
{
	if (!wakeup_supported)
		return -ENOSYS;

	/*
	 * Set CPU resume address -
	 * secure firmware running on boot will jump to this address
	 * after setting proper CPU mode, and initialiing e.g. secure
	 * regs (the same mode all CPUs are booted to - usually HYP)
	 */
	writel(phys_resume_addr,
	       &al_cpu_resume_regs->per_cpu[phys_cpu].resume_addr);

	/* Power-up the CPU */
	regmap_write(al_sysfabric, AL_SYSFAB_POWER_CONTROL(phys_cpu), 0);

	return 0;
}