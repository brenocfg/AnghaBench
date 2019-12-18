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
struct kobject {int dummy; } ;
struct driver_private {struct device_driver* driver; } ;
struct device_driver {int dummy; } ;
struct bus_type {TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  drivers_kset; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 struct kobject* kset_find_obj (int /*<<< orphan*/ ,char const*) ; 
 struct driver_private* to_driver (struct kobject*) ; 

struct device_driver *driver_find(const char *name, struct bus_type *bus)
{
	struct kobject *k = kset_find_obj(bus->p->drivers_kset, name);
	struct driver_private *priv;

	if (k) {
		/* Drop reference added by kset_find_obj() */
		kobject_put(k);
		priv = to_driver(k);
		return priv->driver;
	}
	return NULL;
}