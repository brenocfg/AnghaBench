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
struct umass_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UDMASS_USB ; 
 int /*<<< orphan*/  UMASS_T_MAX ; 
 struct umass_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umass_cam_detach_sim (struct umass_softc*) ; 
 int /*<<< orphan*/  umass_cancel_ccb (struct umass_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
umass_detach(device_t dev)
{
	struct umass_softc *sc = device_get_softc(dev);

	DPRINTF(sc, UDMASS_USB, "\n");

	/* teardown our statemachine */

	usbd_transfer_unsetup(sc->sc_xfer, UMASS_T_MAX);

	mtx_lock(&sc->sc_mtx);

	/* cancel any leftover CCB's */

	umass_cancel_ccb(sc);

	umass_cam_detach_sim(sc);

	mtx_unlock(&sc->sc_mtx);

	mtx_destroy(&sc->sc_mtx);

	return (0);			/* success */
}