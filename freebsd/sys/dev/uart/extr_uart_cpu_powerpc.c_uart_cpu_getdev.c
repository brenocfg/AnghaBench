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
struct TYPE_2__ {int regshft; int chan; char rclk; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
struct uart_devinfo {char baudrate; int databits; int stopbits; int /*<<< orphan*/  parity; TYPE_1__ bas; int /*<<< orphan*/  ops; } ;
struct uart_class {int dummy; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int OF_decode_addr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int OF_finddevice (char*) ; 
 int OF_getprop (int,char*,char*,int) ; 
#define  UART_DEV_CONSOLE 129 
#define  UART_DEV_DBGPORT 128 
 int /*<<< orphan*/  UART_PARITY_NONE ; 
 int /*<<< orphan*/  getenv_string (char*,char*,int) ; 
 scalar_t__ ofw_bus_node_is_compatible (int,char*) ; 
 int ofw_get_console_phandle_path (int,int*,char*) ; 
 int ofw_get_uart_console (int,int*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  uart_getops (struct uart_class*) ; 
 struct uart_class uart_ns8250_class ; 
 struct uart_class uart_z8530_class ; 

int
uart_cpu_getdev(int devtype, struct uart_devinfo *di)
{
	char buf[64];
	struct uart_class *class;
	phandle_t input, opts, chosen;
	int error;

	opts = OF_finddevice("/options");
	chosen = OF_finddevice("/chosen");
	switch (devtype) {
	case UART_DEV_CONSOLE:
		error = ENXIO;
		if (chosen != -1 && error != 0)
			error = ofw_get_uart_console(chosen, &input,
			    "stdout-path", NULL);
		if (chosen != -1 && error != 0)
			error = ofw_get_uart_console(chosen, &input,
			    "linux,stdout-path", NULL);
		if (chosen != -1 && error != 0)
			error = ofw_get_console_phandle_path(chosen, &input,
			    "stdout");
		if (chosen != -1 && error != 0)
			error = ofw_get_uart_console(chosen, &input,
			    "stdin-path", NULL);
		if (chosen != -1 && error != 0)
			error = ofw_get_console_phandle_path(chosen, &input,
			    "stdin");
		if (opts != -1 && error != 0)
			error = ofw_get_uart_console(opts, &input,
			    "input-device", "output-device");
		if (opts != -1 && error != 0)
			error = ofw_get_uart_console(opts, &input,
			    "input-device-1", "output-device-1");
		if (error != 0) {
			input = OF_finddevice("serial0"); /* Last ditch */
			if (input == -1)
				error = (ENXIO);
		}

		if (error != 0)
			return (error);
		break;
	case UART_DEV_DBGPORT:
		if (!getenv_string("hw.uart.dbgport", buf, sizeof(buf)))
			return (ENXIO);
		input = OF_finddevice(buf);
		if (input == -1)
			return (ENXIO);
		break;
	default:
		return (EINVAL);
	}

	if (OF_getprop(input, "device_type", buf, sizeof(buf)) == -1)
		return (ENXIO);
	if (strcmp(buf, "serial") != 0)
		return (ENXIO);

	if (ofw_bus_node_is_compatible(input, "chrp,es")) {
		class = &uart_z8530_class;
		di->bas.regshft = 4;
		di->bas.chan = 1;
	} else if (ofw_bus_node_is_compatible(input,"ns16550") ||
	    ofw_bus_node_is_compatible(input,"ns8250")) {
		class = &uart_ns8250_class;
		di->bas.regshft = 0;
		di->bas.chan = 0;
	} else
		return (ENXIO);

	if (class == NULL)
		return (ENXIO);

	error = OF_decode_addr(input, 0, &di->bas.bst, &di->bas.bsh, NULL);
	if (error)
		return (error);

	di->ops = uart_getops(class);

	if (OF_getprop(input, "clock-frequency", &di->bas.rclk, 
	    sizeof(di->bas.rclk)) == -1)
		di->bas.rclk = 230400;
	if (OF_getprop(input, "current-speed", &di->baudrate, 
	    sizeof(di->baudrate)) == -1)
		di->baudrate = 0;
	OF_getprop(input, "reg-shift", &di->bas.regshft,
	    sizeof(di->bas.regshft));

	di->databits = 8;
	di->stopbits = 1;
	di->parity = UART_PARITY_NONE;
	return (0);
}