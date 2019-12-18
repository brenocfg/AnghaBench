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
typedef  int /*<<< orphan*/  u32 ;
struct exynos_bus {unsigned long curr_freq; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
struct dev_pm_opp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 int PTR_ERR (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct exynos_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 
 int dev_pm_opp_set_rate (struct device*,unsigned long) ; 
 struct dev_pm_opp* devfreq_recommended_opp (struct device*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exynos_bus_target(struct device *dev, unsigned long *freq, u32 flags)
{
	struct exynos_bus *bus = dev_get_drvdata(dev);
	struct dev_pm_opp *new_opp;
	int ret = 0;

	/* Get correct frequency for bus. */
	new_opp = devfreq_recommended_opp(dev, freq, flags);
	if (IS_ERR(new_opp)) {
		dev_err(dev, "failed to get recommended opp instance\n");
		return PTR_ERR(new_opp);
	}

	dev_pm_opp_put(new_opp);

	/* Change voltage and frequency according to new OPP level */
	mutex_lock(&bus->lock);
	ret = dev_pm_opp_set_rate(dev, *freq);
	if (!ret)
		bus->curr_freq = *freq;

	mutex_unlock(&bus->lock);

	return ret;
}