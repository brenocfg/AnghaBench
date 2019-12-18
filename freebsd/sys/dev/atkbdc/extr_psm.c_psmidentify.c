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
typedef  scalar_t__ u_long ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ driver_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KBDC_RID_AUX ; 
 int /*<<< orphan*/  PSMCPNP_DRIVER_NAME ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_get_resource_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 int device_get_unit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
psmidentify(driver_t *driver, device_t parent)
{
	device_t psmc;
	device_t psm;
	u_long irq;
	int unit;

	unit = device_get_unit(parent);

	/* always add at least one child */
	psm = BUS_ADD_CHILD(parent, KBDC_RID_AUX, driver->name, unit);
	if (psm == NULL)
		return;

	irq = bus_get_resource_start(psm, SYS_RES_IRQ, KBDC_RID_AUX);
	if (irq > 0)
		return;

	/*
	 * If the PS/2 mouse device has already been reported by ACPI or
	 * PnP BIOS, obtain the IRQ resource from it.
	 * (See psmcpnp_attach() below.)
	 */
	psmc = device_find_child(device_get_parent(parent),
	    PSMCPNP_DRIVER_NAME, unit);
	if (psmc == NULL)
		return;
	irq = bus_get_resource_start(psmc, SYS_RES_IRQ, 0);
	if (irq <= 0)
		return;
	bus_delete_resource(psmc, SYS_RES_IRQ, 0);
	bus_set_resource(psm, SYS_RES_IRQ, KBDC_RID_AUX, irq, 1);
}