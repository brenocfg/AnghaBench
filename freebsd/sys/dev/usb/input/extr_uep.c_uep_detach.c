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
struct uep_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/  xfer; int /*<<< orphan*/  fifo; int /*<<< orphan*/  evdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  UEP_N_TRANSFER ; 
 struct uep_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fifo_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uep_detach(device_t dev)
{
	struct uep_softc *sc = device_get_softc(dev);

#ifdef EVDEV_SUPPORT
	evdev_free(sc->evdev);
#else
	usb_fifo_detach(&sc->fifo);
#endif

	usbd_transfer_unsetup(sc->xfer, UEP_N_TRANSFER);

	mtx_destroy(&sc->mtx);

	return (0);
}