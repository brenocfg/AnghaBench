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
struct tegra_devfreq_device {int target_freq; int avg_count; TYPE_1__* config; scalar_t__ boost_freq; } ;
struct tegra_devfreq {int dummy; } ;
struct TYPE_2__ {int avg_dependency_threshold; int boost_up_threshold; } ;

/* Variables and functions */
 int ACTMON_SAMPLING_PERIOD ; 
 unsigned long actmon_cpu_to_emc_rate (struct tegra_devfreq*,unsigned long) ; 
 unsigned long cpufreq_get (int /*<<< orphan*/ ) ; 
 int do_percent (int,unsigned int) ; 
 int max (int,unsigned long) ; 

__attribute__((used)) static void actmon_update_target(struct tegra_devfreq *tegra,
				 struct tegra_devfreq_device *dev)
{
	unsigned long cpu_freq = 0;
	unsigned long static_cpu_emc_freq = 0;
	unsigned int avg_sustain_coef;

	if (dev->config->avg_dependency_threshold) {
		cpu_freq = cpufreq_get(0);
		static_cpu_emc_freq = actmon_cpu_to_emc_rate(tegra, cpu_freq);
	}

	dev->target_freq = dev->avg_count / ACTMON_SAMPLING_PERIOD;
	avg_sustain_coef = 100 * 100 / dev->config->boost_up_threshold;
	dev->target_freq = do_percent(dev->target_freq, avg_sustain_coef);
	dev->target_freq += dev->boost_freq;

	if (dev->avg_count >= dev->config->avg_dependency_threshold)
		dev->target_freq = max(dev->target_freq, static_cpu_emc_freq);
}