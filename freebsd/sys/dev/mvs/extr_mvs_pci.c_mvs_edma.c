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
struct mvs_controller {scalar_t__ ccc; int pmim; int mim; int gmim; int /*<<< orphan*/  mtx; int /*<<< orphan*/  r_mem; int /*<<< orphan*/  msia; } ;
struct mvs_channel {int unit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CHIP_MIM ; 
 int IC_DONE_IRQ ; 
 int MVS_EDMA_OFF ; 
 struct mvs_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mvs_edma(device_t dev, device_t child, int mode)
{
	struct mvs_controller *ctlr = device_get_softc(dev);
	int unit = ((struct mvs_channel *)device_get_softc(child))->unit;
	int bit = IC_DONE_IRQ << (unit * 2 + unit / 4) ;

	if (ctlr->ccc == 0)
		return;
	/* CCC is not working for non-EDMA mode. Unmask device interrupts. */
	mtx_lock(&ctlr->mtx);
	if (mode == MVS_EDMA_OFF)
		ctlr->pmim |= bit;
	else
		ctlr->pmim &= ~bit;
	ctlr->mim = ctlr->gmim | ctlr->pmim;
	if (!ctlr->msia)
		ATA_OUTL(ctlr->r_mem, CHIP_MIM, ctlr->mim);
	mtx_unlock(&ctlr->mtx);
}