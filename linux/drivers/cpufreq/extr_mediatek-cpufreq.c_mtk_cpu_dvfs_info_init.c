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
struct regulator {int dummy; } ;
struct mtk_cpu_dvfs_info {int need_voltage_tracking; int /*<<< orphan*/  cpus; struct regulator* inter_clk; struct regulator* cpu_clk; struct regulator* sram_reg; struct regulator* proc_reg; struct device* cpu_dev; int /*<<< orphan*/  intermediate_voltage; } ;
struct device {int dummy; } ;
typedef  struct regulator dev_pm_opp ;
typedef  struct regulator clk ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
 struct regulator* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 struct regulator* clk_get (struct device*,char*) ; 
 unsigned long clk_get_rate (struct regulator*) ; 
 int /*<<< orphan*/  clk_put (struct regulator*) ; 
 struct regulator* dev_pm_opp_find_freq_ceil (struct device*,unsigned long*) ; 
 int /*<<< orphan*/  dev_pm_opp_get_voltage (struct regulator*) ; 
 int dev_pm_opp_of_cpumask_add_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_opp_of_cpumask_remove_table (int /*<<< orphan*/ *) ; 
 int dev_pm_opp_of_get_sharing_cpus (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct regulator*) ; 
 struct device* get_cpu_device (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 struct regulator* regulator_get_exclusive (struct device*,char*) ; 
 struct regulator* regulator_get_optional (struct device*,char*) ; 
 int /*<<< orphan*/  regulator_put (struct regulator*) ; 

__attribute__((used)) static int mtk_cpu_dvfs_info_init(struct mtk_cpu_dvfs_info *info, int cpu)
{
	struct device *cpu_dev;
	struct regulator *proc_reg = ERR_PTR(-ENODEV);
	struct regulator *sram_reg = ERR_PTR(-ENODEV);
	struct clk *cpu_clk = ERR_PTR(-ENODEV);
	struct clk *inter_clk = ERR_PTR(-ENODEV);
	struct dev_pm_opp *opp;
	unsigned long rate;
	int ret;

	cpu_dev = get_cpu_device(cpu);
	if (!cpu_dev) {
		pr_err("failed to get cpu%d device\n", cpu);
		return -ENODEV;
	}

	cpu_clk = clk_get(cpu_dev, "cpu");
	if (IS_ERR(cpu_clk)) {
		if (PTR_ERR(cpu_clk) == -EPROBE_DEFER)
			pr_warn("cpu clk for cpu%d not ready, retry.\n", cpu);
		else
			pr_err("failed to get cpu clk for cpu%d\n", cpu);

		ret = PTR_ERR(cpu_clk);
		return ret;
	}

	inter_clk = clk_get(cpu_dev, "intermediate");
	if (IS_ERR(inter_clk)) {
		if (PTR_ERR(inter_clk) == -EPROBE_DEFER)
			pr_warn("intermediate clk for cpu%d not ready, retry.\n",
				cpu);
		else
			pr_err("failed to get intermediate clk for cpu%d\n",
			       cpu);

		ret = PTR_ERR(inter_clk);
		goto out_free_resources;
	}

	proc_reg = regulator_get_optional(cpu_dev, "proc");
	if (IS_ERR(proc_reg)) {
		if (PTR_ERR(proc_reg) == -EPROBE_DEFER)
			pr_warn("proc regulator for cpu%d not ready, retry.\n",
				cpu);
		else
			pr_err("failed to get proc regulator for cpu%d\n",
			       cpu);

		ret = PTR_ERR(proc_reg);
		goto out_free_resources;
	}

	/* Both presence and absence of sram regulator are valid cases. */
	sram_reg = regulator_get_exclusive(cpu_dev, "sram");

	/* Get OPP-sharing information from "operating-points-v2" bindings */
	ret = dev_pm_opp_of_get_sharing_cpus(cpu_dev, &info->cpus);
	if (ret) {
		pr_err("failed to get OPP-sharing information for cpu%d\n",
		       cpu);
		goto out_free_resources;
	}

	ret = dev_pm_opp_of_cpumask_add_table(&info->cpus);
	if (ret) {
		pr_warn("no OPP table for cpu%d\n", cpu);
		goto out_free_resources;
	}

	/* Search a safe voltage for intermediate frequency. */
	rate = clk_get_rate(inter_clk);
	opp = dev_pm_opp_find_freq_ceil(cpu_dev, &rate);
	if (IS_ERR(opp)) {
		pr_err("failed to get intermediate opp for cpu%d\n", cpu);
		ret = PTR_ERR(opp);
		goto out_free_opp_table;
	}
	info->intermediate_voltage = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	info->cpu_dev = cpu_dev;
	info->proc_reg = proc_reg;
	info->sram_reg = IS_ERR(sram_reg) ? NULL : sram_reg;
	info->cpu_clk = cpu_clk;
	info->inter_clk = inter_clk;

	/*
	 * If SRAM regulator is present, software "voltage tracking" is needed
	 * for this CPU power domain.
	 */
	info->need_voltage_tracking = !IS_ERR(sram_reg);

	return 0;

out_free_opp_table:
	dev_pm_opp_of_cpumask_remove_table(&info->cpus);

out_free_resources:
	if (!IS_ERR(proc_reg))
		regulator_put(proc_reg);
	if (!IS_ERR(sram_reg))
		regulator_put(sram_reg);
	if (!IS_ERR(cpu_clk))
		clk_put(cpu_clk);
	if (!IS_ERR(inter_clk))
		clk_put(inter_clk);

	return ret;
}