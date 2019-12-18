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
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int
cs4231_bus_probe(device_t dev)
{
	const char *compat, *name;

	compat = ofw_bus_get_compat(dev);
	name = ofw_bus_get_name(dev);
	if (strcmp("SUNW,CS4231", name) == 0 ||
	    (compat != NULL && strcmp("SUNW,CS4231", compat) == 0)) {
		device_set_desc(dev, "Sun Audiocs");
		return (BUS_PROBE_DEFAULT);
	}
	return (ENXIO);
}