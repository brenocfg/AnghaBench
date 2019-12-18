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
 int EEXIST ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 scalar_t__ ti_scm_sc ; 
 int /*<<< orphan*/  ti_soc_is_supported () ; 

__attribute__((used)) static int
ti_scm_probe(device_t dev)
{

	if (!ti_soc_is_supported())
		return (ENXIO);

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (!ofw_bus_is_compatible(dev, "syscon"))
		return (ENXIO);

	if (ti_scm_sc) {
		return (EEXIST);
	}

	device_set_desc(dev, "TI Control Module");
	return (BUS_PROBE_DEFAULT);
}