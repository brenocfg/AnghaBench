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
struct TYPE_2__ {int /*<<< orphan*/ * bus; scalar_t__ owner; scalar_t__ name; } ;
struct gio_driver {TYPE_1__ driver; scalar_t__ owner; scalar_t__ name; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  gio_bus_type ; 

int gio_register_driver(struct gio_driver *drv)
{
	/* initialize common driver fields */
	if (!drv->driver.name)
		drv->driver.name = drv->name;
	if (!drv->driver.owner)
		drv->driver.owner = drv->owner;
	drv->driver.bus = &gio_bus_type;

	/* register with core */
	return driver_register(&drv->driver);
}