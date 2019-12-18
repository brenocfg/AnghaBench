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
struct TYPE_2__ {int change_suspend; scalar_t__ status_device_mode; scalar_t__ status_suspend; } ;
struct dwc_otg_softc {int /*<<< orphan*/  sc_irq_mask; TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOTG_GINTMSK ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GINTMSK_USBSUSPMSK ; 
 int /*<<< orphan*/  GINTMSK_WKUPINTMSK ; 
 int /*<<< orphan*/  dwc_otg_root_intr (struct dwc_otg_softc*) ; 

__attribute__((used)) static void
dwc_otg_resume_irq(struct dwc_otg_softc *sc)
{
	if (sc->sc_flags.status_suspend) {
		/* update status bits */
		sc->sc_flags.status_suspend = 0;
		sc->sc_flags.change_suspend = 1;

		if (sc->sc_flags.status_device_mode) {
			/*
			 * Disable resume interrupt and enable suspend
			 * interrupt:
			 */
			sc->sc_irq_mask &= ~GINTMSK_WKUPINTMSK;
			sc->sc_irq_mask |= GINTMSK_USBSUSPMSK;
			DWC_OTG_WRITE_4(sc, DOTG_GINTMSK, sc->sc_irq_mask);
		}

		/* complete root HUB interrupt endpoint */
		dwc_otg_root_intr(sc);
	}
}