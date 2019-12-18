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
 int /*<<< orphan*/  PCI_UART1_INT_REG ; 
 int /*<<< orphan*/  PCI_UART2_INT_REG ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void loongson_cs5536_isa_fixup(struct pci_dev *pdev)
{
	/* the uart1 and uart2 interrupt in PIC is enabled as default */
	pci_write_config_dword(pdev, PCI_UART1_INT_REG, 1);
	pci_write_config_dword(pdev, PCI_UART2_INT_REG, 1);
}