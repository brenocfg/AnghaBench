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
struct tegra_mc {scalar_t__ regs; } ;
struct tegra_devfreq {struct tegra_mc* devfreq; scalar_t__ regs; struct tegra_mc* emc_clock; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFREQ_GOV_SIMPLE_ONDEMAND ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct tegra_mc*) ; 
 scalar_t__ MC_STAT_CONTROL ; 
 scalar_t__ MC_STAT_EMC_CLOCK_LIMIT ; 
 scalar_t__ MC_STAT_EMC_CONTROL ; 
 int PTR_ERR (struct tegra_mc*) ; 
 unsigned long ULONG_MAX ; 
 unsigned long clk_round_rate (struct tegra_mc*,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int dev_pm_opp_add (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_opp_remove_all_dynamic (int /*<<< orphan*/ *) ; 
 struct tegra_mc* devfreq_add_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tegra_mc* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct tegra_devfreq* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_devfreq*) ; 
 int /*<<< orphan*/  tegra_devfreq_profile ; 
 struct tegra_mc* tegra_get_memory_controller () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int tegra_devfreq_probe(struct platform_device *pdev)
{
	struct tegra_devfreq *tegra;
	struct tegra_mc *mc;
	unsigned long max_rate;
	unsigned long rate;
	int err;

	mc = tegra_get_memory_controller();
	if (IS_ERR(mc)) {
		err = PTR_ERR(mc);
		dev_err(&pdev->dev, "failed to get memory controller: %d\n",
			err);
		return err;
	}

	tegra = devm_kzalloc(&pdev->dev, sizeof(*tegra), GFP_KERNEL);
	if (!tegra)
		return -ENOMEM;

	/* EMC is a system-critical clock that is always enabled */
	tegra->emc_clock = devm_clk_get(&pdev->dev, "emc");
	if (IS_ERR(tegra->emc_clock)) {
		err = PTR_ERR(tegra->emc_clock);
		dev_err(&pdev->dev, "failed to get emc clock: %d\n", err);
		return err;
	}

	tegra->regs = mc->regs;

	max_rate = clk_round_rate(tegra->emc_clock, ULONG_MAX);

	for (rate = 0; rate <= max_rate; rate++) {
		rate = clk_round_rate(tegra->emc_clock, rate);

		err = dev_pm_opp_add(&pdev->dev, rate, 0);
		if (err) {
			dev_err(&pdev->dev, "failed to add opp: %d\n", err);
			goto remove_opps;
		}
	}

	/*
	 * Reset statistic gathers state, select global bandwidth for the
	 * statistics collection mode and set clocks counter saturation
	 * limit to maximum.
	 */
	writel_relaxed(0x00000000, tegra->regs + MC_STAT_CONTROL);
	writel_relaxed(0x00000000, tegra->regs + MC_STAT_EMC_CONTROL);
	writel_relaxed(0xffffffff, tegra->regs + MC_STAT_EMC_CLOCK_LIMIT);

	platform_set_drvdata(pdev, tegra);

	tegra->devfreq = devfreq_add_device(&pdev->dev, &tegra_devfreq_profile,
					    DEVFREQ_GOV_SIMPLE_ONDEMAND, NULL);
	if (IS_ERR(tegra->devfreq)) {
		err = PTR_ERR(tegra->devfreq);
		goto remove_opps;
	}

	return 0;

remove_opps:
	dev_pm_opp_remove_all_dynamic(&pdev->dev);

	return err;
}