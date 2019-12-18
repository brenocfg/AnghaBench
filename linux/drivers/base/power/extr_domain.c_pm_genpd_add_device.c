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
struct generic_pm_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int genpd_add_device (struct generic_pm_domain*,struct device*,struct device*) ; 
 int /*<<< orphan*/  gpd_list_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int pm_genpd_add_device(struct generic_pm_domain *genpd, struct device *dev)
{
	int ret;

	mutex_lock(&gpd_list_lock);
	ret = genpd_add_device(genpd, dev, dev);
	mutex_unlock(&gpd_list_lock);

	return ret;
}