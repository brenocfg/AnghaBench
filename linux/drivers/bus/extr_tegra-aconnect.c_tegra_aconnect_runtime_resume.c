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
struct tegra_aconnect {int /*<<< orphan*/  ape_clk; int /*<<< orphan*/  apb2ape_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct tegra_aconnect* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int tegra_aconnect_runtime_resume(struct device *dev)
{
	struct tegra_aconnect *aconnect = dev_get_drvdata(dev);
	int ret;

	ret = clk_prepare_enable(aconnect->ape_clk);
	if (ret) {
		dev_err(dev, "ape clk_enable failed: %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(aconnect->apb2ape_clk);
	if (ret) {
		clk_disable_unprepare(aconnect->ape_clk);
		dev_err(dev, "apb2ape clk_enable failed: %d\n", ret);
		return ret;
	}

	return 0;
}