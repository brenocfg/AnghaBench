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

/* Variables and functions */
 int /*<<< orphan*/  of_console_device ; 
 int /*<<< orphan*/  of_node_is_type (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prom_halt () ; 
 int /*<<< orphan*/  prom_halt_power_off () ; 
 scalar_t__ scons_pwroff ; 

void machine_power_off(void)
{
	if (!of_node_is_type(of_console_device, "serial") || scons_pwroff)
		prom_halt_power_off();

	prom_halt();
}