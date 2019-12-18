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
struct tegra_devfreq_device {TYPE_1__* config; } ;
struct tegra_devfreq {int cur_freq; } ;
struct TYPE_2__ {int /*<<< orphan*/  boost_down_threshold; int /*<<< orphan*/  boost_up_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTMON_DEV_LOWER_WMARK ; 
 int /*<<< orphan*/  ACTMON_DEV_UPPER_WMARK ; 
 int ACTMON_SAMPLING_PERIOD ; 
 int /*<<< orphan*/  device_writel (struct tegra_devfreq_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_percent (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_devfreq_update_wmark(struct tegra_devfreq *tegra,
				       struct tegra_devfreq_device *dev)
{
	u32 val = tegra->cur_freq * ACTMON_SAMPLING_PERIOD;

	device_writel(dev, do_percent(val, dev->config->boost_up_threshold),
		      ACTMON_DEV_UPPER_WMARK);

	device_writel(dev, do_percent(val, dev->config->boost_down_threshold),
		      ACTMON_DEV_LOWER_WMARK);
}