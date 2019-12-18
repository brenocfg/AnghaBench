#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  bus_mtx; } ;
struct TYPE_3__ {scalar_t__ status_device_mode; int /*<<< orphan*/  status_suspend; } ;
struct dwc_otg_softc {int sc_hprt_val; TYPE_2__ sc_bus; TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int DCTL_RMTWKUPSIG ; 
 int /*<<< orphan*/  DOTG_DCTL ; 
 int /*<<< orphan*/  DOTG_HPRT ; 
 int /*<<< orphan*/  DOTG_PCGCCTL ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int DWC_OTG_READ_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int HPRT_PRTRES ; 
 int HPRT_PRTSUSP ; 
 int /*<<< orphan*/  dwc_otg_resume_irq (struct dwc_otg_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
dwc_otg_wakeup_peer(struct dwc_otg_softc *sc)
{
	if (!sc->sc_flags.status_suspend)
		return;

	DPRINTFN(5, "Remote wakeup\n");

	if (sc->sc_flags.status_device_mode) {
		uint32_t temp;

		/* enable remote wakeup signalling */
		temp = DWC_OTG_READ_4(sc, DOTG_DCTL);
		temp |= DCTL_RMTWKUPSIG;
		DWC_OTG_WRITE_4(sc, DOTG_DCTL, temp);

		/* Wait 8ms for remote wakeup to complete. */
		usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 125);

		temp &= ~DCTL_RMTWKUPSIG;
		DWC_OTG_WRITE_4(sc, DOTG_DCTL, temp);
	} else {
		/* enable USB port */
		DWC_OTG_WRITE_4(sc, DOTG_PCGCCTL, 0);

		/* wait 10ms */
		usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 100);

		/* resume port */
		sc->sc_hprt_val |= HPRT_PRTRES;
		DWC_OTG_WRITE_4(sc, DOTG_HPRT, sc->sc_hprt_val);

		/* Wait 100ms for resume signalling to complete. */
		usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 10);

		/* clear suspend and resume */
		sc->sc_hprt_val &= ~(HPRT_PRTSUSP | HPRT_PRTRES);
		DWC_OTG_WRITE_4(sc, DOTG_HPRT, sc->sc_hprt_val);

		/* Wait 4ms */
		usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 250);
	}

	/* need to fake resume IRQ */
	dwc_otg_resume_irq(sc);
}