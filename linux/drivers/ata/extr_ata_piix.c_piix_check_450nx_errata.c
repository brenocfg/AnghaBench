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
typedef  int u16 ;
struct pci_dev {int revision; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_82454NX ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 

__attribute__((used)) static int piix_check_450nx_errata(struct pci_dev *ata_dev)
{
	struct pci_dev *pdev = NULL;
	u16 cfg;
	int no_piix_dma = 0;

	while ((pdev = pci_get_device(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82454NX, pdev)) != NULL) {
		/* Look for 450NX PXB. Check for problem configurations
		   A PCI quirk checks bit 6 already */
		pci_read_config_word(pdev, 0x41, &cfg);
		/* Only on the original revision: IDE DMA can hang */
		if (pdev->revision == 0x00)
			no_piix_dma = 1;
		/* On all revisions below 5 PXB bus lock must be disabled for IDE */
		else if (cfg & (1<<14) && pdev->revision < 5)
			no_piix_dma = 2;
	}
	if (no_piix_dma)
		dev_warn(&ata_dev->dev,
			 "450NX errata present, disabling IDE DMA%s\n",
			 no_piix_dma == 2 ? " - a BIOS update may resolve this"
			 : "");

	return no_piix_dma;
}