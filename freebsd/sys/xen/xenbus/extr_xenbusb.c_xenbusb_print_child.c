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
struct xenbus_device_ivars {char* xd_node; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xenbus_device_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,char*) ; 

int
xenbusb_print_child(device_t dev, device_t child)
{
	struct xenbus_device_ivars *ivars = device_get_ivars(child);
	int	retval = 0;

	retval += bus_print_child_header(dev, child);
	retval += printf(" at %s", ivars->xd_node);
	retval += bus_print_child_footer(dev, child);

	return (retval);
}