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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCIC_SERIALBUS ; 
 scalar_t__ PCIP_SERIALBUS_USB_XHCI ; 
 scalar_t__ PCIS_SERIALBUS_USB ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_progif (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
xhci_pci_match(device_t self)
{
	uint32_t device_id = pci_get_devid(self);

	switch (device_id) {
	case 0x145c1022:
		return ("AMD KERNCZ USB 3.0 controller");
	case 0x43ba1022:
		return ("AMD X399 USB 3.0 controller");
	case 0x43b91022: /* X370 */
	case 0x43bb1022: /* B350 */
		return ("AMD 300 Series USB 3.0 controller");
	case 0x78141022:
		return ("AMD FCH USB 3.0 controller");

	case 0x01941033:
		return ("NEC uPD720200 USB 3.0 controller");
	case 0x00151912:
		return ("NEC uPD720202 USB 3.0 controller");

	case 0x10001b73:
		return ("Fresco Logic FL1000G USB 3.0 controller");
	case 0x11001b73:
		return ("Fresco Logic FL1100 USB 3.0 controller");

	case 0x10421b21:
		return ("ASMedia ASM1042 USB 3.0 controller");
	case 0x11421b21:
		return ("ASMedia ASM1042A USB 3.0 controller");

	case 0x0f358086:
		return ("Intel BayTrail USB 3.0 controller");
	case 0x19d08086:
		return ("Intel Denverton USB 3.0 controller");
	case 0x9c318086:
	case 0x1e318086:
		return ("Intel Panther Point USB 3.0 controller");
	case 0x22b58086:
		return ("Intel Braswell USB 3.0 controller");
	case 0x5aa88086:
		return ("Intel Apollo Lake USB 3.0 controller");
	case 0x8c318086:
		return ("Intel Lynx Point USB 3.0 controller");
	case 0x8cb18086:
		return ("Intel Wildcat Point USB 3.0 controller");
	case 0x8d318086:
		return ("Intel Wellsburg USB 3.0 controller");
	case 0x9cb18086:
		return ("Broadwell Integrated PCH-LP chipset USB 3.0 controller");
	case 0x9d2f8086:
		return ("Intel Sunrise Point-LP USB 3.0 controller");
	case 0xa12f8086:
		return ("Intel Sunrise Point USB 3.0 controller");
	case 0xa1af8086:
		return ("Intel Lewisburg USB 3.0 controller");
	case 0xa2af8086:
		return ("Intel Union Point USB 3.0 controller");
	case 0xa36d8086:
		return ("Intel Cannon Lake USB 3.1 controller");

	case 0xa01b177d:
		return ("Cavium ThunderX USB 3.0 controller");

	default:
		break;
	}

	if ((pci_get_class(self) == PCIC_SERIALBUS)
	    && (pci_get_subclass(self) == PCIS_SERIALBUS_USB)
	    && (pci_get_progif(self) == PCIP_SERIALBUS_USB_XHCI)) {
		return ("XHCI (generic) USB 3.0 controller");
	}
	return (NULL);			/* dunno */
}