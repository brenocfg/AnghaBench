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
typedef  int uint32_t ;
struct TYPE_2__ {int status_bus_reset; int status_suspend; int change_suspend; int change_connect; } ;
struct saf1761_otg_softc {scalar_t__ sc_xfer_complete; int /*<<< orphan*/  sc_bus; TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,int,int) ; 
 int SAF1761_DCINTERRUPT_THREAD_IRQ ; 
 int SAF1761_READ_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAF1761_WRITE_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SOTG_ADDRESS ; 
 int SOTG_ADDRESS_ENABLE ; 
 int /*<<< orphan*/  SOTG_DCINTERRUPT ; 
 int SOTG_DCINTERRUPT_IEBRST ; 
 int SOTG_DCINTERRUPT_IERESM ; 
 int SOTG_DCINTERRUPT_IESUSP ; 
 int SOTG_DCINTERRUPT_IEVBUS ; 
 int /*<<< orphan*/  SOTG_FRAME_NUM ; 
 int /*<<< orphan*/  SOTG_FRINDEX ; 
 int /*<<< orphan*/  SOTG_UNLOCK_DEVICE ; 
 int SOTG_UNLOCK_DEVICE_CODE ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saf1761_otg_interrupt_complete_locked (struct saf1761_otg_softc*) ; 
 int /*<<< orphan*/  saf1761_otg_root_intr (struct saf1761_otg_softc*) ; 
 int /*<<< orphan*/  saf1761_otg_update_vbus (struct saf1761_otg_softc*) ; 
 int /*<<< orphan*/  saf1761_otg_wait_suspend (struct saf1761_otg_softc*,int) ; 

void
saf1761_otg_interrupt(void *arg)
{
	struct saf1761_otg_softc *sc = arg;
	uint32_t status;

	USB_BUS_LOCK(&sc->sc_bus);
	USB_BUS_SPIN_LOCK(&sc->sc_bus);

	status = SAF1761_READ_LE_4(sc, SOTG_DCINTERRUPT) & 
	    SAF1761_DCINTERRUPT_THREAD_IRQ;

	/* acknowledge all device controller interrupts */
	SAF1761_WRITE_LE_4(sc, SOTG_DCINTERRUPT, status);

	DPRINTF("DCINTERRUPT=0x%08x SOF=0x%08x "
	    "FRINDEX=0x%08x\n", status,
	    SAF1761_READ_LE_4(sc, SOTG_FRAME_NUM),
	    SAF1761_READ_LE_4(sc, SOTG_FRINDEX));

	/* update VBUS and ID bits, if any */
	if (status & SOTG_DCINTERRUPT_IEVBUS)
		saf1761_otg_update_vbus(sc);

	if (status & SOTG_DCINTERRUPT_IEBRST) {
		/* unlock device */
		SAF1761_WRITE_LE_4(sc, SOTG_UNLOCK_DEVICE,
		    SOTG_UNLOCK_DEVICE_CODE);

		/* Enable device address */
		SAF1761_WRITE_LE_4(sc, SOTG_ADDRESS,
		    SOTG_ADDRESS_ENABLE);

		sc->sc_flags.status_bus_reset = 1;
		sc->sc_flags.status_suspend = 0;
		sc->sc_flags.change_suspend = 0;
		sc->sc_flags.change_connect = 1;

		/* disable resume interrupt */
		saf1761_otg_wait_suspend(sc, 1);
		/* complete root HUB interrupt endpoint */
		saf1761_otg_root_intr(sc);
	}
	/*
	 * If "RESUME" and "SUSPEND" is set at the same time we
	 * interpret that like "RESUME". Resume is set when there is
	 * at least 3 milliseconds of inactivity on the USB BUS:
	 */
	if (status & SOTG_DCINTERRUPT_IERESM) {
		/* unlock device */
		SAF1761_WRITE_LE_4(sc, SOTG_UNLOCK_DEVICE,
		    SOTG_UNLOCK_DEVICE_CODE);

		if (sc->sc_flags.status_suspend) {
			sc->sc_flags.status_suspend = 0;
			sc->sc_flags.change_suspend = 1;
			/* disable resume interrupt */
			saf1761_otg_wait_suspend(sc, 1);
			/* complete root HUB interrupt endpoint */
			saf1761_otg_root_intr(sc);
		}
	} else if (status & SOTG_DCINTERRUPT_IESUSP) {
		if (!sc->sc_flags.status_suspend) {
			sc->sc_flags.status_suspend = 1;
			sc->sc_flags.change_suspend = 1;
			/* enable resume interrupt */
			saf1761_otg_wait_suspend(sc, 0);
			/* complete root HUB interrupt endpoint */
			saf1761_otg_root_intr(sc);
		}
	}

	if (sc->sc_xfer_complete != 0) {
		sc->sc_xfer_complete = 0;

		/* complete FIFOs, if any */
		saf1761_otg_interrupt_complete_locked(sc);
	}
	USB_BUS_SPIN_UNLOCK(&sc->sc_bus);
	USB_BUS_UNLOCK(&sc->sc_bus);
}