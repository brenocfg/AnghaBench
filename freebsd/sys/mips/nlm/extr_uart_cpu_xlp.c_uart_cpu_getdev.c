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
struct TYPE_2__ {int regshft; int /*<<< orphan*/  rclk; int /*<<< orphan*/  bsh; void* bst; scalar_t__ chan; } ;
struct uart_devinfo {int databits; int stopbits; int /*<<< orphan*/  parity; int /*<<< orphan*/  baudrate; TYPE_1__ bas; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOARD_CONSOLE_SPEED ; 
 int /*<<< orphan*/  BOARD_CONSOLE_UART ; 
 int /*<<< orphan*/  UART_PARITY_NONE ; 
 int /*<<< orphan*/  XLP_IO_CLK ; 
 int /*<<< orphan*/  nlm_get_uart_regbase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* rmi_uart_bus_space ; 
 int /*<<< orphan*/ * uart_bus_space_io ; 
 void* uart_bus_space_mem ; 
 int /*<<< orphan*/  uart_getops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_ns8250_class ; 

int
uart_cpu_getdev(int devtype, struct uart_devinfo *di)
{
	di->ops = uart_getops(&uart_ns8250_class);
	di->bas.chan = 0;
	di->bas.bst = rmi_uart_bus_space;
	di->bas.bsh = nlm_get_uart_regbase(0, BOARD_CONSOLE_UART);

	di->bas.regshft = 2;
	/* divisor = rclk / (baudrate * 16); */
	di->bas.rclk = XLP_IO_CLK;
	di->baudrate = BOARD_CONSOLE_SPEED;
	di->databits = 8;
	di->stopbits = 1;
	di->parity = UART_PARITY_NONE;

	uart_bus_space_io = NULL;
	uart_bus_space_mem = rmi_uart_bus_space;
	return (0);
}