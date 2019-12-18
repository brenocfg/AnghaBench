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
struct device {scalar_t__ pm_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 struct device* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct device* genpd_dev_pm_attach_by_name (struct device*,char const*) ; 

struct device *dev_pm_domain_attach_by_name(struct device *dev,
					    const char *name)
{
	if (dev->pm_domain)
		return ERR_PTR(-EEXIST);

	return genpd_dev_pm_attach_by_name(dev, name);
}