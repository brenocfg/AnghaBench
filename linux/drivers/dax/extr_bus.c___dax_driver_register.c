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
struct module {int dummy; } ;
struct device_driver {char const* name; char const* mod_name; int /*<<< orphan*/ * bus; struct module* owner; } ;
struct dax_device_driver {scalar_t__ match_always; int /*<<< orphan*/  ids; struct device_driver drv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dax_bus_lock ; 
 int /*<<< orphan*/  dax_bus_type ; 
 int driver_register (struct device_driver*) ; 
 int match_always_count ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int __dax_driver_register(struct dax_device_driver *dax_drv,
		struct module *module, const char *mod_name)
{
	struct device_driver *drv = &dax_drv->drv;
	int rc = 0;

	INIT_LIST_HEAD(&dax_drv->ids);
	drv->owner = module;
	drv->name = mod_name;
	drv->mod_name = mod_name;
	drv->bus = &dax_bus_type;

	/* there can only be one default driver */
	mutex_lock(&dax_bus_lock);
	match_always_count += dax_drv->match_always;
	if (match_always_count > 1) {
		match_always_count--;
		WARN_ON(1);
		rc = -EINVAL;
	}
	mutex_unlock(&dax_bus_lock);
	if (rc)
		return rc;
	return driver_register(drv);
}