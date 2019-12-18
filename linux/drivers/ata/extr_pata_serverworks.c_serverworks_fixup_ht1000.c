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
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void serverworks_fixup_ht1000(struct pci_dev *pdev)
{
	u8 btr;
	/* Setup HT1000 SouthBridge Controller - Single Channel Only */
	pci_read_config_byte(pdev, 0x5A, &btr);
	btr &= ~0x40;
	btr |= 0x3;
	pci_write_config_byte(pdev, 0x5A, btr);
}