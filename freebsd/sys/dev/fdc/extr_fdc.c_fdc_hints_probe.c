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
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdc_add_child (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ resource_find_match (int*,char const**,int*,char*,char const*) ; 
 int /*<<< orphan*/  resource_int_value (char const*,int,char*,int*) ; 

int
fdc_hints_probe(device_t dev)
{
	const char *name, *dname;
	int i, error, dunit;

	/*
	 * Probe and attach any children.  We should probably detect
	 * devices from the BIOS unless overridden.
	 */
	name = device_get_nameunit(dev);
	i = 0;
	while ((resource_find_match(&i, &dname, &dunit, "at", name)) == 0) {
		resource_int_value(dname, dunit, "drive", &dunit);
		fdc_add_child(dev, dname, dunit);
	}

	if ((error = bus_generic_attach(dev)) != 0)
		return (error);
	return (0);
}