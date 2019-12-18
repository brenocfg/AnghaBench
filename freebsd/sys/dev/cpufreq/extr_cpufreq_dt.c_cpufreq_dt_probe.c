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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
 int /*<<< orphan*/  OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpufreq_dt_probe(device_t dev)
{
	phandle_t node;

	node = ofw_bus_get_node(device_get_parent(dev));

	if (!OF_hasprop(node, "clocks") ||
	    (!OF_hasprop(node, "cpu-supply") &&
	    !OF_hasprop(node, "cpu0-supply")))

		return (ENXIO);

	if (!OF_hasprop(node, "operating-points") &&
	  !OF_hasprop(node, "operating-points-v2"))
		return (ENXIO);

	device_set_desc(dev, "Generic cpufreq driver");
	return (BUS_PROBE_GENERIC);
}