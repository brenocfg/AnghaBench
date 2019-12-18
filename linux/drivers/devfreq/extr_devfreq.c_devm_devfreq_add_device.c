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
struct devfreq_dev_profile {int dummy; } ;
struct devfreq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct devfreq* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct devfreq*) ; 
 struct devfreq* devfreq_add_device (struct device*,struct devfreq_dev_profile*,char const*,void*) ; 
 int /*<<< orphan*/  devm_devfreq_dev_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct devfreq**) ; 
 struct devfreq** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct devfreq**) ; 

struct devfreq *devm_devfreq_add_device(struct device *dev,
					struct devfreq_dev_profile *profile,
					const char *governor_name,
					void *data)
{
	struct devfreq **ptr, *devfreq;

	ptr = devres_alloc(devm_devfreq_dev_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	devfreq = devfreq_add_device(dev, profile, governor_name, data);
	if (IS_ERR(devfreq)) {
		devres_free(ptr);
		return devfreq;
	}

	*ptr = devfreq;
	devres_add(dev, ptr);

	return devfreq;
}