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
struct ieee80211com {int dummy; } ;
struct otus_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/  sc_task; int /*<<< orphan*/  tx_task; int /*<<< orphan*/  calib_to; int /*<<< orphan*/  scan_to; int /*<<< orphan*/  sc_xfer; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OTUS_N_XFER ; 
 struct otus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  otus_close_pipes (struct otus_softc*) ; 
 int /*<<< orphan*/  otus_stop (struct otus_softc*) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  usb_rem_wait_task (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_ref_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
otus_detach(device_t self)
{
	struct otus_softc *sc = device_get_softc(self);
	struct ieee80211com *ic = &sc->sc_ic;

	otus_stop(sc);

	usbd_transfer_unsetup(sc->sc_xfer, OTUS_N_XFER);

	taskqueue_drain_timeout(taskqueue_thread, &sc->scan_to);
	taskqueue_drain_timeout(taskqueue_thread, &sc->calib_to);
	taskqueue_drain(taskqueue_thread, &sc->tx_task);

	otus_close_pipes(sc);
#if 0
	/* Wait for all queued asynchronous commands to complete. */
	usb_rem_wait_task(sc->sc_udev, &sc->sc_task);

	usbd_ref_wait(sc->sc_udev);
#endif

	ieee80211_ifdetach(ic);
	mtx_destroy(&sc->sc_mtx);
	return 0;
}