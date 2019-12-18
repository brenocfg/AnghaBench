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
typedef  int u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVICE_ID_VIA_8235 ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_VIA_8237 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_VIA ; 
 int acpi_regs_addr ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

__attribute__((used)) static int longhaul_setup_southbridge(void)
{
	struct pci_dev *dev;
	u8 pci_cmd;

	/* Find VT8235 southbridge */
	dev = pci_get_device(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8235, NULL);
	if (dev == NULL)
		/* Find VT8237 southbridge */
		dev = pci_get_device(PCI_VENDOR_ID_VIA,
				     PCI_DEVICE_ID_VIA_8237, NULL);
	if (dev != NULL) {
		/* Set transition time to max */
		pci_read_config_byte(dev, 0xec, &pci_cmd);
		pci_cmd &= ~(1 << 2);
		pci_write_config_byte(dev, 0xec, pci_cmd);
		pci_read_config_byte(dev, 0xe4, &pci_cmd);
		pci_cmd &= ~(1 << 7);
		pci_write_config_byte(dev, 0xe4, pci_cmd);
		pci_read_config_byte(dev, 0xe5, &pci_cmd);
		pci_cmd |= 1 << 7;
		pci_write_config_byte(dev, 0xe5, pci_cmd);
		/* Get address of ACPI registers block*/
		pci_read_config_byte(dev, 0x81, &pci_cmd);
		if (pci_cmd & 1 << 7) {
			pci_read_config_dword(dev, 0x88, &acpi_regs_addr);
			acpi_regs_addr &= 0xff00;
			pr_info("ACPI I/O at 0x%x\n", acpi_regs_addr);
		}

		pci_dev_put(dev);
		return 1;
	}
	return 0;
}