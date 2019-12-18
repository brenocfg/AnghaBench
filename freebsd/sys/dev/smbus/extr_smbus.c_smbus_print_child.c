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
struct smbus_ivar {scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct smbus_ivar* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,scalar_t__) ; 

__attribute__((used)) static int
smbus_print_child(device_t parent, device_t child)
{
	struct smbus_ivar *devi;
	int retval;

	devi = device_get_ivars(child);
	retval = bus_print_child_header(parent, child);
	if (devi->addr != 0)
		retval += printf(" at addr 0x%x", devi->addr);
	retval += bus_print_child_footer(parent, child);

	return (retval);
}