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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  AUXIO_POWER_OFF ; 
 scalar_t__ auxio_power_register ; 
 int /*<<< orphan*/  machine_halt () ; 
 int /*<<< orphan*/  of_console_device ; 
 int /*<<< orphan*/  of_node_is_type (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sbus_readb (scalar_t__) ; 
 int /*<<< orphan*/  sbus_writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ scons_pwroff ; 

void machine_power_off(void)
{
	if (auxio_power_register &&
	    (!of_node_is_type(of_console_device, "serial") || scons_pwroff)) {
		u8 power_register = sbus_readb(auxio_power_register);
		power_register |= AUXIO_POWER_OFF;
		sbus_writeb(power_register, auxio_power_register);
	}

	machine_halt();
}