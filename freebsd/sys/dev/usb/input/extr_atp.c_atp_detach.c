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
struct atp_softc {int sc_state; int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_fifo; int /*<<< orphan*/  sc_callout; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATP_ENABLED ; 
 int /*<<< orphan*/  ATP_N_TRANSFER ; 
 int /*<<< orphan*/  HID_MODE ; 
 int /*<<< orphan*/  atp_disable (struct atp_softc*) ; 
 int /*<<< orphan*/  atp_set_device_mode (struct atp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct atp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fifo_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atp_detach(device_t dev)
{
	struct atp_softc *sc;

	sc = device_get_softc(dev);
	atp_set_device_mode(sc, HID_MODE);

	mtx_lock(&sc->sc_mutex);
	callout_drain(&sc->sc_callout);
	if (sc->sc_state & ATP_ENABLED)
		atp_disable(sc);
	mtx_unlock(&sc->sc_mutex);

	usb_fifo_detach(&sc->sc_fifo);

	usbd_transfer_unsetup(sc->sc_xfer, ATP_N_TRANSFER);

	mtx_destroy(&sc->sc_mutex);

	return (0);
}