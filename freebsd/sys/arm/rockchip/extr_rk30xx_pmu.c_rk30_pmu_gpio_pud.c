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
 int PMU_GPIO0A_PULL ; 
 int /*<<< orphan*/  pmu_write_4 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rk30_pmu_sc ; 

void
rk30_pmu_gpio_pud(uint32_t pin, uint32_t state)
{
	uint32_t offset;

	offset = PMU_GPIO0A_PULL + ((pin / 8) * 4);
	pin = (pin % 8) * 2;
	pmu_write_4(rk30_pmu_sc, offset, (0x3 << (16 + pin)) | (state << pin));
}