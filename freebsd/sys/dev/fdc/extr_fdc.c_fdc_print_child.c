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
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int fdc_get_fdunit (int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,...) ; 

int
fdc_print_child(device_t me, device_t child)
{
	int retval = 0, flags;

	retval += bus_print_child_header(me, child);
	retval += printf(" on %s drive %d", device_get_nameunit(me),
	       fdc_get_fdunit(child));
	if ((flags = device_get_flags(me)) != 0)
		retval += printf(" flags %#x", flags);
	retval += printf("\n");

	return (retval);
}