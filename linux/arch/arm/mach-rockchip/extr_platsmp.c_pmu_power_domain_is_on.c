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
 int BIT (int) ; 
 int /*<<< orphan*/  PMU_PWRDN_ST ; 
 int /*<<< orphan*/  pmu ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int pmu_power_domain_is_on(int pd)
{
	u32 val;
	int ret;

	ret = regmap_read(pmu, PMU_PWRDN_ST, &val);
	if (ret < 0)
		return ret;

	return !(val & BIT(pd));
}