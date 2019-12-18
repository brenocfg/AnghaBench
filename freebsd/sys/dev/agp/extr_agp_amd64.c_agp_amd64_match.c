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
 int /*<<< orphan*/  agp_amd64_nvidia_match (int) ; 
 scalar_t__ agp_find_caps (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*
agp_amd64_match(device_t dev)
{
	if (pci_get_class(dev) != PCIC_BRIDGE ||
	    pci_get_subclass(dev) != PCIS_BRIDGE_HOST ||
	    agp_find_caps(dev) == 0)
		return (NULL);

	switch (pci_get_devid(dev)) {
	case 0x74541022:
		return ("AMD 8151 AGP graphics tunnel");
	case 0x07551039:
		return ("SiS 755 host to AGP bridge");
	case 0x07601039:
		return ("SiS 760 host to AGP bridge");
	case 0x168910b9:
		return ("ULi M1689 AGP Controller");
	case 0x00d110de:
		if (agp_amd64_nvidia_match(0x00d2))
			return (NULL);
		return ("NVIDIA nForce3 AGP Controller");
	case 0x00e110de:
		if (agp_amd64_nvidia_match(0x00e2))
			return (NULL);
		return ("NVIDIA nForce3-250 AGP Controller");
	case 0x02041106:
		return ("VIA 8380 host to PCI bridge");
	case 0x02381106:
		return ("VIA 3238 host to PCI bridge");
	case 0x02821106:
		return ("VIA K8T800Pro host to PCI bridge");
	case 0x31881106:
		return ("VIA 8385 host to PCI bridge");
	}

	return (NULL);
}