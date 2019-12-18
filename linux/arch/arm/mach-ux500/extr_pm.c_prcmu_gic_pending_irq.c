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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ GIC_DIST_ENABLE_SET ; 
 scalar_t__ GIC_DIST_PENDING_SET ; 
 int PRCMU_GIC_NUMBER_REGS ; 
 scalar_t__ dist_base ; 
 int readl_relaxed (scalar_t__) ; 

bool prcmu_gic_pending_irq(void)
{
	u32 pr; /* Pending register */
	u32 er; /* Enable register */
	int i;

	/* 5 registers. STI & PPI not skipped */
	for (i = 0; i < PRCMU_GIC_NUMBER_REGS; i++) {

		pr = readl_relaxed(dist_base + GIC_DIST_PENDING_SET + i * 4);
		er = readl_relaxed(dist_base + GIC_DIST_ENABLE_SET + i * 4);

		if (pr & er)
			return true; /* There is a pending interrupt */
	}

	return false;
}