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
 scalar_t__ device_get_desc (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 scalar_t__ device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ printf (char*,char*) ; 

int
bus_print_child_header(device_t dev, device_t child)
{
	int	retval = 0;

	if (device_get_desc(child)) {
		retval += device_printf(child, "<%s>", device_get_desc(child));
	} else {
		retval += printf("%s", device_get_nameunit(child));
	}

	return (retval);
}