#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  bus_mtx; int /*<<< orphan*/ * methods; int /*<<< orphan*/  usbrev; } ;
struct avr32dci_softc {TYPE_1__ sc_bus; int /*<<< orphan*/  (* sc_clocks_on ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AVR32_CTRL_DEV_DETACH ; 
 int /*<<< orphan*/  AVR32_CTRL_DEV_EN_USBA ; 
 int /*<<< orphan*/  AVR32_EPTCTLDIS (int) ; 
 int AVR32_EPTCTL_EPT_ENABL ; 
 int /*<<< orphan*/  AVR32_EPTRST ; 
 int AVR32_EP_MAX ; 
 int AVR32_INT_DET_SUSPD ; 
 int AVR32_INT_ENDRESET ; 
 int /*<<< orphan*/  AVR32_WRITE_4 (struct avr32dci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  USB_REV_1_1 ; 
 int /*<<< orphan*/  avr32dci_bus_methods ; 
 int /*<<< orphan*/  avr32dci_clocks_off (struct avr32dci_softc*) ; 
 int /*<<< orphan*/  avr32dci_do_poll (TYPE_1__*) ; 
 int /*<<< orphan*/  avr32dci_mod_ctrl (struct avr32dci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avr32dci_mod_ien (struct avr32dci_softc*,int,int) ; 
 int hz ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

usb_error_t
avr32dci_init(struct avr32dci_softc *sc)
{
	uint8_t n;

	DPRINTF("start\n");

	/* set up the bus structure */
	sc->sc_bus.usbrev = USB_REV_1_1;
	sc->sc_bus.methods = &avr32dci_bus_methods;

	USB_BUS_LOCK(&sc->sc_bus);

	/* make sure USB is enabled */
	avr32dci_mod_ctrl(sc, AVR32_CTRL_DEV_EN_USBA, 0);

	/* turn on clocks */
	(sc->sc_clocks_on) (&sc->sc_bus);

	/* make sure device is re-enumerated */
	avr32dci_mod_ctrl(sc, AVR32_CTRL_DEV_DETACH, 0);

	/* wait a little for things to stabilise */
	usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 20);

	/* disable interrupts */
	avr32dci_mod_ien(sc, 0, 0xFFFFFFFF);

	/* enable interrupts */
	avr32dci_mod_ien(sc, AVR32_INT_DET_SUSPD |
	    AVR32_INT_ENDRESET, 0);

	/* reset all endpoints */
	AVR32_WRITE_4(sc, AVR32_EPTRST, (1 << AVR32_EP_MAX) - 1);

	/* disable all endpoints */
	for (n = 0; n != AVR32_EP_MAX; n++) {
		/* disable endpoint */
		AVR32_WRITE_4(sc, AVR32_EPTCTLDIS(n), AVR32_EPTCTL_EPT_ENABL);
	}

	/* turn off clocks */

	avr32dci_clocks_off(sc);

	USB_BUS_UNLOCK(&sc->sc_bus);

	/* catch any lost interrupts */

	avr32dci_do_poll(&sc->sc_bus);

	return (0);			/* success */
}