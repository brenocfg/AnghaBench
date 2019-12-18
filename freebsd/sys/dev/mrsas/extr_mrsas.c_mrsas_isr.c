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
struct mrsas_softc {int /*<<< orphan*/  reset_flags; int /*<<< orphan*/  msix_vectors; scalar_t__ mask_interrupts; } ;
struct mrsas_irq_context {int /*<<< orphan*/  MSIxIndex; struct mrsas_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MRSAS_FUSION_IN_RESET ; 
 scalar_t__ SUCCESS ; 
 int mrsas_clear_intr (struct mrsas_softc*) ; 
 scalar_t__ mrsas_complete_cmd (struct mrsas_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ mrsas_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
mrsas_isr(void *arg)
{
	struct mrsas_irq_context *irq_context = (struct mrsas_irq_context *)arg;
	struct mrsas_softc *sc = irq_context->sc;
	int status = 0;

	if (sc->mask_interrupts)
		return;

	if (!sc->msix_vectors) {
		status = mrsas_clear_intr(sc);
		if (!status)
			return;
	}
	/* If we are resetting, bail */
	if (mrsas_test_bit(MRSAS_FUSION_IN_RESET, &sc->reset_flags)) {
		printf(" Entered into ISR when OCR is going active. \n");
		mrsas_clear_intr(sc);
		return;
	}
	/* Process for reply request and clear response interrupt */
	if (mrsas_complete_cmd(sc, irq_context->MSIxIndex) != SUCCESS)
		mrsas_clear_intr(sc);

	return;
}