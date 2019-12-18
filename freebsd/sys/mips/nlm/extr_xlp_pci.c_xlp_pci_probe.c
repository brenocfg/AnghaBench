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
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
xlp_pci_probe(device_t dev)
{
	device_t pcib;

	pcib = device_get_parent(dev);
	/*
	 * Only the top level bus has SoC devices, leave the rest to
	 * Generic PCI code
	 */
	if (strcmp(device_get_nameunit(pcib), "pcib0") != 0)
		return (ENXIO);
	device_set_desc(dev, "XLP SoCbus");
	return (BUS_PROBE_DEFAULT);
}