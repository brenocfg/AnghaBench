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
 int /*<<< orphan*/  OFW_SBUS_NAME ; 
 int /*<<< orphan*/  OFW_SBUS_TYPE ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char const* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sbus_probe(device_t dev)
{
	const char *t;

	t = ofw_bus_get_type(dev);
	if (((t == NULL || strcmp(t, OFW_SBUS_TYPE) != 0)) &&
	    strcmp(ofw_bus_get_name(dev), OFW_SBUS_NAME) != 0)
		return (ENXIO);
	device_set_desc(dev, "U2S UPA-SBus bridge");
	return (0);
}