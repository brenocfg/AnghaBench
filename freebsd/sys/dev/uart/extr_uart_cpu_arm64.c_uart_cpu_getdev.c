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
typedef  void* u_int ;
struct TYPE_2__ {int /*<<< orphan*/  bst; int /*<<< orphan*/  bsh; void* rclk; void* regiowidth; void* regshft; scalar_t__ chan; } ;
struct uart_devinfo {int baudrate; int databits; int stopbits; TYPE_1__ bas; int /*<<< orphan*/  parity; int /*<<< orphan*/  ops; } ;
struct uart_class {int dummy; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int ENXIO ; 
 int UART_DEV_CONSOLE ; 
 int /*<<< orphan*/  UART_PARITY_NONE ; 
 int /*<<< orphan*/ * uart_bus_space_io ; 
 int /*<<< orphan*/  uart_bus_space_mem ; 
 scalar_t__ uart_cpu_acpi_spcr (int,struct uart_devinfo*) ; 
 int uart_cpu_fdt_probe (struct uart_class**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,void**,void**,void**) ; 
 int uart_getenv (int,struct uart_devinfo*,struct uart_class*) ; 
 int /*<<< orphan*/  uart_getops (struct uart_class*) ; 
 struct uart_class uart_ns8250_class ; 

int
uart_cpu_getdev(int devtype, struct uart_devinfo *di)
{
	struct uart_class *class;
	bus_space_handle_t bsh;
	bus_space_tag_t bst;
	u_int rclk, shift, iowidth;
	int br, err;

	/* Allow overriding the FDT using the environment. */
	class = &uart_ns8250_class;
	err = uart_getenv(devtype, di, class);
	if (err == 0)
		return (0);

#ifdef DEV_ACPI
	/* Check if SPCR can tell us what console to use. */
	if (uart_cpu_acpi_spcr(devtype, di) == 0)
		return (0);
#endif

	if (devtype != UART_DEV_CONSOLE)
		return (ENXIO);

	err = ENXIO;
#ifdef FDT
	if (err != 0) {
		err = uart_cpu_fdt_probe(&class, &bst, &bsh, &br, &rclk,
		    &shift, &iowidth);
	}
#endif
	if (err != 0)
		return (err);

	/*
	 * Finalize configuration.
	 */
	di->bas.chan = 0;
	di->bas.regshft = shift;
	di->bas.regiowidth = iowidth;
	di->baudrate = br;
	di->bas.rclk = rclk;
	di->ops = uart_getops(class);
	di->databits = 8;
	di->stopbits = 1;
	di->parity = UART_PARITY_NONE;
	di->bas.bst = bst;
	di->bas.bsh = bsh;
	uart_bus_space_mem = di->bas.bst;
	uart_bus_space_io = NULL;

	return (0);
}