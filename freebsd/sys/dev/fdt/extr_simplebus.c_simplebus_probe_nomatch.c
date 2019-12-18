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
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  simplebus_print_res (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
simplebus_probe_nomatch(device_t bus, device_t child)
{
	const char *name, *type, *compat;

	if (!bootverbose)
		return;

	compat = ofw_bus_get_compat(child);
	if (compat == NULL)
		return;
	name = ofw_bus_get_name(child);
	type = ofw_bus_get_type(child);

	device_printf(bus, "<%s>", name != NULL ? name : "unknown");
	simplebus_print_res(device_get_ivars(child));
	if (!ofw_bus_status_okay(child))
		printf(" disabled");
	if (type)
		printf(" type %s", type);
	printf(" compat %s (no driver attached)\n", compat);
}