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
struct mvs_controller {int ccc; int cccc; int channels; int quirks; int gmim; int mim; int pmim; int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ CHIP_ICC ; 
 int CHIP_ICC_ALL_PORTS ; 
 scalar_t__ CHIP_ICT ; 
 scalar_t__ CHIP_ITT ; 
 scalar_t__ CHIP_MIM ; 
 scalar_t__ CHIP_PCIIC ; 
 scalar_t__ CHIP_PCIIM ; 
 scalar_t__ HC_BASE (int) ; 
 scalar_t__ HC_IC ; 
 scalar_t__ HC_ICT ; 
 scalar_t__ HC_ITT ; 
 int IC_ALL_PORTS_COAL_DONE ; 
 int IC_DONE_HC0 ; 
 int IC_DONE_HC1 ; 
 int IC_ERR_HC0 ; 
 int IC_ERR_HC1 ; 
 int IC_HC0_COAL_DONE ; 
 int IC_HC_SHIFT ; 
 int MVS_Q_GENI ; 
 scalar_t__ bootverbose ; 
 struct mvs_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int
mvs_ctlr_setup(device_t dev)
{
	struct mvs_controller *ctlr = device_get_softc(dev);
	int i, ccc = ctlr->ccc, cccc = ctlr->cccc, ccim = 0;

	/* Mask chip interrupts */
	ATA_OUTL(ctlr->r_mem, CHIP_MIM, 0x00000000);
	/* Mask PCI interrupts */
	ATA_OUTL(ctlr->r_mem, CHIP_PCIIM, 0x00000000);
	/* Clear PCI interrupts */
	ATA_OUTL(ctlr->r_mem, CHIP_PCIIC, 0x00000000);
	if (ccc && bootverbose) {
		device_printf(dev,
		    "CCC with %dus/%dcmd enabled\n",
		    ctlr->ccc, ctlr->cccc);
	}
	ccc *= 150;
	/* Configure chip-global CCC */
	if (ctlr->channels > 4 && (ctlr->quirks & MVS_Q_GENI) == 0) {
		ATA_OUTL(ctlr->r_mem, CHIP_ICT, cccc);
		ATA_OUTL(ctlr->r_mem, CHIP_ITT, ccc);
		ATA_OUTL(ctlr->r_mem, CHIP_ICC, ~CHIP_ICC_ALL_PORTS);
		if (ccc)
			ccim |= IC_ALL_PORTS_COAL_DONE;
		ccc = 0;
		cccc = 0;
	}
	for (i = 0; i < ctlr->channels / 4; i++) {
		/* Configure per-HC CCC */
		ATA_OUTL(ctlr->r_mem, HC_BASE(i) + HC_ICT, cccc);
		ATA_OUTL(ctlr->r_mem, HC_BASE(i) + HC_ITT, ccc);
		if (ccc)
			ccim |= (IC_HC0_COAL_DONE << (i * IC_HC_SHIFT));
		/* Clear HC interrupts */
		ATA_OUTL(ctlr->r_mem, HC_BASE(i) + HC_IC, 0x00000000);
	}
	/* Enable chip interrupts */
	ctlr->gmim = (ccim ? ccim : (IC_DONE_HC0 | IC_DONE_HC1)) |
	     IC_ERR_HC0 | IC_ERR_HC1;
	ctlr->mim = ctlr->gmim | ctlr->pmim;
	ATA_OUTL(ctlr->r_mem, CHIP_MIM, ctlr->mim);
	/* Enable PCI interrupts */
	ATA_OUTL(ctlr->r_mem, CHIP_PCIIM, 0x007fffff);
	return (0);
}