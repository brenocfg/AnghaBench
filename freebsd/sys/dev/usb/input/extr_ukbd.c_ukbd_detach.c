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
struct TYPE_5__ {scalar_t__ kb_flags; } ;
struct ukbd_softc {int sc_flags; int /*<<< orphan*/  sc_callout; int /*<<< orphan*/ * sc_xfer; TYPE_1__ sc_kbd; int /*<<< orphan*/  sc_evdev; int /*<<< orphan*/  sc_ndata; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 scalar_t__ KBD_IS_CONFIGURED (TYPE_1__*) ; 
 int UKBD_FLAG_ATTACHED ; 
 int UKBD_FLAG_GONE ; 
 size_t UKBD_INTR_DT_0 ; 
 size_t UKBD_INTR_DT_1 ; 
 int /*<<< orphan*/  UKBD_LOCK_ASSERT () ; 
 int /*<<< orphan*/  UKBD_N_TRANSFER ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ukbd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evdev_free (int /*<<< orphan*/ ) ; 
 int kbd_detach (TYPE_1__*) ; 
 int kbd_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ukbd_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  ukbd_interrupt (struct ukbd_softc*) ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ukbd_detach(device_t dev)
{
	struct ukbd_softc *sc = device_get_softc(dev);
	int error;

	UKBD_LOCK_ASSERT();

	DPRINTF("\n");

	sc->sc_flags |= UKBD_FLAG_GONE;

	usb_callout_stop(&sc->sc_callout);

	/* kill any stuck keys */
	if (sc->sc_flags & UKBD_FLAG_ATTACHED) {
		/* stop receiving events from the USB keyboard */
		usbd_transfer_stop(sc->sc_xfer[UKBD_INTR_DT_0]);
		usbd_transfer_stop(sc->sc_xfer[UKBD_INTR_DT_1]);

		/* release all leftover keys, if any */
		memset(&sc->sc_ndata, 0, sizeof(sc->sc_ndata));

		/* process releasing of all keys */
		ukbd_interrupt(sc);
	}

	ukbd_disable(&sc->sc_kbd);

#ifdef KBD_INSTALL_CDEV
	if (sc->sc_flags & UKBD_FLAG_ATTACHED) {
		error = kbd_detach(&sc->sc_kbd);
		if (error) {
			/* usb attach cannot return an error */
			device_printf(dev, "WARNING: kbd_detach() "
			    "returned non-zero! (ignored)\n");
		}
	}
#endif

#ifdef EVDEV_SUPPORT
	evdev_free(sc->sc_evdev);
#endif

	if (KBD_IS_CONFIGURED(&sc->sc_kbd)) {
		error = kbd_unregister(&sc->sc_kbd);
		if (error) {
			/* usb attach cannot return an error */
			device_printf(dev, "WARNING: kbd_unregister() "
			    "returned non-zero! (ignored)\n");
		}
	}
	sc->sc_kbd.kb_flags = 0;

	usbd_transfer_unsetup(sc->sc_xfer, UKBD_N_TRANSFER);

	usb_callout_drain(&sc->sc_callout);

	DPRINTF("%s: disconnected\n",
	    device_get_nameunit(dev));

	return (0);
}