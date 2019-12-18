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
 scalar_t__ PCIS_SERIALBUS_USB ; 
 scalar_t__ PCI_INTERFACE_OHCI ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_progif (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
ohci_pci_match(device_t self)
{
	uint32_t device_id = pci_get_devid(self);

	switch (device_id) {
	case 0x523710b9:
		return ("AcerLabs M5237 (Aladdin-V) USB controller");

	case 0x740c1022:
		return ("AMD-756 USB Controller");
	case 0x74141022:
		return ("AMD-766 USB Controller");
	case 0x78071022:
		return ("AMD FCH USB Controller");

	case 0x43741002:
		return "ATI SB400 USB Controller";
	case 0x43751002:
		return "ATI SB400 USB Controller";
	case 0x43971002:
		return ("AMD SB7x0/SB8x0/SB9x0 USB controller");
	case 0x43981002:
		return ("AMD SB7x0/SB8x0/SB9x0 USB controller");
	case 0x43991002:
		return ("AMD SB7x0/SB8x0/SB9x0 USB controller");

	case 0x06701095:
		return ("CMD Tech 670 (USB0670) USB controller");

	case 0x06731095:
		return ("CMD Tech 673 (USB0673) USB controller");

	case 0xc8611045:
		return ("OPTi 82C861 (FireLink) USB controller");

	case 0x00351033:
		return ("NEC uPD 9210 USB controller");

	case 0x00d710de:
		return ("nVidia nForce3 USB Controller");

	case 0x005a10de:
		return ("nVidia nForce CK804 USB Controller");
	case 0x036c10de:
		return ("nVidia nForce MCP55 USB Controller");
	case 0x03f110de:
		return ("nVidia nForce MCP61 USB Controller");
	case 0x0aa510de:
		return ("nVidia nForce MCP79 USB Controller");
	case 0x0aa710de:
		return ("nVidia nForce MCP79 USB Controller");
	case 0x0aa810de:
		return ("nVidia nForce MCP79 USB Controller");

	case 0x70011039:
		return ("SiS 5571 USB controller");

	case 0x1103108e:
		return "Sun PCIO-2 USB controller";

	case 0x0019106b:
		return ("Apple KeyLargo USB controller");
	case 0x003f106b:
		return ("Apple KeyLargo/Intrepid USB controller");

	default:
		break;
	}
	if ((pci_get_class(self) == PCIC_SERIALBUS) &&
	    (pci_get_subclass(self) == PCIS_SERIALBUS_USB) &&
	    (pci_get_progif(self) == PCI_INTERFACE_OHCI)) {
		return ("OHCI (generic) USB controller");
	}
	return (NULL);
}