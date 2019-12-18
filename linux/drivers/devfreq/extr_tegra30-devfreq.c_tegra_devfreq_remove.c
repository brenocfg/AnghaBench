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
struct tegra_devfreq {int /*<<< orphan*/  clock; int /*<<< orphan*/  reset; int /*<<< orphan*/  rate_change_nb; int /*<<< orphan*/  emc_clock; int /*<<< orphan*/  devfreq; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_opp_remove_all_dynamic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devfreq_remove_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfreq_remove_governor (int /*<<< orphan*/ *) ; 
 struct tegra_devfreq* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_devfreq_governor ; 

__attribute__((used)) static int tegra_devfreq_remove(struct platform_device *pdev)
{
	struct tegra_devfreq *tegra = platform_get_drvdata(pdev);

	devfreq_remove_device(tegra->devfreq);
	devfreq_remove_governor(&tegra_devfreq_governor);

	clk_notifier_unregister(tegra->emc_clock, &tegra->rate_change_nb);
	dev_pm_opp_remove_all_dynamic(&pdev->dev);

	reset_control_reset(tegra->reset);
	clk_disable_unprepare(tegra->clock);

	return 0;
}