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
struct TYPE_2__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/  name; } ;
struct dio_driver {TYPE_1__ driver; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dio_bus_type ; 
 int driver_register (TYPE_1__*) ; 

int dio_register_driver(struct dio_driver *drv)
{
	/* initialize common driver fields */
	drv->driver.name = drv->name;
	drv->driver.bus = &dio_bus_type;

	/* register with core */
	return driver_register(&drv->driver);
}