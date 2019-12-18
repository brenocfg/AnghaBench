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
struct uart_softc {int /*<<< orphan*/ * sc_class; } ;
struct uart_devinfo {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  UART_DEV_KEYBOARD ; 
 int /*<<< orphan*/  device_disable (int /*<<< orphan*/ ) ; 
 struct uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 char const* sparc64_model ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int uart_bus_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_cpu_getdev (int /*<<< orphan*/ ,struct uart_devinfo*) ; 
 int /*<<< orphan*/  uart_ns8250_class ; 

__attribute__((used)) static int
uart_ebus_probe(device_t dev)
{
	const char *nm, *cmpt;
	struct uart_softc *sc;
	struct uart_devinfo dummy;

	sc = device_get_softc(dev);
	sc->sc_class = NULL;

	nm = ofw_bus_get_name(dev);
	cmpt = ofw_bus_get_compat(dev);
	if (cmpt == NULL)
		cmpt = "";
	if (!strcmp(nm, "lom-console") || !strcmp(nm, "su") ||
	    !strcmp(nm, "su_pnp") || !strcmp(cmpt, "rsc-console") ||
	    !strcmp(cmpt, "rsc-control") || !strcmp(cmpt, "su") ||
	    !strcmp(cmpt, "su16550") || !strcmp(cmpt, "su16552")) {
		/*
		 * On AXi and AXmp boards the NS16550 (used to connect
		 * keyboard/mouse) share their IRQ lines with the i8042.
		 * Any IRQ activity (typically during attach) of the
		 * NS16550 used to connect the keyboard when actually the
		 * PS/2 keyboard is selected in OFW causes interaction
		 * with the OBP i8042 driver resulting in a hang and vice
		 * versa. As RS232 keyboards and mice obviously aren't
		 * meant to be used in parallel with PS/2 ones on these
		 * boards don't attach to the NS16550 in case the RS232
		 * keyboard isn't selected in order to prevent such hangs.
		 */
		if ((!strcmp(sparc64_model, "SUNW,UltraAX-MP") ||
		    !strcmp(sparc64_model, "SUNW,UltraSPARC-IIi-Engine")) &&
		    uart_cpu_getdev(UART_DEV_KEYBOARD, &dummy)) {
				device_disable(dev);
				return (ENXIO);
		}
		sc->sc_class = &uart_ns8250_class;
		return (uart_bus_probe(dev, 0, 0, 0, 0, 0, 0));
	}

	return (ENXIO);
}