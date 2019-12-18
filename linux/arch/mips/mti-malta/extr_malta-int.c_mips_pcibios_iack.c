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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int BONITO_PCIMAP_CFG ; 
 int /*<<< orphan*/  GT_PCI0_IACK_OFS ; 
 int GT_READ (int /*<<< orphan*/ ) ; 
#define  MIPS_REVISION_SCON_BONITO 133 
#define  MIPS_REVISION_SCON_GT64120 132 
#define  MIPS_REVISION_SCON_ROCIT 131 
#define  MIPS_REVISION_SCON_SOCIT 130 
#define  MIPS_REVISION_SCON_SOCITSC 129 
#define  MIPS_REVISION_SCON_SOCITSCP 128 
 int /*<<< orphan*/  MSC01_PCI_IACK ; 
 int /*<<< orphan*/  MSC_READ (int /*<<< orphan*/ ,int) ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 
 scalar_t__ _pcictrl_bonito_pcicfg ; 
 int /*<<< orphan*/  iob () ; 
 int mips_revision_sconid ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 

__attribute__((used)) static inline int mips_pcibios_iack(void)
{
	int irq;

	/*
	 * Determine highest priority pending interrupt by performing
	 * a PCI Interrupt Acknowledge cycle.
	 */
	switch (mips_revision_sconid) {
	case MIPS_REVISION_SCON_SOCIT:
	case MIPS_REVISION_SCON_ROCIT:
	case MIPS_REVISION_SCON_SOCITSC:
	case MIPS_REVISION_SCON_SOCITSCP:
		MSC_READ(MSC01_PCI_IACK, irq);
		irq &= 0xff;
		break;
	case MIPS_REVISION_SCON_GT64120:
		irq = GT_READ(GT_PCI0_IACK_OFS);
		irq &= 0xff;
		break;
	case MIPS_REVISION_SCON_BONITO:
		/* The following will generate a PCI IACK cycle on the
		 * Bonito controller. It's a little bit kludgy, but it
		 * was the easiest way to implement it in hardware at
		 * the given time.
		 */
		BONITO_PCIMAP_CFG = 0x20000;

		/* Flush Bonito register block */
		(void) BONITO_PCIMAP_CFG;
		iob();	  /* sync */

		irq = __raw_readl((u32 *)_pcictrl_bonito_pcicfg);
		iob();	  /* sync */
		irq &= 0xff;
		BONITO_PCIMAP_CFG = 0;
		break;
	default:
		pr_emerg("Unknown system controller.\n");
		return -1;
	}
	return irq;
}