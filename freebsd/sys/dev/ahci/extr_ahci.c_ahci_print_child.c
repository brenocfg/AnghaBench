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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 intptr_t AHCI_EM_UNIT ; 
 int AHCI_UNIT ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,int) ; 

int
ahci_print_child(device_t dev, device_t child)
{
	intptr_t ivars;
	int retval;

	retval = bus_print_child_header(dev, child);
	ivars = (intptr_t)device_get_ivars(child);
	if ((ivars & AHCI_EM_UNIT) == 0)
		retval += printf(" at channel %d", (int)ivars & AHCI_UNIT);
	retval += bus_print_child_footer(dev, child);
	return (retval);
}