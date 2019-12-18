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
struct pci_dev {int revision; scalar_t__ vendor; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_VENDOR_ID_AL ; 
 struct pci_dev* ali_isa_bridge ; 
 int /*<<< orphan*/  ata_pci_bmdma_clear_simplex (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void ali_init_chipset(struct pci_dev *pdev)
{
	u8 tmp;
	struct pci_dev *north;

	/*
	 * The chipset revision selects the driver operations and
	 * mode data.
	 */

	if (pdev->revision <= 0x20) {
		pci_read_config_byte(pdev, 0x53, &tmp);
		tmp |= 0x03;
		pci_write_config_byte(pdev, 0x53, tmp);
	} else {
		pci_read_config_byte(pdev, 0x4a, &tmp);
		pci_write_config_byte(pdev, 0x4a, tmp | 0x20);
		pci_read_config_byte(pdev, 0x4B, &tmp);
		if (pdev->revision < 0xC2)
			/* 1543-E/F, 1543C-C, 1543C-D, 1543C-E */
			/* Clear CD-ROM DMA write bit */
			tmp &= 0x7F;
		/* Cable and UDMA */
		if (pdev->revision >= 0xc2)
			tmp |= 0x01;
		pci_write_config_byte(pdev, 0x4B, tmp | 0x08);
		/*
		 * CD_ROM DMA on (0x53 bit 0). Enable this even if we want
		 * to use PIO. 0x53 bit 1 (rev 20 only) - enable FIFO control
		 * via 0x54/55.
		 */
		pci_read_config_byte(pdev, 0x53, &tmp);
		if (pdev->revision >= 0xc7)
			tmp |= 0x03;
		else
			tmp |= 0x01;	/* CD_ROM enable for DMA */
		pci_write_config_byte(pdev, 0x53, tmp);
	}
	north = pci_get_domain_bus_and_slot(pci_domain_nr(pdev->bus), 0,
					    PCI_DEVFN(0, 0));
	if (north && north->vendor == PCI_VENDOR_ID_AL && ali_isa_bridge) {
		/* Configure the ALi bridge logic. For non ALi rely on BIOS.
		   Set the south bridge enable bit */
		pci_read_config_byte(ali_isa_bridge, 0x79, &tmp);
		if (pdev->revision == 0xC2)
			pci_write_config_byte(ali_isa_bridge, 0x79, tmp | 0x04);
		else if (pdev->revision > 0xC2 && pdev->revision < 0xC5)
			pci_write_config_byte(ali_isa_bridge, 0x79, tmp | 0x02);
	}
	pci_dev_put(north);
	ata_pci_bmdma_clear_simplex(pdev);
}