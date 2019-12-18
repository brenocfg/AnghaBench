#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  bus_mtx; } ;
struct TYPE_8__ {int sc_isreset; TYPE_1__ sc_bus; } ;
typedef  TYPE_2__ uhci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int,...) ; 
 int UHCI_PORTSC1 ; 
 int UHCI_PORTSC2 ; 
 int UHCI_PORTSC_CCS ; 
 int UHCI_PORTSC_CSC ; 
 int UHCI_PORTSC_PE ; 
 int UHCI_PORTSC_POEDC ; 
 int UHCI_PORTSC_PR ; 
 int UREAD2 (TYPE_2__*,int) ; 
 int URWMASK (int) ; 
 int /*<<< orphan*/  USB_ERR_IOERROR ; 
 int /*<<< orphan*/  USB_ERR_NORMAL_COMPLETION ; 
 int /*<<< orphan*/  USB_ERR_TIMEOUT ; 
 int /*<<< orphan*/  USB_MS_TO_TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UWRITE2 (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uhci_restart (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_port_reset_delay ; 
 int /*<<< orphan*/  usb_port_root_reset_delay ; 

__attribute__((used)) static usb_error_t
uhci_portreset(uhci_softc_t *sc, uint16_t index)
{
	uint16_t port;
	uint16_t x;
	uint8_t lim;

	if (index == 1)
		port = UHCI_PORTSC1;
	else if (index == 2)
		port = UHCI_PORTSC2;
	else
		return (USB_ERR_IOERROR);

	/*
	 * Before we do anything, turn on SOF messages on the USB
	 * BUS. Some USB devices do not cope without them!
	 */
	uhci_restart(sc);

	x = URWMASK(UREAD2(sc, port));
	UWRITE2(sc, port, x | UHCI_PORTSC_PR);

	usb_pause_mtx(&sc->sc_bus.bus_mtx,
	    USB_MS_TO_TICKS(usb_port_root_reset_delay));

	DPRINTFN(4, "uhci port %d reset, status0 = 0x%04x\n",
	    index, UREAD2(sc, port));

	x = URWMASK(UREAD2(sc, port));
	UWRITE2(sc, port, x & ~UHCI_PORTSC_PR);


	mtx_unlock(&sc->sc_bus.bus_mtx);

	/* 
	 * This delay needs to be exactly 100us, else some USB devices
	 * fail to attach!
	 */
	DELAY(100);

	mtx_lock(&sc->sc_bus.bus_mtx);

	DPRINTFN(4, "uhci port %d reset, status1 = 0x%04x\n",
	    index, UREAD2(sc, port));

	x = URWMASK(UREAD2(sc, port));
	UWRITE2(sc, port, x | UHCI_PORTSC_PE);

	for (lim = 0; lim < 12; lim++) {

		usb_pause_mtx(&sc->sc_bus.bus_mtx,
		    USB_MS_TO_TICKS(usb_port_reset_delay));

		x = UREAD2(sc, port);

		DPRINTFN(4, "uhci port %d iteration %u, status = 0x%04x\n",
		    index, lim, x);

		if (!(x & UHCI_PORTSC_CCS)) {
			/*
			 * No device is connected (or was disconnected
			 * during reset).  Consider the port reset.
			 * The delay must be long enough to ensure on
			 * the initial iteration that the device
			 * connection will have been registered.  50ms
			 * appears to be sufficient, but 20ms is not.
			 */
			DPRINTFN(4, "uhci port %d loop %u, device detached\n",
			    index, lim);
			goto done;
		}
		if (x & (UHCI_PORTSC_POEDC | UHCI_PORTSC_CSC)) {
			/*
			 * Port enabled changed and/or connection
			 * status changed were set.  Reset either or
			 * both raised flags (by writing a 1 to that
			 * bit), and wait again for state to settle.
			 */
			UWRITE2(sc, port, URWMASK(x) |
			    (x & (UHCI_PORTSC_POEDC | UHCI_PORTSC_CSC)));
			continue;
		}
		if (x & UHCI_PORTSC_PE) {
			/* port is enabled */
			goto done;
		}
		UWRITE2(sc, port, URWMASK(x) | UHCI_PORTSC_PE);
	}

	DPRINTFN(2, "uhci port %d reset timed out\n", index);
	return (USB_ERR_TIMEOUT);

done:
	DPRINTFN(4, "uhci port %d reset, status2 = 0x%04x\n",
	    index, UREAD2(sc, port));

	sc->sc_isreset = 1;
	return (USB_ERR_NORMAL_COMPLETION);
}