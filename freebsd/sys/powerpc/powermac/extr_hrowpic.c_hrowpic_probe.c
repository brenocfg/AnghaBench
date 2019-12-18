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
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
hrowpic_probe(device_t dev)
{
	const char *type = ofw_bus_get_type(dev);

	/*
	 * OpenPIC cells have a type of "open-pic", so this
	 * is sufficient to identify a Heathrow cell
	 */
	if (strcmp(type, "interrupt-controller") != 0)
		return (ENXIO);

	/*
	 * The description was already printed out in the nexus
	 * probe, so don't do it again here
	 */
	device_set_desc(dev, "Heathrow MacIO interrupt controller");
	return (0);
}