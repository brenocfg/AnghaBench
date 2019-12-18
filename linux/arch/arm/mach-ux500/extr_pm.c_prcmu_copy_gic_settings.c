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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ GIC_DIST_ENABLE_SET ; 
 int PRCMU_GIC_NUMBER_REGS ; 
 scalar_t__ PRCM_ARMITMSK31TO0 ; 
 scalar_t__ dist_base ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int prcmu_copy_gic_settings(void)
{
	u32 er; /* Enable register */
	int i;

	/* We skip the STI and PPI */
	for (i = 0; i < PRCMU_GIC_NUMBER_REGS - 1; i++) {
		er = readl_relaxed(dist_base +
				   GIC_DIST_ENABLE_SET + (i + 1) * 4);
		writel(er, PRCM_ARMITMSK31TO0 + i * 4);
	}

	return 0;
}