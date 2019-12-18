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
 int /*<<< orphan*/  CPU_PM_CTRL_ALL ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int soc_power_ctrl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_power_ctrl_set (int) ; 

__attribute__((used)) static __inline void
pm_disable_device(int mask)
{
#ifdef DIAGNOSTIC
	uint32_t reg;

	reg = soc_power_ctrl_get(CPU_PM_CTRL_ALL);
	printf("Power Management Register: 0%x\n", reg);

	reg &= ~mask;
	soc_power_ctrl_set(reg);
	printf("Device %x is disabled\n", mask);

	reg = soc_power_ctrl_get(CPU_PM_CTRL_ALL);
	printf("Power Management Register: 0%x\n", reg);
#endif
}