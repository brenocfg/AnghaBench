#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device_method {void* func; int /*<<< orphan*/  desc; } ;
typedef  TYPE_3__* device_t ;
struct TYPE_7__ {TYPE_2__* dev_module; } ;
struct TYPE_6__ {TYPE_1__* driver; } ;
struct TYPE_5__ {struct device_method* methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  default_method ; 
 scalar_t__ devclass_equal (int /*<<< orphan*/ ,char const*) ; 

void   *
device_get_method(device_t dev, const char *what)
{
	const struct device_method *mtod;

	mtod = dev->dev_module->driver->methods;
	while (mtod->func != NULL) {
		if (devclass_equal(mtod->desc, what)) {
			return (mtod->func);
		}
		mtod++;
	}
	return ((void *)&default_method);
}