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
 int /*<<< orphan*/  SC_DRIVER_NAME ; 
 int SC_MD_FLAGS ; 
 int SC_MD_MAX ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int sc_probe_unit (int,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sc_probe(device_t dev)
{
	int unit;

	unit = device_get_unit(dev);
	if (strcmp(ofw_bus_get_name(dev), SC_DRIVER_NAME) != 0 ||
	    unit >= SC_MD_MAX)
		return (ENXIO);

	device_set_desc(dev, "System console");
	return (sc_probe_unit(unit, device_get_flags(dev) | SC_MD_FLAGS));
}