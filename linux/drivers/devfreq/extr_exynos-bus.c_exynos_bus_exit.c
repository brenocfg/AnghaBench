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
struct exynos_bus {int /*<<< orphan*/ * opp_table; int /*<<< orphan*/  clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct exynos_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_of_remove_table (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_put_regulators (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int exynos_bus_disable_edev (struct exynos_bus*) ; 

__attribute__((used)) static void exynos_bus_exit(struct device *dev)
{
	struct exynos_bus *bus = dev_get_drvdata(dev);
	int ret;

	ret = exynos_bus_disable_edev(bus);
	if (ret < 0)
		dev_warn(dev, "failed to disable the devfreq-event devices\n");

	dev_pm_opp_of_remove_table(dev);
	clk_disable_unprepare(bus->clk);
	if (bus->opp_table) {
		dev_pm_opp_put_regulators(bus->opp_table);
		bus->opp_table = NULL;
	}
}