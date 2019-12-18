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
struct device {int dummy; } ;
struct devfreq {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int devfreq_register_opp_notifier (struct device*,struct devfreq*) ; 
 int /*<<< orphan*/  devm_devfreq_opp_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct devfreq**) ; 
 struct devfreq** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct devfreq**) ; 

int devm_devfreq_register_opp_notifier(struct device *dev,
				       struct devfreq *devfreq)
{
	struct devfreq **ptr;
	int ret;

	ptr = devres_alloc(devm_devfreq_opp_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	ret = devfreq_register_opp_notifier(dev, devfreq);
	if (ret) {
		devres_free(ptr);
		return ret;
	}

	*ptr = devfreq;
	devres_add(dev, ptr);

	return 0;
}