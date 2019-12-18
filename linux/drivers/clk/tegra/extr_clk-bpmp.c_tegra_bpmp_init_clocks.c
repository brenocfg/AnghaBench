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
struct tegra_bpmp_clk_info {int dummy; } ;
struct tegra_bpmp {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct tegra_bpmp_clk_info*) ; 
 int of_clk_add_hw_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_bpmp*) ; 
 int /*<<< orphan*/  tegra_bpmp_clk_of_xlate ; 
 int tegra_bpmp_probe_clocks (struct tegra_bpmp*,struct tegra_bpmp_clk_info**) ; 
 int tegra_bpmp_register_clocks (struct tegra_bpmp*,struct tegra_bpmp_clk_info*,unsigned int) ; 
 int /*<<< orphan*/  tegra_bpmp_unregister_clocks (struct tegra_bpmp*) ; 

int tegra_bpmp_init_clocks(struct tegra_bpmp *bpmp)
{
	struct tegra_bpmp_clk_info *clocks;
	unsigned int count;
	int err;

	err = tegra_bpmp_probe_clocks(bpmp, &clocks);
	if (err < 0)
		return err;

	count = err;

	dev_dbg(bpmp->dev, "%u clocks probed\n", count);

	err = tegra_bpmp_register_clocks(bpmp, clocks, count);
	if (err < 0)
		goto free;

	err = of_clk_add_hw_provider(bpmp->dev->of_node,
				     tegra_bpmp_clk_of_xlate,
				     bpmp);
	if (err < 0) {
		tegra_bpmp_unregister_clocks(bpmp);
		goto free;
	}

free:
	kfree(clocks);
	return err;
}