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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS5536_IDE_FLASH_SIGNATURE ; 
 int /*<<< orphan*/  PCI_IDE_CFG_REG ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void loongson_cs5536_ide_fixup(struct pci_dev *pdev)
{
	/* setting the mutex pin as IDE function */
	pci_write_config_dword(pdev, PCI_IDE_CFG_REG,
			       CS5536_IDE_FLASH_SIGNATURE);
}