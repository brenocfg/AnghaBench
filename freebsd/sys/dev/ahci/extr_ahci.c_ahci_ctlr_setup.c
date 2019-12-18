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
struct ahci_controller {int ccc; int cccv; int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_CCCC ; 
 int AHCI_CCCC_CC_SHIFT ; 
 int AHCI_CCCC_EN ; 
 int AHCI_CCCC_INT_MASK ; 
 int AHCI_CCCC_INT_SHIFT ; 
 int AHCI_CCCC_TV_SHIFT ; 
 int /*<<< orphan*/  AHCI_CCCP ; 
 int /*<<< orphan*/  AHCI_GHC ; 
 int AHCI_GHC_IE ; 
 int /*<<< orphan*/  AHCI_IS ; 
 int /*<<< orphan*/  AHCI_PI ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 struct ahci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 

int
ahci_ctlr_setup(device_t dev)
{
	struct ahci_controller *ctlr = device_get_softc(dev);
	/* Clear interrupts */
	ATA_OUTL(ctlr->r_mem, AHCI_IS, ATA_INL(ctlr->r_mem, AHCI_IS));
	/* Configure CCC */
	if (ctlr->ccc) {
		ATA_OUTL(ctlr->r_mem, AHCI_CCCP, ATA_INL(ctlr->r_mem, AHCI_PI));
		ATA_OUTL(ctlr->r_mem, AHCI_CCCC,
		    (ctlr->ccc << AHCI_CCCC_TV_SHIFT) |
		    (4 << AHCI_CCCC_CC_SHIFT) |
		    AHCI_CCCC_EN);
		ctlr->cccv = (ATA_INL(ctlr->r_mem, AHCI_CCCC) &
		    AHCI_CCCC_INT_MASK) >> AHCI_CCCC_INT_SHIFT;
		if (bootverbose) {
			device_printf(dev,
			    "CCC with %dms/4cmd enabled on vector %d\n",
			    ctlr->ccc, ctlr->cccv);
		}
	}
	/* Enable AHCI interrupts */
	ATA_OUTL(ctlr->r_mem, AHCI_GHC,
	    ATA_INL(ctlr->r_mem, AHCI_GHC) | AHCI_GHC_IE);
	return (0);
}