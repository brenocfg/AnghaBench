#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev_children; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_link ; 
 int /*<<< orphan*/  device_printf (TYPE_1__*,char*,...) ; 
 TYPE_1__* make_device (TYPE_1__*,char const*) ; 

device_t
device_add_child(device_t dev, const char *name, int unit)
{
	device_t child;

	if (unit != -1) {
		device_printf(dev, "Unit is not -1\n");
	}
	child = make_device(dev, name);
	if (child == NULL) {
		device_printf(dev, "Could not add child '%s'\n", name);
		goto done;
	}
	if (dev == NULL) {
		/* no parent */
		goto done;
	}
	TAILQ_INSERT_TAIL(&dev->dev_children, child, dev_link);
done:
	return (child);
}