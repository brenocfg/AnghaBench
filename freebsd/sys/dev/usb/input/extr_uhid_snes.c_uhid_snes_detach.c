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
struct uhid_snes_softc {int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/  sc_watchdog; int /*<<< orphan*/  sc_transfer; int /*<<< orphan*/  sc_fifo_no_reset; int /*<<< orphan*/  sc_fifo; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  UHID_SNES_N_TRANSFER ; 
 struct uhid_snes_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fifo_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uhid_snes_detach(device_t dev)
{
	struct uhid_snes_softc *sc = device_get_softc(dev);

	usb_fifo_detach(&sc->sc_fifo);
	usb_fifo_detach(&sc->sc_fifo_no_reset);

	mtx_lock(&sc->sc_mutex);
	usb_callout_stop(&sc->sc_watchdog);
	mtx_unlock(&sc->sc_mutex);

	usbd_transfer_unsetup(sc->sc_transfer, UHID_SNES_N_TRANSFER);
	usb_callout_drain(&sc->sc_watchdog);
	mtx_destroy(&sc->sc_mutex);

	return (0);
}