#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ GLXIIC_CS5536_DEV_ID ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
glxiic_identify(driver_t *driver, device_t parent)
{

	/* Prevent child from being added more than once. */
	if (device_find_child(parent, driver->name, -1) != NULL)
		return;

	if (pci_get_devid(parent) == GLXIIC_CS5536_DEV_ID) {
		if (device_add_child(parent, driver->name, -1) == NULL)
			device_printf(parent, "Could not add glxiic child\n");
	}
}