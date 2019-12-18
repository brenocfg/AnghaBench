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
struct mvs_controller {int ccc; int cccc; int gmim; int pmim; int /*<<< orphan*/  r_mem; int /*<<< orphan*/  channels; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CHIP_SOC_HC0_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_SOC_MIC ; 
 int /*<<< orphan*/  CHIP_SOC_MIM ; 
 int /*<<< orphan*/  HC_IC ; 
 int /*<<< orphan*/  HC_ICT ; 
 int /*<<< orphan*/  HC_ITT ; 
 int IC_DONE_HC0 ; 
 int IC_ERR_HC0 ; 
 int IC_HC0_COAL_DONE ; 
 scalar_t__ bootverbose ; 
 struct mvs_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int
mvs_ctlr_setup(device_t dev)
{
	struct mvs_controller *ctlr = device_get_softc(dev);
	int ccc = ctlr->ccc, cccc = ctlr->cccc, ccim = 0;

	/* Mask chip interrupts */
	ATA_OUTL(ctlr->r_mem, CHIP_SOC_MIM, 0x00000000);
	/* Clear HC interrupts */
	ATA_OUTL(ctlr->r_mem, HC_IC, 0x00000000);
	/* Clear chip interrupts */
	ATA_OUTL(ctlr->r_mem, CHIP_SOC_MIC, 0);
	/* Configure per-HC CCC */
	if (ccc && bootverbose) {
		device_printf(dev,
		    "CCC with %dus/%dcmd enabled\n",
		    ctlr->ccc, ctlr->cccc);
	}
	ccc *= 150;
	ATA_OUTL(ctlr->r_mem, HC_ICT, cccc);
	ATA_OUTL(ctlr->r_mem, HC_ITT, ccc);
	if (ccc)
		ccim |= IC_HC0_COAL_DONE;
	/* Enable chip interrupts */
	ctlr->gmim = ((ccc ? IC_HC0_COAL_DONE :
	    (IC_DONE_HC0 & CHIP_SOC_HC0_MASK(ctlr->channels))) |
	    (IC_ERR_HC0 & CHIP_SOC_HC0_MASK(ctlr->channels)));
	ATA_OUTL(ctlr->r_mem, CHIP_SOC_MIM, ctlr->gmim | ctlr->pmim);
	return (0);
}