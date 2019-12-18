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
struct gpiobus_softc {int dummy; } ;
struct gpiobus_ivar {int /*<<< orphan*/  rl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 struct gpiobus_ivar* GPIOBUS_IVAR (int /*<<< orphan*/ ) ; 
 struct gpiobus_softc* GPIOBUS_SOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct gpiobus_ivar*,int /*<<< orphan*/ ) ; 
 scalar_t__ gpiobus_parse_pin_list (struct gpiobus_softc*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ gpiobus_parse_pins (struct gpiobus_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ resource_int_value (char const*,int,char*,int*) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 scalar_t__ resource_string_value (char const*,int,char*,char const**) ; 

__attribute__((used)) static void
gpiobus_hinted_child(device_t bus, const char *dname, int dunit)
{
	struct gpiobus_softc *sc = GPIOBUS_SOFTC(bus);
	struct gpiobus_ivar *devi;
	device_t child;
	const char *pins;
	int irq, pinmask;

	child = BUS_ADD_CHILD(bus, 0, dname, dunit);
	devi = GPIOBUS_IVAR(child);
	if (resource_int_value(dname, dunit, "pins", &pinmask) == 0) {
		if (gpiobus_parse_pins(sc, child, pinmask)) {
			resource_list_free(&devi->rl);
			free(devi, M_DEVBUF);
			device_delete_child(bus, child);
			return;
		}
	}
	else if (resource_string_value(dname, dunit, "pin_list", &pins) == 0) {
		if (gpiobus_parse_pin_list(sc, child, pins)) {
			resource_list_free(&devi->rl);
			free(devi, M_DEVBUF);
			device_delete_child(bus, child);
			return;
		}
	}
	if (resource_int_value(dname, dunit, "irq", &irq) == 0) {
		if (bus_set_resource(child, SYS_RES_IRQ, 0, irq, 1) != 0)
			device_printf(bus,
			    "warning: bus_set_resource() failed\n");
	}
}