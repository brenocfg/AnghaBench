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
typedef  int u32 ;
struct tegra_devfreq_device {scalar_t__ avg_count; scalar_t__ boost_freq; TYPE_1__* config; } ;
struct tegra_devfreq {scalar_t__ max_freq; } ;
struct TYPE_2__ {scalar_t__ avg_dependency_threshold; int /*<<< orphan*/  boost_down_coeff; int /*<<< orphan*/  boost_up_coeff; } ;

/* Variables and functions */
 int ACTMON_BOOST_FREQ_STEP ; 
 int /*<<< orphan*/  ACTMON_DEV_AVG_COUNT ; 
 int /*<<< orphan*/  ACTMON_DEV_CTRL ; 
 int ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_EN ; 
 int ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_EN ; 
 int ACTMON_DEV_INTR_CONSECUTIVE_LOWER ; 
 int ACTMON_DEV_INTR_CONSECUTIVE_UPPER ; 
 int /*<<< orphan*/  ACTMON_DEV_INTR_STATUS ; 
 int ACTMON_INTR_STATUS_CLEAR ; 
 int /*<<< orphan*/  actmon_write_barrier (struct tegra_devfreq*) ; 
 void* device_readl (struct tegra_devfreq_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_writel (struct tegra_devfreq_device*,int,int /*<<< orphan*/ ) ; 
 void* do_percent (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_devfreq_update_avg_wmark (struct tegra_devfreq*,struct tegra_devfreq_device*) ; 

__attribute__((used)) static void actmon_isr_device(struct tegra_devfreq *tegra,
			      struct tegra_devfreq_device *dev)
{
	u32 intr_status, dev_ctrl;

	dev->avg_count = device_readl(dev, ACTMON_DEV_AVG_COUNT);
	tegra_devfreq_update_avg_wmark(tegra, dev);

	intr_status = device_readl(dev, ACTMON_DEV_INTR_STATUS);
	dev_ctrl = device_readl(dev, ACTMON_DEV_CTRL);

	if (intr_status & ACTMON_DEV_INTR_CONSECUTIVE_UPPER) {
		/*
		 * new_boost = min(old_boost * up_coef + step, max_freq)
		 */
		dev->boost_freq = do_percent(dev->boost_freq,
					     dev->config->boost_up_coeff);
		dev->boost_freq += ACTMON_BOOST_FREQ_STEP;

		dev_ctrl |= ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_EN;

		if (dev->boost_freq >= tegra->max_freq)
			dev->boost_freq = tegra->max_freq;
		else
			dev_ctrl |= ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_EN;
	} else if (intr_status & ACTMON_DEV_INTR_CONSECUTIVE_LOWER) {
		/*
		 * new_boost = old_boost * down_coef
		 * or 0 if (old_boost * down_coef < step / 2)
		 */
		dev->boost_freq = do_percent(dev->boost_freq,
					     dev->config->boost_down_coeff);

		dev_ctrl |= ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_EN;

		if (dev->boost_freq < (ACTMON_BOOST_FREQ_STEP >> 1))
			dev->boost_freq = 0;
		else
			dev_ctrl |= ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_EN;
	}

	if (dev->config->avg_dependency_threshold) {
		if (dev->avg_count >= dev->config->avg_dependency_threshold)
			dev_ctrl |= ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_EN;
		else if (dev->boost_freq == 0)
			dev_ctrl &= ~ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_EN;
	}

	device_writel(dev, dev_ctrl, ACTMON_DEV_CTRL);

	device_writel(dev, ACTMON_INTR_STATUS_CLEAR, ACTMON_DEV_INTR_STATUS);

	actmon_write_barrier(tegra);
}