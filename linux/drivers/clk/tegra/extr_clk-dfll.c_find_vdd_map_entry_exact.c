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
struct tegra_dfll {scalar_t__ pmu_if; int /*<<< orphan*/  dev; TYPE_1__* soc; int /*<<< orphan*/  vdd_reg; } ;
struct TYPE_4__ {int step_uv; } ;
struct TYPE_3__ {TYPE_2__ alignment; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TEGRA_DFLL_PMU_PWM ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regulator_count_voltages (int /*<<< orphan*/ ) ; 
 int regulator_list_voltage (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int find_vdd_map_entry_exact(struct tegra_dfll *td, int uV)
{
	int i, n_voltages, reg_uV,reg_volt_id, align_step;

	if (WARN_ON(td->pmu_if == TEGRA_DFLL_PMU_PWM))
		return -EINVAL;

	align_step = uV / td->soc->alignment.step_uv;
	n_voltages = regulator_count_voltages(td->vdd_reg);
	for (i = 0; i < n_voltages; i++) {
		reg_uV = regulator_list_voltage(td->vdd_reg, i);
		if (reg_uV < 0)
			break;

		reg_volt_id = reg_uV / td->soc->alignment.step_uv;

		if (align_step == reg_volt_id)
			return i;
	}

	dev_err(td->dev, "no voltage map entry for %d uV\n", uV);
	return -EINVAL;
}