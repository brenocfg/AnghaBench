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
struct TYPE_2__ {scalar_t__ rclk; scalar_t__ regshft; int /*<<< orphan*/  bsh; void* bst; scalar_t__ chan; } ;
struct uart_devinfo {int databits; int stopbits; int /*<<< orphan*/  parity; scalar_t__ baudrate; TYPE_1__ bas; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALTA_UART0ADR ; 
 int /*<<< orphan*/  MIPS_PHYS_TO_KSEG1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_PARITY_NONE ; 
 void* mips_bus_space_generic ; 
 int /*<<< orphan*/ * uart_bus_space_io ; 
 void* uart_bus_space_mem ; 
 int /*<<< orphan*/  uart_getops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_ns8250_class ; 

int
uart_cpu_getdev(int devtype, struct uart_devinfo *di)
{
	di->ops = uart_getops(&uart_ns8250_class);
	di->bas.chan = 0;
	di->bas.bst = mips_bus_space_generic;
	di->bas.bsh = MIPS_PHYS_TO_KSEG1(MALTA_UART0ADR);
	di->bas.regshft = 0;
	di->bas.rclk = 0;
	di->baudrate = 0;	/* retain the baudrate configured by YAMON */
	di->databits = 8;
	di->stopbits = 1;
	di->parity = UART_PARITY_NONE;

	uart_bus_space_io = NULL;
	uart_bus_space_mem = mips_bus_space_generic;
	return (0);
}