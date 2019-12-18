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
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
 scalar_t__ PCIC_SERIALBUS ; 
 scalar_t__ PCIS_SERIALBUS_IPMI ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipmi2_pci_probe(device_t dev)
{

	if (pci_get_class(dev) == PCIC_SERIALBUS &&
	    pci_get_subclass(dev) == PCIS_SERIALBUS_IPMI) {
		device_set_desc(dev, "IPMI System Interface");
		return (BUS_PROBE_GENERIC);
	}

	return (ENXIO);
}