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
struct ums_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_callout; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_evdev; int /*<<< orphan*/  sc_fifo; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct ums_softc*) ; 
 int /*<<< orphan*/  UMS_N_TRANSFER ; 
 struct ums_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fifo_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ums_detach(device_t self)
{
	struct ums_softc *sc = device_get_softc(self);

	DPRINTF("sc=%p\n", sc);

	usb_fifo_detach(&sc->sc_fifo);

#ifdef EVDEV_SUPPORT
	evdev_free(sc->sc_evdev);
#endif

	usbd_transfer_unsetup(sc->sc_xfer, UMS_N_TRANSFER);

	usb_callout_drain(&sc->sc_callout);

	mtx_destroy(&sc->sc_mtx);

	return (0);
}