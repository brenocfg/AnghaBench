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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ KBD_STATUS_PORT ; 
 scalar_t__ OF_finddevice (char*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int atkbdc_probe_unit (int /*<<< orphan*/ ,struct resource*,struct resource*) ; 
 struct resource* bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  device_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparc64_model ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
atkbdc_ebus_probe(device_t dev)
{
	struct resource *port0, *port1;
	rman_res_t count, start;
	int error, rid;

	if (strcmp(ofw_bus_get_name(dev), "8042") != 0)
		return (ENXIO);

	/*
	 * On AXi and AXmp boards the NS16550 (used to connect keyboard/
	 * mouse) share their IRQ lines with the i8042. Any IRQ activity
	 * (typically during attach) of the NS16550 used to connect the
	 * keyboard when actually the PS/2 keyboard is selected in OFW
	 * causes interaction with the OBP i8042 driver resulting in a
	 * hang and vice versa. As RS232 keyboards and mice obviously
	 * aren't meant to be used in parallel with PS/2 ones on these
	 * boards don't attach to the i8042 in case the PS/2 keyboard
	 * isn't selected in order to prevent such hangs.
	 * Note that it's not sufficient here to rely on the '8042' node
	 * only showing up when a PS/2 keyboard is actually connected as
	 * the user still might have adjusted the 'keyboard' alias to
	 * point to the RS232 keyboard.
	 */
	if ((!strcmp(sparc64_model, "SUNW,UltraAX-MP") ||
	    !strcmp(sparc64_model, "SUNW,UltraSPARC-IIi-Engine")) &&
	    OF_finddevice("keyboard") != ofw_bus_get_node(dev)) {
		device_disable(dev);
		return (ENXIO);
	}

	device_set_desc(dev, "Keyboard controller (i8042)");

	/*
	 * The '8042' node has two identical 8 addresses wide resources
	 * which are apparently meant to be used one for the keyboard
	 * half and the other one for the mouse half. To simplify matters
	 * we use one for the command/data port resource and the other
	 * one for the status port resource as the atkbdc(4) back-end
	 * expects two struct resource rather than two bus space handles.
	 */
	rid = 0;
	if (bus_get_resource(dev, SYS_RES_MEMORY, rid, &start, &count) != 0) {
		device_printf(dev,
		    "cannot determine command/data port resource\n");
		return (ENXIO);
	}
	port0 = bus_alloc_resource(dev, SYS_RES_MEMORY, &rid, start, start, 1,
	    RF_ACTIVE);
	if (port0 == NULL) {
		device_printf(dev,
		    "cannot allocate command/data port resource\n");
		return (ENXIO);
	}

	rid = 1;
	if (bus_get_resource(dev, SYS_RES_MEMORY, rid, &start, &count) != 0) {
		device_printf(dev, "cannot determine status port resource\n");
		error = ENXIO;
		goto fail_port0;
	}
	start += KBD_STATUS_PORT;
	port1 = bus_alloc_resource(dev, SYS_RES_MEMORY, &rid, start, start, 1,
	    RF_ACTIVE);
	if (port1 == NULL) {
		device_printf(dev, "cannot allocate status port resource\n");
		error = ENXIO;
		goto fail_port0;
	}

	error = atkbdc_probe_unit(device_get_unit(dev), port0, port1);
	if (error != 0)
		device_printf(dev, "atkbdc_porbe_unit failed\n");

	bus_release_resource(dev, SYS_RES_MEMORY, 1, port1);
 fail_port0:
	bus_release_resource(dev, SYS_RES_MEMORY, 0, port0);

	return (error);
}