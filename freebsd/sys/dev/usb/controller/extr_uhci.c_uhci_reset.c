#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_11__ {int /*<<< orphan*/  bdev; int /*<<< orphan*/  bus_mtx; } ;
struct TYPE_10__ {TYPE_5__ sc_bus; int /*<<< orphan*/  sc_root_intr; } ;
typedef  TYPE_1__ uhci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  UHCICMD (TYPE_1__*,int) ; 
 int /*<<< orphan*/  UHCI_CMD ; 
 int UHCI_CMD_GRESET ; 
 int UHCI_CMD_HCRESET ; 
 int /*<<< orphan*/  UHCI_FRNUM ; 
 int /*<<< orphan*/  UHCI_INTR ; 
 int UHCI_RESET_TIMEOUT ; 
 int /*<<< orphan*/  UHCI_SOF ; 
 int /*<<< orphan*/  UHCI_STS ; 
 int UHCI_STS_HCH ; 
 int UREAD2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_RESET_DELAY ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (TYPE_5__*) ; 
 int USB_MS_TO_TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UWRITE1 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UWRITE2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

void
uhci_reset(uhci_softc_t *sc)
{
	uint16_t n;

	USB_BUS_LOCK_ASSERT(&sc->sc_bus, MA_OWNED);

	DPRINTF("resetting the HC\n");

	/* disable interrupts */

	UWRITE2(sc, UHCI_INTR, 0);

	/* global reset */

	UHCICMD(sc, UHCI_CMD_GRESET);

	/* wait */

	usb_pause_mtx(&sc->sc_bus.bus_mtx,
	    USB_MS_TO_TICKS(USB_BUS_RESET_DELAY));

	/* terminate all transfers */

	UHCICMD(sc, UHCI_CMD_HCRESET);

	/* the reset bit goes low when the controller is done */

	n = UHCI_RESET_TIMEOUT;
	while (n--) {
		/* wait one millisecond */

		usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 1000);

		if (!(UREAD2(sc, UHCI_CMD) & UHCI_CMD_HCRESET)) {
			goto done_1;
		}
	}

	device_printf(sc->sc_bus.bdev,
	    "controller did not reset\n");

done_1:

	n = 10;
	while (n--) {
		/* wait one millisecond */

		usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 1000);

		/* check if HC is stopped */
		if (UREAD2(sc, UHCI_STS) & UHCI_STS_HCH) {
			goto done_2;
		}
	}

	device_printf(sc->sc_bus.bdev,
	    "controller did not stop\n");

done_2:

	/* reset frame number */
	UWRITE2(sc, UHCI_FRNUM, 0);
	/* set default SOF value */
	UWRITE1(sc, UHCI_SOF, 0x40);

	USB_BUS_UNLOCK(&sc->sc_bus);

	/* stop root interrupt */
	usb_callout_drain(&sc->sc_root_intr);

	USB_BUS_LOCK(&sc->sc_bus);
}