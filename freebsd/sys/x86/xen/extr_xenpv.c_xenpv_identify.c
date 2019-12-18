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
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 scalar_t__ devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  xen_domain () ; 
 int /*<<< orphan*/  xenpv_devclass ; 

__attribute__((used)) static void
xenpv_identify(driver_t *driver, device_t parent)
{
	if (!xen_domain())
		return;

	/* Make sure there's only one xenpv device. */
	if (devclass_get_device(xenpv_devclass, 0))
		return;

	/*
	 * The xenpv bus should be the last to attach in order
	 * to properly detect if an ISA bus has already been added.
	 */
	if (BUS_ADD_CHILD(parent, UINT_MAX, "xenpv", 0) == NULL)
		panic("Unable to attach xenpv bus.");
}