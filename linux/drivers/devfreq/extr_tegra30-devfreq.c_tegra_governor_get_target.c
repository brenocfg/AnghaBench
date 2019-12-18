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
struct tegra_devfreq_device {int /*<<< orphan*/  target_freq; } ;
struct tegra_devfreq {struct tegra_devfreq_device* devices; } ;
struct devfreq_dev_status {struct tegra_devfreq* private_data; } ;
struct devfreq {struct devfreq_dev_status last_status; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct tegra_devfreq_device*) ; 
 unsigned long KHZ ; 
 int /*<<< orphan*/  actmon_update_target (struct tegra_devfreq*,struct tegra_devfreq_device*) ; 
 int devfreq_update_stats (struct devfreq*) ; 
 unsigned long max (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_governor_get_target(struct devfreq *devfreq,
				     unsigned long *freq)
{
	struct devfreq_dev_status *stat;
	struct tegra_devfreq *tegra;
	struct tegra_devfreq_device *dev;
	unsigned long target_freq = 0;
	unsigned int i;
	int err;

	err = devfreq_update_stats(devfreq);
	if (err)
		return err;

	stat = &devfreq->last_status;

	tegra = stat->private_data;

	for (i = 0; i < ARRAY_SIZE(tegra->devices); i++) {
		dev = &tegra->devices[i];

		actmon_update_target(tegra, dev);

		target_freq = max(target_freq, dev->target_freq);
	}

	*freq = target_freq * KHZ;

	return 0;
}