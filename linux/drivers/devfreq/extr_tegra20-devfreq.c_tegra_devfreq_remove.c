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
struct tegra_devfreq {int /*<<< orphan*/  devfreq; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_pm_opp_remove_all_dynamic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devfreq_remove_device (int /*<<< orphan*/ ) ; 
 struct tegra_devfreq* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tegra_devfreq_remove(struct platform_device *pdev)
{
	struct tegra_devfreq *tegra = platform_get_drvdata(pdev);

	devfreq_remove_device(tegra->devfreq);
	dev_pm_opp_remove_all_dynamic(&pdev->dev);

	return 0;
}