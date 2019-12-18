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
struct ugold_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/ * sc_readout_msg; int /*<<< orphan*/  sc_callout; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  UGOLD_N_TRANSFER ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct ugold_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_proc_explore_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_proc_explore_mwait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_proc_explore_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ugold_detach(device_t dev)
{
	struct ugold_softc *sc = device_get_softc(dev);

	callout_drain(&sc->sc_callout);

	usb_proc_explore_lock(sc->sc_udev);
	usb_proc_explore_mwait(sc->sc_udev,
	    &sc->sc_readout_msg[0], &sc->sc_readout_msg[1]);
	usb_proc_explore_unlock(sc->sc_udev);

	usbd_transfer_unsetup(sc->sc_xfer, UGOLD_N_TRANSFER);

	mtx_destroy(&sc->sc_mtx);

	return (0);
}