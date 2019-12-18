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
struct pci_dev {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIIX4_FUNC1_IDETIM_PRIMARY_HI ; 
 unsigned char PIIX4_FUNC1_IDETIM_PRIMARY_HI_IDE_DECODE_EN ; 
 int /*<<< orphan*/  PIIX4_FUNC1_IDETIM_SECONDARY_HI ; 
 unsigned char PIIX4_FUNC1_IDETIM_SECONDARY_HI_IDE_DECODE_EN ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void malta_piix_func1_fixup(struct pci_dev *pdev)
{
	unsigned char reg_val;

	/* Done by YAMON 2.02 onwards */
	if (PCI_SLOT(pdev->devfn) == 10) {
		/*
		 * IDE Decode enable.
		 */
		pci_read_config_byte(pdev, PIIX4_FUNC1_IDETIM_PRIMARY_HI,
			&reg_val);
		pci_write_config_byte(pdev, PIIX4_FUNC1_IDETIM_PRIMARY_HI,
			reg_val|PIIX4_FUNC1_IDETIM_PRIMARY_HI_IDE_DECODE_EN);
		pci_read_config_byte(pdev, PIIX4_FUNC1_IDETIM_SECONDARY_HI,
			&reg_val);
		pci_write_config_byte(pdev, PIIX4_FUNC1_IDETIM_SECONDARY_HI,
			reg_val|PIIX4_FUNC1_IDETIM_SECONDARY_HI_IDE_DECODE_EN);
	}
}