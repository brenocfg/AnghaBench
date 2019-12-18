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
agp_intel_match(device_t dev)
{
	if (pci_get_class(dev) != PCIC_BRIDGE
	    || pci_get_subclass(dev) != PCIS_BRIDGE_HOST)
		return (NULL);

	if (agp_find_caps(dev) == 0)
		return (NULL);

	switch (pci_get_devid(dev)) {
	/* Intel -- vendor 0x8086 */
	case 0x71808086:
		return ("Intel 82443LX (440 LX) host to PCI bridge");
	case 0x71908086:
		return ("Intel 82443BX (440 BX) host to PCI bridge");
 	case 0x71a08086:
 		return ("Intel 82443GX host to PCI bridge");
 	case 0x71a18086:
 		return ("Intel 82443GX host to AGP bridge");
	case 0x11308086:
		return ("Intel 82815 (i815 GMCH) host to PCI bridge");
	case 0x25008086:
	case 0x25018086:
		return ("Intel 82820 host to AGP bridge");
	case 0x35758086:
		return ("Intel 82830 host to AGP bridge");
	case 0x1a218086:
		return ("Intel 82840 host to AGP bridge");
	case 0x1a308086:
		return ("Intel 82845 host to AGP bridge");
	case 0x25308086:
		return ("Intel 82850 host to AGP bridge");
	case 0x33408086:
		return ("Intel 82855 host to AGP bridge");
	case 0x25318086:
		return ("Intel 82860 host to AGP bridge");
	case 0x25708086:
		return ("Intel 82865 host to AGP bridge");
	case 0x255d8086:
		return ("Intel E7205 host to AGP bridge");
	case 0x25508086:
		return ("Intel E7505 host to AGP bridge");
	case 0x25788086:
		return ("Intel 82875P host to AGP bridge");
	case 0x25608086:
		return ("Intel 82845G host to AGP bridge");
	case 0x35808086:
		return ("Intel 82855GM host to AGP bridge");
	}

	return (NULL);
}