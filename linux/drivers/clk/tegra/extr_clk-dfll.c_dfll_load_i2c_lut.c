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
struct tegra_dfll {int lut_min; int lut_max; scalar_t__ lut_base; int /*<<< orphan*/ * lut; int /*<<< orphan*/  vdd_reg; } ;

/* Variables and functions */
 int MAX_DFLL_VOLTAGES ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dfll_i2c_wmb (struct tegra_dfll*) ; 
 int /*<<< orphan*/  regulator_list_hardware_vsel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dfll_load_i2c_lut(struct tegra_dfll *td)
{
	int i, lut_index;
	u32 val;

	for (i = 0; i < MAX_DFLL_VOLTAGES; i++) {
		if (i < td->lut_min)
			lut_index = td->lut_min;
		else if (i > td->lut_max)
			lut_index = td->lut_max;
		else
			lut_index = i;

		val = regulator_list_hardware_vsel(td->vdd_reg,
						     td->lut[lut_index]);
		__raw_writel(val, td->lut_base + i * 4);
	}

	dfll_i2c_wmb(td);
}