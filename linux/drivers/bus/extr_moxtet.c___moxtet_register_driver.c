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
struct TYPE_2__ {int /*<<< orphan*/ * bus; struct module* owner; } ;
struct moxtet_driver {TYPE_1__ driver; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  moxtet_bus_type ; 

int __moxtet_register_driver(struct module *owner,
			     struct moxtet_driver *mdrv)
{
	mdrv->driver.owner = owner;
	mdrv->driver.bus = &moxtet_bus_type;
	return driver_register(&mdrv->driver);
}