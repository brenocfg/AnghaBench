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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_domain () ; 
 int /*<<< orphan*/  xentimer_devclass ; 

__attribute__((used)) static void
xentimer_identify(driver_t *driver, device_t parent)
{
	if (!xen_domain())
		return;

	/* Handle all Xen PV timers in one device instance. */
	if (devclass_get_device(xentimer_devclass, 0))
		return;

	BUS_ADD_CHILD(parent, 0, "xen_et", 0);
}