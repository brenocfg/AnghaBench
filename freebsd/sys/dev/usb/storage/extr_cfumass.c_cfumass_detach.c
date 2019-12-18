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
struct cfumass_softc {int sc_ctl_initid; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFUMASS_DEBUG (struct cfumass_softc*,char*) ; 
 int /*<<< orphan*/  CFUMASS_LOCK (struct cfumass_softc*) ; 
 int /*<<< orphan*/  CFUMASS_T_MAX ; 
 int /*<<< orphan*/  CFUMASS_UNLOCK (struct cfumass_softc*) ; 
 int /*<<< orphan*/  CFUMASS_WARN (struct cfumass_softc*,char*,int) ; 
 int /*<<< orphan*/  cfumass_port ; 
 int /*<<< orphan*/  cfumass_refcount ; 
 int /*<<< orphan*/  cfumass_terminate (struct cfumass_softc*) ; 
 int ctl_remove_initiator (int /*<<< orphan*/ *,int) ; 
 struct cfumass_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cfumass_detach(device_t dev)
{
	struct cfumass_softc *sc;
	int error;

	sc = device_get_softc(dev);

	CFUMASS_DEBUG(sc, "go");

	CFUMASS_LOCK(sc);
	cfumass_terminate(sc);
	CFUMASS_UNLOCK(sc);
	usbd_transfer_unsetup(sc->sc_xfer, CFUMASS_T_MAX);

	if (sc->sc_ctl_initid != -1) {
		error = ctl_remove_initiator(&cfumass_port, sc->sc_ctl_initid);
		if (error != 0) {
			CFUMASS_WARN(sc, "ctl_remove_initiator() failed "
			    "with error %d", error);
		}
		sc->sc_ctl_initid = -1;
	}

	mtx_destroy(&sc->sc_mtx);
	refcount_release(&cfumass_refcount);

	return (0);
}