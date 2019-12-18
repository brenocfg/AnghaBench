#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_channel {TYPE_1__* resources; } ;
struct TYPE_2__ {int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PCIC_WRITE (int /*<<< orphan*/ ,int) ; 
 unsigned long PCIMCR_MRSET_OFF ; 
 unsigned long PCIMCR_RFSH_OFF ; 
 scalar_t__ SH7751_BCR1 ; 
 scalar_t__ SH7751_BCR2 ; 
 scalar_t__ SH7751_MCR ; 
 int /*<<< orphan*/  SH7751_PCIAINTM ; 
 int /*<<< orphan*/  SH7751_PCIBCR1 ; 
 int /*<<< orphan*/  SH7751_PCIBCR2 ; 
 int /*<<< orphan*/  SH7751_PCICONF1 ; 
 int /*<<< orphan*/  SH7751_PCICONF11 ; 
 int /*<<< orphan*/  SH7751_PCICONF2 ; 
 int /*<<< orphan*/  SH7751_PCICONF4 ; 
 int /*<<< orphan*/  SH7751_PCICONF5 ; 
 int /*<<< orphan*/  SH7751_PCICONF6 ; 
 int /*<<< orphan*/  SH7751_PCICR ; 
 int /*<<< orphan*/  SH7751_PCIINTM ; 
 int /*<<< orphan*/  SH7751_PCIIOBR ; 
 int SH7751_PCIIOBR_MASK ; 
 int /*<<< orphan*/  SH7751_PCILAR0 ; 
 int /*<<< orphan*/  SH7751_PCILAR1 ; 
 int /*<<< orphan*/  SH7751_PCILSR0 ; 
 int /*<<< orphan*/  SH7751_PCILSR1 ; 
 int /*<<< orphan*/  SH7751_PCIMBR ; 
 int /*<<< orphan*/  SH7751_PCIMCR ; 
 int /*<<< orphan*/  SH7751_PCIWCR1 ; 
 int /*<<< orphan*/  SH7751_PCIWCR2 ; 
 int /*<<< orphan*/  SH7751_PCIWCR3 ; 
 int SH7751_PCI_MEMORY_BASE ; 
 scalar_t__ SH7751_WCR1 ; 
 scalar_t__ SH7751_WCR2 ; 
 scalar_t__ SH7751_WCR3 ; 
 int /*<<< orphan*/  printk (char*) ; 

int pci_fixup_pcic(struct pci_channel *chan)
{
	unsigned long bcr1, wcr1, wcr2, wcr3, mcr;
	unsigned short bcr2;

	/*
	* Initialize the slave bus controller on the pcic.  The values used
	* here should not be hardcoded, but they should be taken from the bsc
	* on the processor, to make this function as generic as possible.
	* (i.e. Another sbc may usr different SDRAM timing settings -- in order
	* for the pcic to work, its settings need to be exactly the same.)
	*/
	bcr1 = (*(volatile unsigned long*)(SH7751_BCR1));
	bcr2 = (*(volatile unsigned short*)(SH7751_BCR2));
	wcr1 = (*(volatile unsigned long*)(SH7751_WCR1));
	wcr2 = (*(volatile unsigned long*)(SH7751_WCR2));
	wcr3 = (*(volatile unsigned long*)(SH7751_WCR3));
	mcr = (*(volatile unsigned long*)(SH7751_MCR));

	bcr1 = bcr1 | 0x00080000;  /* Enable Bit 19, BREQEN */
	(*(volatile unsigned long*)(SH7751_BCR1)) = bcr1;

	bcr1 = bcr1 | 0x40080000;  /* Enable Bit 19 BREQEN, set PCIC to slave */
	PCIC_WRITE(SH7751_PCIBCR1, bcr1);	 /* PCIC BCR1 */
	PCIC_WRITE(SH7751_PCIBCR2, bcr2);     /* PCIC BCR2 */
	PCIC_WRITE(SH7751_PCIWCR1, wcr1);     /* PCIC WCR1 */
	PCIC_WRITE(SH7751_PCIWCR2, wcr2);     /* PCIC WCR2 */
	PCIC_WRITE(SH7751_PCIWCR3, wcr3);     /* PCIC WCR3 */
	mcr = (mcr & PCIMCR_MRSET_OFF) & PCIMCR_RFSH_OFF;
	PCIC_WRITE(SH7751_PCIMCR, mcr);      /* PCIC MCR */


	/* Enable all interrupts, so we know what to fix */
	PCIC_WRITE(SH7751_PCIINTM, 0x0000c3ff);
	PCIC_WRITE(SH7751_PCIAINTM, 0x0000380f);

	/* Set up standard PCI config registers */
	PCIC_WRITE(SH7751_PCICONF1,	0xF39000C7); /* Bus Master, Mem & I/O access */
	PCIC_WRITE(SH7751_PCICONF2,	0x00000000); /* PCI Class code & Revision ID */
	PCIC_WRITE(SH7751_PCICONF4,	0xab000001); /* PCI I/O address (local regs) */
	PCIC_WRITE(SH7751_PCICONF5,	0x0c000000); /* PCI MEM address (local RAM)  */
	PCIC_WRITE(SH7751_PCICONF6,	0xd0000000); /* PCI MEM address (unused)     */
	PCIC_WRITE(SH7751_PCICONF11, 0x35051054); /* PCI Subsystem ID & Vendor ID */
	PCIC_WRITE(SH7751_PCILSR0, 0x03f00000);   /* MEM (full 64M exposed)       */
	PCIC_WRITE(SH7751_PCILSR1, 0x00000000);   /* MEM (unused)                 */
	PCIC_WRITE(SH7751_PCILAR0, 0x0c000000);   /* MEM (direct map from PCI)    */
	PCIC_WRITE(SH7751_PCILAR1, 0x00000000);   /* MEM (unused)                 */

	/* Now turn it on... */
	PCIC_WRITE(SH7751_PCICR, 0xa5000001);

	/*
	* Set PCIMBR and PCIIOBR here, assuming a single window
	* (16M MEM, 256K IO) is enough.  If a larger space is
	* needed, the readx/writex and inx/outx functions will
	* have to do more (e.g. setting registers for each call).
	*/

	/*
	* Set the MBR so PCI address is one-to-one with window,
	* meaning all calls go straight through... use BUG_ON to
	* catch erroneous assumption.
	*/
	BUG_ON(chan->resources[1].start != SH7751_PCI_MEMORY_BASE);

	PCIC_WRITE(SH7751_PCIMBR, chan->resources[1].start);

	/* Set IOBR for window containing area specified in pci.h */
	PCIC_WRITE(SH7751_PCIIOBR, (chan->resources[0].start & SH7751_PCIIOBR_MASK));

	/* All done, may as well say so... */
	printk("SH7751 PCI: Finished initialization of the PCI controller\n");

	return 1;
}