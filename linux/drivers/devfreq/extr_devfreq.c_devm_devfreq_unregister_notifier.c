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
struct notifier_block {int dummy; } ;
struct device {int dummy; } ;
struct devfreq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_devfreq_dev_match ; 
 int /*<<< orphan*/  devm_devfreq_notifier_release ; 
 int /*<<< orphan*/  devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct devfreq*) ; 

void devm_devfreq_unregister_notifier(struct device *dev,
				      struct devfreq *devfreq,
				      struct notifier_block *nb,
				      unsigned int list)
{
	WARN_ON(devres_release(dev, devm_devfreq_notifier_release,
			       devm_devfreq_dev_match, devfreq));
}