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
 int /*<<< orphan*/  MRDMODE ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int /*<<< orphan*/  UDIDETCR0 ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cmd64x_fixup(struct pci_dev *pdev)
{
	u8 mrdmode;

	pci_write_config_byte(pdev, PCI_LATENCY_TIMER, 64);
	pci_read_config_byte(pdev, MRDMODE, &mrdmode);
	mrdmode &= ~0x30;	/* IRQ set up */
	mrdmode |= 0x02;	/* Memory read line enable */
	pci_write_config_byte(pdev, MRDMODE, mrdmode);

	/* PPC specific fixup copied from old driver */
#ifdef CONFIG_PPC
	pci_write_config_byte(pdev, UDIDETCR0, 0xF0);
#endif
}