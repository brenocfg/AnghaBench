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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ CBE_PM_16BIT_CTR (scalar_t__) ; 
 scalar_t__ NR_PHYS_CTRS ; 
 scalar_t__ cbe_read_pm (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_control ; 

u32 cbe_get_ctr_size(u32 cpu, u32 phys_ctr)
{
	u32 pm_ctrl, size = 0;

	if (phys_ctr < NR_PHYS_CTRS) {
		pm_ctrl = cbe_read_pm(cpu, pm_control);
		size = (pm_ctrl & CBE_PM_16BIT_CTR(phys_ctr)) ? 16 : 32;
	}

	return size;
}