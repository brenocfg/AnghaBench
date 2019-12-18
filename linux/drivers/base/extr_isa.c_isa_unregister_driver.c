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
struct isa_driver {int /*<<< orphan*/  driver; struct device* devices; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_isa_dev (struct device*) ; 

void isa_unregister_driver(struct isa_driver *isa_driver)
{
	struct device *dev = isa_driver->devices;

	while (dev) {
		struct device *tmp = to_isa_dev(dev)->next;
		device_unregister(dev);
		dev = tmp;
	}
	driver_unregister(&isa_driver->driver);
}