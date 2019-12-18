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
struct TYPE_2__ {scalar_t__ status_device_mode; } ;
struct dwc_otg_softc {int sc_needsof; int sc_irq_mask; TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOTG_GINTMSK ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int GINTMSK_SOFMSK ; 

__attribute__((used)) static void
dwc_otg_enable_sof_irq(struct dwc_otg_softc *sc)
{
	/* In device mode we don't use the SOF interrupt */
	if (sc->sc_flags.status_device_mode != 0)
		return;
	/* Ensure the SOF interrupt is not disabled */
	sc->sc_needsof = 1;
	/* Check if the SOF interrupt is already enabled */
	if ((sc->sc_irq_mask & GINTMSK_SOFMSK) != 0)
		return;
	sc->sc_irq_mask |= GINTMSK_SOFMSK;
	DWC_OTG_WRITE_4(sc, DOTG_GINTMSK, sc->sc_irq_mask);
}