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
 int BUS_PROBE_SPECIFIC ; 
 int ENXIO ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_exists () ; 

__attribute__((used)) static int
plpar_pcibus_probe(device_t dev)
{
	phandle_t rtas;
 
	if (ofw_bus_get_node(dev) == -1 || !rtas_exists())
		return (ENXIO);

	rtas = OF_finddevice("/rtas");
	if (!OF_hasprop(rtas, "ibm,hypertas-functions"))
		return (ENXIO);

	device_set_desc(dev, "POWER Hypervisor PCI bus");

	return (BUS_PROBE_SPECIFIC);
}