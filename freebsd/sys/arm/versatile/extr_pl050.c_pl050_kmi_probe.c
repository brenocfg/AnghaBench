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
 scalar_t__ kmi_attached ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pl050_kmi_probe(device_t dev)
{

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	/*
	 * PL050 is plain PS2 port that pushes bytes to/from computer
	 * VersatilePB has two such ports and QEMU simulates keyboard
	 * connected to port #0 and mouse connected to port #1. This
	 * information can't be obtained from device tree so we just
	 * hardcode this knowledge here. We attach keyboard driver to
	 * port #0 and ignore port #1
	 */
	if (kmi_attached)
		return (ENXIO);

	if (ofw_bus_is_compatible(dev, "arm,pl050")) {
		device_set_desc(dev, "PL050 Keyboard/Mouse Interface");
		return (BUS_PROBE_DEFAULT);
	}

	return (ENXIO);
}