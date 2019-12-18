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
struct atmegadci_softc {TYPE_1__ sc_bus; int /*<<< orphan*/  (* sc_clocks_on ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int ATMEGA_EP_MAX ; 
 int ATMEGA_READ_1 (struct atmegadci_softc*,int) ; 
 int ATMEGA_UDCON ; 
 int ATMEGA_UDCON_DETACH ; 
 int ATMEGA_UDIEN ; 
 int ATMEGA_UDINT_EORSTE ; 
 int ATMEGA_UDINT_SUSPE ; 
 int ATMEGA_UECONX ; 
 int ATMEGA_UEIENX ; 
 int ATMEGA_UENUM ; 
 int ATMEGA_UERST ; 
 int ATMEGA_UHWCON ; 
 int ATMEGA_UHWCON_UIMOD ; 
 int ATMEGA_UHWCON_UVREGE ; 
 int ATMEGA_USBCON ; 
 int ATMEGA_USBCON_FRZCLK ; 
 int ATMEGA_USBCON_OTGPADE ; 
 int ATMEGA_USBCON_USBE ; 
 int ATMEGA_USBCON_VBUSTE ; 
 int ATMEGA_USBSTA ; 
 int ATMEGA_USBSTA_VBUS ; 
 int /*<<< orphan*/  ATMEGA_WRITE_1 (struct atmegadci_softc*,int,int) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  USB_REV_1_1 ; 
 int /*<<< orphan*/  atmegadci_bus_methods ; 
 int /*<<< orphan*/  atmegadci_clocks_off (struct atmegadci_softc*) ; 
 int /*<<< orphan*/  atmegadci_do_poll (TYPE_1__*) ; 
 int /*<<< orphan*/  atmegadci_vbus_interrupt (struct atmegadci_softc*,int) ; 
 int hz ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

usb_error_t
atmegadci_init(struct atmegadci_softc *sc)
{
	uint8_t n;

	DPRINTF("start\n");

	/* set up the bus structure */
	sc->sc_bus.usbrev = USB_REV_1_1;
	sc->sc_bus.methods = &atmegadci_bus_methods;

	USB_BUS_LOCK(&sc->sc_bus);

	/* make sure USB is enabled */
	ATMEGA_WRITE_1(sc, ATMEGA_USBCON,
	    ATMEGA_USBCON_USBE |
	    ATMEGA_USBCON_FRZCLK);

	/* enable USB PAD regulator */
	ATMEGA_WRITE_1(sc, ATMEGA_UHWCON,
	    ATMEGA_UHWCON_UVREGE |
	    ATMEGA_UHWCON_UIMOD);

	/* the following register sets up the USB PLL, assuming 16MHz X-tal */
	ATMEGA_WRITE_1(sc, 0x49 /* PLLCSR */, 0x14 | 0x02);

	/* wait for PLL to lock */
	for (n = 0; n != 20; n++) {
		if (ATMEGA_READ_1(sc, 0x49) & 0x01)
			break;
		/* wait a little bit for PLL to start */
		usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 100);
	}

	/* make sure USB is enabled */
	ATMEGA_WRITE_1(sc, ATMEGA_USBCON,
	    ATMEGA_USBCON_USBE |
	    ATMEGA_USBCON_OTGPADE |
	    ATMEGA_USBCON_VBUSTE);

	/* turn on clocks */
	(sc->sc_clocks_on) (&sc->sc_bus);

	/* make sure device is re-enumerated */
	ATMEGA_WRITE_1(sc, ATMEGA_UDCON, ATMEGA_UDCON_DETACH);

	/* wait a little for things to stabilise */
	usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 20);

	/* enable interrupts */
	ATMEGA_WRITE_1(sc, ATMEGA_UDIEN,
	    ATMEGA_UDINT_SUSPE |
	    ATMEGA_UDINT_EORSTE);

	/* reset all endpoints */
	ATMEGA_WRITE_1(sc, ATMEGA_UERST,
	    (1 << ATMEGA_EP_MAX) - 1);

	/* disable reset */
	ATMEGA_WRITE_1(sc, ATMEGA_UERST, 0);

	/* disable all endpoints */
	for (n = 0; n != ATMEGA_EP_MAX; n++) {

		/* select endpoint */
		ATMEGA_WRITE_1(sc, ATMEGA_UENUM, n);

		/* disable endpoint interrupt */
		ATMEGA_WRITE_1(sc, ATMEGA_UEIENX, 0);

		/* disable endpoint */
		ATMEGA_WRITE_1(sc, ATMEGA_UECONX, 0);
	}

	/* turn off clocks */

	atmegadci_clocks_off(sc);

	/* read initial VBUS state */

	n = ATMEGA_READ_1(sc, ATMEGA_USBSTA);
	atmegadci_vbus_interrupt(sc, n & ATMEGA_USBSTA_VBUS);

	USB_BUS_UNLOCK(&sc->sc_bus);

	/* catch any lost interrupts */

	atmegadci_do_poll(&sc->sc_bus);

	return (0);			/* success */
}