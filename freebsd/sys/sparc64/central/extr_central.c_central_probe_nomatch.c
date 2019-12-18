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
 int /*<<< orphan*/  central_print_res (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void
central_probe_nomatch(device_t dev, device_t child)
{
	const char *type;

	device_printf(dev, "<%s>", ofw_bus_get_name(child));
	central_print_res(device_get_ivars(child));
	type = ofw_bus_get_type(child);
	printf(" type %s (no driver attached)\n",
	    type != NULL ? type : "unknown");
}