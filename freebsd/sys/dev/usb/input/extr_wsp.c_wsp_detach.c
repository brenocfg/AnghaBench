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
struct wsp_softc {int sc_state; int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_fifo; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int WSP_ENABLED ; 
 int /*<<< orphan*/  WSP_N_TRANSFER ; 
 struct wsp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fifo_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsp_disable (struct wsp_softc*) ; 
 int /*<<< orphan*/  wsp_set_device_mode (struct wsp_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wsp_detach(device_t dev)
{
	struct wsp_softc *sc = device_get_softc(dev);

	(void) wsp_set_device_mode(sc, 0);

	mtx_lock(&sc->sc_mutex);
	if (sc->sc_state & WSP_ENABLED)
		wsp_disable(sc);
	mtx_unlock(&sc->sc_mutex);

	usb_fifo_detach(&sc->sc_fifo);

	usbd_transfer_unsetup(sc->sc_xfer, WSP_N_TRANSFER);

	mtx_destroy(&sc->sc_mutex);

	return (0);
}