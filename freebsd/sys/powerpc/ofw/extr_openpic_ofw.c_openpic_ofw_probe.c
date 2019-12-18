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
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_finddevice (char*) ; 
 int /*<<< orphan*/  OPENPIC_DEVSTR ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
openpic_ofw_probe(device_t dev)
{
	const char *type = ofw_bus_get_type(dev);

	if (type == NULL)
                return (ENXIO);

	if (!ofw_bus_is_compatible(dev, "chrp,open-pic") &&
	    strcmp(type, "open-pic") != 0)
                return (ENXIO);

	/*
	 * On some U4 systems, there is a phantom MPIC in the mac-io cell.
	 * The uninorth driver will pick up the real PIC, so ignore it here.
	 */
	if (OF_finddevice("/u4") != (phandle_t)-1)
		return (ENXIO);

	device_set_desc(dev, OPENPIC_DEVSTR);
	return (0);
}