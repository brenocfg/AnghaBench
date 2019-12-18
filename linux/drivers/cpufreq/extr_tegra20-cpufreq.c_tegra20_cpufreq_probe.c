#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  target_intermediate; int /*<<< orphan*/  get_intermediate; int /*<<< orphan*/  target_index; struct tegra20_cpufreq* driver_data; int /*<<< orphan*/  suspend; int /*<<< orphan*/  verify; int /*<<< orphan*/  flags; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; int /*<<< orphan*/  attr; int /*<<< orphan*/  get; } ;
struct tegra20_cpufreq {void* cpu_clk; void* pll_x_clk; void* pll_p_clk; TYPE_1__ driver; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_NAME_LEN ; 
 int /*<<< orphan*/  CPUFREQ_NEED_INITIAL_FREQ_CHECK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* clk_get_sys (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (void*) ; 
 int /*<<< orphan*/  cpufreq_generic_attr ; 
 int /*<<< orphan*/  cpufreq_generic_frequency_table_verify ; 
 int /*<<< orphan*/  cpufreq_generic_get ; 
 int /*<<< orphan*/  cpufreq_generic_suspend ; 
 int cpufreq_register_driver (TYPE_1__*) ; 
 struct tegra20_cpufreq* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra20_cpufreq*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tegra_cpu_exit ; 
 int /*<<< orphan*/  tegra_cpu_init ; 
 int /*<<< orphan*/  tegra_get_intermediate ; 
 int /*<<< orphan*/  tegra_target ; 
 int /*<<< orphan*/  tegra_target_intermediate ; 

__attribute__((used)) static int tegra20_cpufreq_probe(struct platform_device *pdev)
{
	struct tegra20_cpufreq *cpufreq;
	int err;

	cpufreq = devm_kzalloc(&pdev->dev, sizeof(*cpufreq), GFP_KERNEL);
	if (!cpufreq)
		return -ENOMEM;

	cpufreq->cpu_clk = clk_get_sys(NULL, "cclk");
	if (IS_ERR(cpufreq->cpu_clk))
		return PTR_ERR(cpufreq->cpu_clk);

	cpufreq->pll_x_clk = clk_get_sys(NULL, "pll_x");
	if (IS_ERR(cpufreq->pll_x_clk)) {
		err = PTR_ERR(cpufreq->pll_x_clk);
		goto put_cpu;
	}

	cpufreq->pll_p_clk = clk_get_sys(NULL, "pll_p");
	if (IS_ERR(cpufreq->pll_p_clk)) {
		err = PTR_ERR(cpufreq->pll_p_clk);
		goto put_pll_x;
	}

	cpufreq->dev = &pdev->dev;
	cpufreq->driver.get = cpufreq_generic_get;
	cpufreq->driver.attr = cpufreq_generic_attr;
	cpufreq->driver.init = tegra_cpu_init;
	cpufreq->driver.exit = tegra_cpu_exit;
	cpufreq->driver.flags = CPUFREQ_NEED_INITIAL_FREQ_CHECK;
	cpufreq->driver.verify = cpufreq_generic_frequency_table_verify;
	cpufreq->driver.suspend = cpufreq_generic_suspend;
	cpufreq->driver.driver_data = cpufreq;
	cpufreq->driver.target_index = tegra_target;
	cpufreq->driver.get_intermediate = tegra_get_intermediate;
	cpufreq->driver.target_intermediate = tegra_target_intermediate;
	snprintf(cpufreq->driver.name, CPUFREQ_NAME_LEN, "tegra");

	err = cpufreq_register_driver(&cpufreq->driver);
	if (err)
		goto put_pll_p;

	platform_set_drvdata(pdev, cpufreq);

	return 0;

put_pll_p:
	clk_put(cpufreq->pll_p_clk);
put_pll_x:
	clk_put(cpufreq->pll_x_clk);
put_cpu:
	clk_put(cpufreq->cpu_clk);

	return err;
}