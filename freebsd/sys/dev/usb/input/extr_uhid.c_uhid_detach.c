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
struct uhid_softc {int sc_flags; int /*<<< orphan*/  sc_mtx; scalar_t__ sc_repdesc_ptr; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_fifo; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int UHID_FLAG_STATIC_DESC ; 
 int /*<<< orphan*/  UHID_N_TRANSFER ; 
 struct uhid_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fifo_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uhid_detach(device_t dev)
{
	struct uhid_softc *sc = device_get_softc(dev);

	usb_fifo_detach(&sc->sc_fifo);

	usbd_transfer_unsetup(sc->sc_xfer, UHID_N_TRANSFER);

	if (sc->sc_repdesc_ptr) {
		if (!(sc->sc_flags & UHID_FLAG_STATIC_DESC)) {
			free(sc->sc_repdesc_ptr, M_USBDEV);
		}
	}
	mtx_destroy(&sc->sc_mtx);

	return (0);
}