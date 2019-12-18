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
 char* device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int printf (char*,...) ; 

int
device_print_prettyname(device_t dev)
{
	const char *name = device_get_name(dev);

	if (name == NULL)
		return (printf("unknown: "));
	return (printf("%s%d: ", name, device_get_unit(dev)));
}