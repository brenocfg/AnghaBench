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
 scalar_t__ PCIC_BRIDGE ; 
 scalar_t__ PCIS_BRIDGE_HOST ; 
 scalar_t__ agp_find_caps (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*
agp_amd_match(device_t dev)
{
	if (pci_get_class(dev) != PCIC_BRIDGE
	    || pci_get_subclass(dev) != PCIS_BRIDGE_HOST)
		return NULL;

	if (agp_find_caps(dev) == 0)
		return NULL;

	switch (pci_get_devid(dev)) {
	case 0x70061022:
		return ("AMD 751 host to AGP bridge");
	case 0x700e1022:
		return ("AMD 761 host to AGP bridge");
	case 0x700c1022:
		return ("AMD 762 host to AGP bridge");
	}

	return NULL;
}