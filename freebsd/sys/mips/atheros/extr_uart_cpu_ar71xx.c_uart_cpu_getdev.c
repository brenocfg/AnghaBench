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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int regshft; int /*<<< orphan*/  bsh; int /*<<< orphan*/  rclk; void* bst; scalar_t__ chan; } ;
struct uart_devinfo {int baudrate; int databits; int stopbits; TYPE_1__ bas; int /*<<< orphan*/  parity; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_UART_ADDR ; 
 int /*<<< orphan*/  MIPS_PHYS_TO_KSEG1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_PARITY_NONE ; 
 void* ar71xx_bus_space_reversed ; 
 int /*<<< orphan*/  ar71xx_uart_freq () ; 
 int /*<<< orphan*/ * uart_bus_space_io ; 
 void* uart_bus_space_mem ; 
 int /*<<< orphan*/  uart_getops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_ns8250_class ; 

int
uart_cpu_getdev(int devtype, struct uart_devinfo *di)
{
	uint64_t freq;

	freq = ar71xx_uart_freq();

	di->ops = uart_getops(&uart_ns8250_class);
	di->bas.chan = 0;
	di->bas.bst = ar71xx_bus_space_reversed;
	di->bas.regshft = 2;
	di->bas.rclk = freq;
	di->baudrate = 115200;
	di->databits = 8;
	di->stopbits = 1;

	di->parity = UART_PARITY_NONE;

	uart_bus_space_io = NULL;
	uart_bus_space_mem = ar71xx_bus_space_reversed;
	di->bas.bsh = MIPS_PHYS_TO_KSEG1(AR71XX_UART_ADDR);
	return (0);
}