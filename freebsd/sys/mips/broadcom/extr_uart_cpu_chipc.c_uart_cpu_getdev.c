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
typedef  scalar_t__ u_int ;
struct uart_devinfo {int dummy; } ;

/* Variables and functions */
 int CHIPC_UART_BAUDRATE ; 
 scalar_t__ CHIPC_UART_MAX ; 
 int UART_DEV_CONSOLE ; 
 int UART_DEV_DBGPORT ; 
 int /*<<< orphan*/  UART_FLAGS_CONSOLE (int) ; 
 int /*<<< orphan*/  UART_FLAGS_DBGPORT (int) ; 
 int /*<<< orphan*/  chipc_uart_class ; 
 int /*<<< orphan*/  mips_bus_space_generic ; 
 scalar_t__ resource_int_value (char*,scalar_t__,char*,int*) ; 
 int /*<<< orphan*/ * uart_bus_space_io ; 
 int /*<<< orphan*/  uart_bus_space_mem ; 
 int uart_cpu_init (struct uart_devinfo*,scalar_t__,int) ; 
 scalar_t__ uart_getenv (int,struct uart_devinfo*,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_getenv_cfe (int,struct uart_devinfo*) ; 

int
uart_cpu_getdev(int devtype, struct uart_devinfo *di)
{
	int			 ivar;

	uart_bus_space_io = NULL;
	uart_bus_space_mem = mips_bus_space_generic;

#ifdef CFE
	/* Check the CFE environment */
	if (uart_getenv_cfe(devtype, di) == 0)
		return (0);
#endif /* CFE */

	/* Check the kernel environment. */
	if (uart_getenv(devtype, di, chipc_uart_class) == 0)
		return (0);

	/* Scan the device hints for the first matching device */
	for (u_int i = 0; i < CHIPC_UART_MAX; i++) {
		if (resource_int_value("uart", i, "flags", &ivar))
			continue;

		/* Check usability */
		if (devtype == UART_DEV_CONSOLE && !UART_FLAGS_CONSOLE(ivar))
			continue;

		if (devtype == UART_DEV_DBGPORT && !UART_FLAGS_DBGPORT(ivar))
			continue;

		if (resource_int_value("uart", i, "disabled", &ivar) == 0 &&
		    ivar == 0)
			continue;

		/* Found */
		if (resource_int_value("uart", i, "baud", &ivar) != 0)
			ivar = CHIPC_UART_BAUDRATE;
		
		return (uart_cpu_init(di, i, ivar));
	}

	/* Default to uart0/115200 */
	return (uart_cpu_init(di, 0, CHIPC_UART_BAUDRATE));
}