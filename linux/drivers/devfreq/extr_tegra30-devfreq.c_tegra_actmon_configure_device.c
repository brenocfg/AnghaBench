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
typedef  int u32 ;
struct tegra_devfreq_device {int target_freq; int avg_count; } ;
struct tegra_devfreq {int cur_freq; } ;

/* Variables and functions */
 int ACTMON_ABOVE_WMARK_WINDOW ; 
 int ACTMON_AVERAGE_WINDOW_LOG2 ; 
 int ACTMON_BELOW_WMARK_WINDOW ; 
 int ACTMON_COUNT_WEIGHT ; 
 int /*<<< orphan*/  ACTMON_DEV_COUNT_WEIGHT ; 
 int /*<<< orphan*/  ACTMON_DEV_CTRL ; 
 int ACTMON_DEV_CTRL_AVG_ABOVE_WMARK_EN ; 
 int ACTMON_DEV_CTRL_AVG_BELOW_WMARK_EN ; 
 int ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_EN ; 
 int ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_NUM_SHIFT ; 
 int ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_EN ; 
 int ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_NUM_SHIFT ; 
 int ACTMON_DEV_CTRL_ENB ; 
 int ACTMON_DEV_CTRL_ENB_PERIODIC ; 
 int ACTMON_DEV_CTRL_K_VAL_SHIFT ; 
 int /*<<< orphan*/  ACTMON_DEV_INIT_AVG ; 
 int /*<<< orphan*/  ACTMON_DEV_INTR_STATUS ; 
 int ACTMON_INTR_STATUS_CLEAR ; 
 int ACTMON_SAMPLING_PERIOD ; 
 int /*<<< orphan*/  device_writel (struct tegra_devfreq_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_devfreq_update_avg_wmark (struct tegra_devfreq*,struct tegra_devfreq_device*) ; 
 int /*<<< orphan*/  tegra_devfreq_update_wmark (struct tegra_devfreq*,struct tegra_devfreq_device*) ; 

__attribute__((used)) static void tegra_actmon_configure_device(struct tegra_devfreq *tegra,
					  struct tegra_devfreq_device *dev)
{
	u32 val = 0;

	dev->target_freq = tegra->cur_freq;

	dev->avg_count = tegra->cur_freq * ACTMON_SAMPLING_PERIOD;
	device_writel(dev, dev->avg_count, ACTMON_DEV_INIT_AVG);

	tegra_devfreq_update_avg_wmark(tegra, dev);
	tegra_devfreq_update_wmark(tegra, dev);

	device_writel(dev, ACTMON_COUNT_WEIGHT, ACTMON_DEV_COUNT_WEIGHT);
	device_writel(dev, ACTMON_INTR_STATUS_CLEAR, ACTMON_DEV_INTR_STATUS);

	val |= ACTMON_DEV_CTRL_ENB_PERIODIC;
	val |= (ACTMON_AVERAGE_WINDOW_LOG2 - 1)
		<< ACTMON_DEV_CTRL_K_VAL_SHIFT;
	val |= (ACTMON_BELOW_WMARK_WINDOW - 1)
		<< ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_NUM_SHIFT;
	val |= (ACTMON_ABOVE_WMARK_WINDOW - 1)
		<< ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_NUM_SHIFT;
	val |= ACTMON_DEV_CTRL_AVG_ABOVE_WMARK_EN;
	val |= ACTMON_DEV_CTRL_AVG_BELOW_WMARK_EN;
	val |= ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_EN;
	val |= ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_EN;
	val |= ACTMON_DEV_CTRL_ENB;

	device_writel(dev, val, ACTMON_DEV_CTRL);
}