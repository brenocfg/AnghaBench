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
struct TYPE_2__ {scalar_t__ rclk; scalar_t__ regshft; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; scalar_t__ chan; } ;
struct uart_devinfo {unsigned int baudrate; int databits; int stopbits; int /*<<< orphan*/  parity; TYPE_1__ bas; int /*<<< orphan*/  ops; } ;
struct uart_class {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int UART_DEV_CONSOLE ; 
 int UART_DEV_DBGPORT ; 
 int /*<<< orphan*/  UART_FLAGS_CONSOLE (unsigned int) ; 
 int /*<<< orphan*/  UART_FLAGS_DBGPORT (unsigned int) ; 
 int /*<<< orphan*/  UART_PARITY_NONE ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ resource_int_value (char*,unsigned int,char*,unsigned int*) ; 
 int /*<<< orphan*/  uart_bus_space_io ; 
 scalar_t__ uart_cpu_acpi_spcr (int,struct uart_devinfo*) ; 
 scalar_t__ uart_getenv (int,struct uart_devinfo*,struct uart_class*) ; 
 int /*<<< orphan*/  uart_getops (struct uart_class*) ; 
 int /*<<< orphan*/  uart_getrange (struct uart_class*) ; 
 struct uart_class uart_ns8250_class ; 

int
uart_cpu_getdev(int devtype, struct uart_devinfo *di)
{
	struct uart_class *class;
	unsigned int i, ivar;

	class = &uart_ns8250_class;
	if (class == NULL)
		return (ENXIO);

	/* Check the environment. */
	if (uart_getenv(devtype, di, class) == 0)
		return (0);

#ifdef DEV_ACPI
	/* Check if SPCR can tell us what console to use. */
	if (uart_cpu_acpi_spcr(devtype, di) == 0)
		return (0);
#endif

	/*
	 * Scan the hints. We only try units 0 to 3 (inclusive). This
	 * covers the ISA legacy where 4 UARTs had their resources
	 * predefined.
	 */
	for (i = 0; i < 4; i++) {
		if (resource_int_value("uart", i, "flags", &ivar))
			continue;
		if (devtype == UART_DEV_CONSOLE && !UART_FLAGS_CONSOLE(ivar))
			continue;
		if (devtype == UART_DEV_DBGPORT && !UART_FLAGS_DBGPORT(ivar))
			continue;
		/*
		 * We have a possible device. Make sure it's enabled and
		 * that we have an I/O port.
		 */
		if (resource_int_value("uart", i, "disabled", &ivar) == 0 &&
		    ivar != 0)
			continue;
		if (resource_int_value("uart", i, "port", &ivar) != 0 ||
		    ivar == 0)
			continue;
		/*
		 * Got it. Fill in the instance and return it. We only have
		 * ns8250 and successors on i386.
		 */
		di->ops = uart_getops(class);
		di->bas.chan = 0;
		di->bas.bst = uart_bus_space_io;
		if (bus_space_map(di->bas.bst, ivar, uart_getrange(class), 0,
		    &di->bas.bsh) != 0)
			continue;
		di->bas.regshft = 0;
		di->bas.rclk = 0;
		if (resource_int_value("uart", i, "baud", &ivar) != 0)
			ivar = 0;
		di->baudrate = ivar;
		di->databits = 8;
		di->stopbits = 1;
		di->parity = UART_PARITY_NONE;
		return (0);
	}

	return (ENXIO);
}