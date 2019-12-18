#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uhso_softc {int sc_ttys; int /*<<< orphan*/  sc_if_xfer; int /*<<< orphan*/  sc_mtx; TYPE_2__* sc_ifp; int /*<<< orphan*/  sc_c; TYPE_1__* sc_tty; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_ctrl_xfer; int /*<<< orphan*/  sc_xfer; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int /*<<< orphan*/  if_dunit; } ;
struct TYPE_5__ {int ht_muxport; int /*<<< orphan*/  ht_xfer; } ;

/* Variables and functions */
 int UHSO_CTRL_MAX ; 
 int UHSO_IFNET_MAX ; 
 int /*<<< orphan*/  bpfdetach (TYPE_2__*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_claim_softc (int /*<<< orphan*/ ) ; 
 struct uhso_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (TYPE_2__*) ; 
 int /*<<< orphan*/  if_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhso_free_softc (struct uhso_softc*) ; 
 int /*<<< orphan*/  uhso_if_stop (struct uhso_softc*) ; 
 int /*<<< orphan*/  uhso_ifnet_unit ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
uhso_detach(device_t self)
{
	struct uhso_softc *sc = device_get_softc(self);
	int i;

	usbd_transfer_unsetup(sc->sc_xfer, 3);
	usbd_transfer_unsetup(sc->sc_ctrl_xfer, UHSO_CTRL_MAX);
	if (sc->sc_ttys > 0) {
		ucom_detach(&sc->sc_super_ucom, sc->sc_ucom);

		for (i = 0; i < sc->sc_ttys; i++) {
			if (sc->sc_tty[i].ht_muxport != -1) {
				usbd_transfer_unsetup(sc->sc_tty[i].ht_xfer,
				    UHSO_CTRL_MAX);
			}
		}
	}

	if (sc->sc_ifp != NULL) {
		callout_drain(&sc->sc_c);
		free_unr(uhso_ifnet_unit, sc->sc_ifp->if_dunit);
		mtx_lock(&sc->sc_mtx);
		uhso_if_stop(sc);
		bpfdetach(sc->sc_ifp);
		if_detach(sc->sc_ifp);
		if_free(sc->sc_ifp);
		mtx_unlock(&sc->sc_mtx);
		usbd_transfer_unsetup(sc->sc_if_xfer, UHSO_IFNET_MAX);
	}

	device_claim_softc(self);

	uhso_free_softc(sc);

	return (0);
}