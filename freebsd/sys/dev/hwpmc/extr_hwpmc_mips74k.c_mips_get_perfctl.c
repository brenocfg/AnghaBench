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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALL ; 
 int /*<<< orphan*/  MDP ; 
 int MIPS74K_PMC_ENABLE ; 
 int MIPS74K_PMC_INTERRUPT_ENABLE ; 
 int MIPS74K_PMC_KERNEL_ENABLE ; 
 int MIPS74K_PMC_SELECT ; 
 int MIPS74K_PMC_SUPER_ENABLE ; 
 int MIPS74K_PMC_USER_ENABLE ; 
 int /*<<< orphan*/  PMCDBG2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int) ; 
 int PMC_CAP_INTERRUPT ; 
 int PMC_CAP_SYSTEM ; 
 int PMC_CAP_USER ; 

uint32_t
mips_get_perfctl(int cpu, int ri, uint32_t event, uint32_t caps)
{
	uint32_t config;

	config = event;

	config <<= MIPS74K_PMC_SELECT;

	if (caps & PMC_CAP_SYSTEM)
		config |= (MIPS74K_PMC_SUPER_ENABLE |
			   MIPS74K_PMC_KERNEL_ENABLE);
	if (caps & PMC_CAP_USER)
		config |= MIPS74K_PMC_USER_ENABLE;
	if ((caps & (PMC_CAP_USER | PMC_CAP_SYSTEM)) == 0)
		config |= MIPS74K_PMC_ENABLE;
	if (caps & PMC_CAP_INTERRUPT)
		config |= MIPS74K_PMC_INTERRUPT_ENABLE;

	PMCDBG2(MDP,ALL,2,"mips74k-get_perfctl ri=%d -> config=0x%x", ri, config);

	return (config);
}