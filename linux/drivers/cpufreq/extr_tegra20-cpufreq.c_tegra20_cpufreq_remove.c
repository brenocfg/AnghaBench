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
struct tegra20_cpufreq {int /*<<< orphan*/  cpu_clk; int /*<<< orphan*/  pll_x_clk; int /*<<< orphan*/  pll_p_clk; int /*<<< orphan*/  driver; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_unregister_driver (int /*<<< orphan*/ *) ; 
 struct tegra20_cpufreq* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tegra20_cpufreq_remove(struct platform_device *pdev)
{
	struct tegra20_cpufreq *cpufreq = platform_get_drvdata(pdev);

	cpufreq_unregister_driver(&cpufreq->driver);

	clk_put(cpufreq->pll_p_clk);
	clk_put(cpufreq->pll_x_clk);
	clk_put(cpufreq->cpu_clk);

	return 0;
}