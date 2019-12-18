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
struct uart_devinfo {int /*<<< orphan*/  type; struct consdev* cookie; } ;
struct consdev {struct uart_devinfo* cn_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UART_DEV_CONSOLE ; 
 int /*<<< orphan*/  uart_add_sysdev (struct uart_devinfo*) ; 
 int /*<<< orphan*/  uart_init (struct uart_devinfo*) ; 

__attribute__((used)) static void
uart_cninit(struct consdev *cp)
{
	struct uart_devinfo *di;

	/*
	 * Yedi trick: we need to be able to define cn_dev before we go
	 * single- or multi-user. The problem is that we don't know at
	 * this time what the device will be. Hence, we need to link from
	 * the uart_devinfo to the consdev that corresponds to it so that
	 * we can define cn_dev in uart_bus_attach() when we find the
	 * device during bus enumeration. That's when we'll know what the
	 * the unit number will be.
	 */
	di = cp->cn_arg;
	KASSERT(di->cookie == NULL, ("foo"));
	di->cookie = cp;
	di->type = UART_DEV_CONSOLE;
	uart_add_sysdev(di);
	uart_init(di);
}