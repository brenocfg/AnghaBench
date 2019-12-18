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
typedef  int /*<<< orphan*/  uint32_t ;
struct pmufreq_softc {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  min_freq ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct pmufreq_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmufreq_probe(device_t dev)
{
	struct pmufreq_softc *sc;
	phandle_t node;
	uint32_t min_freq;

	if (resource_disabled("pmufreq", 0))
		return (ENXIO);

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(device_get_parent(dev));
	/*
	 * A scalable MPC7455 has min-clock-frequency/max-clock-frequency as OFW
	 * properties of the 'cpu' node.
	 */
	if (OF_getprop(node, "min-clock-frequency", &min_freq, sizeof(min_freq)) == -1)
		return (ENXIO);
	device_set_desc(dev, "PMU-based frequency scaling");
	return (0);
}