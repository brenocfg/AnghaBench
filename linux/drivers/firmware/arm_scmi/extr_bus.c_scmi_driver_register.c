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
struct TYPE_2__ {char const* mod_name; struct module* owner; int /*<<< orphan*/  name; int /*<<< orphan*/ * bus; } ;
struct scmi_driver {int /*<<< orphan*/  name; TYPE_1__ driver; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmi_bus_type ; 

int scmi_driver_register(struct scmi_driver *driver, struct module *owner,
			 const char *mod_name)
{
	int retval;

	driver->driver.bus = &scmi_bus_type;
	driver->driver.name = driver->name;
	driver->driver.owner = owner;
	driver->driver.mod_name = mod_name;

	retval = driver_register(&driver->driver);
	if (!retval)
		pr_debug("registered new scmi driver %s\n", driver->name);

	return retval;
}