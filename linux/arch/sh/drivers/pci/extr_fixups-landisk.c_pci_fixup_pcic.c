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
struct pci_channel {int dummy; } ;

/* Variables and functions */
 unsigned long PCIMCR_MRSET_OFF ; 
 unsigned long PCIMCR_RFSH_OFF ; 
 int /*<<< orphan*/  SH4_PCIBCR1 ; 
 int /*<<< orphan*/  SH4_PCILAR0 ; 
 int /*<<< orphan*/  SH4_PCILAR1 ; 
 int /*<<< orphan*/  SH4_PCIMCR ; 
 int /*<<< orphan*/  SH7751_BCR1 ; 
 int /*<<< orphan*/  SH7751_MCR ; 
 int /*<<< orphan*/  SH7751_PCICONF5 ; 
 int /*<<< orphan*/  SH7751_PCICONF6 ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_reg (struct pci_channel*,int,int /*<<< orphan*/ ) ; 

int pci_fixup_pcic(struct pci_channel *chan)
{
	unsigned long bcr1, mcr;

	bcr1 = __raw_readl(SH7751_BCR1);
	bcr1 |= 0x40080000;	/* Enable Bit 19 BREQEN, set PCIC to slave */
	pci_write_reg(chan, bcr1, SH4_PCIBCR1);

	mcr = __raw_readl(SH7751_MCR);
	mcr = (mcr & PCIMCR_MRSET_OFF) & PCIMCR_RFSH_OFF;
	pci_write_reg(chan, mcr, SH4_PCIMCR);

	pci_write_reg(chan, 0x0c000000, SH7751_PCICONF5);
	pci_write_reg(chan, 0xd0000000, SH7751_PCICONF6);
	pci_write_reg(chan, 0x0c000000, SH4_PCILAR0);
	pci_write_reg(chan, 0x00000000, SH4_PCILAR1);

	return 0;
}