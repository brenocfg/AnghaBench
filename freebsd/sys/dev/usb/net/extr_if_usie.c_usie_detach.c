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
typedef  size_t uint8_t ;
struct usie_softc {scalar_t__ sc_nucom; int /*<<< orphan*/ * sc_uc_xfer; int /*<<< orphan*/  sc_if_xfer; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/ * sc_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  USIE_IF_N_XFER ; 
 size_t USIE_UCOM_MAX ; 
 int /*<<< orphan*/  USIE_UC_N_XFER ; 
 int /*<<< orphan*/  bpfdetach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_claim_softc (int /*<<< orphan*/ ) ; 
 struct usie_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usie_free_softc (struct usie_softc*) ; 
 int /*<<< orphan*/  usie_if_stop (struct usie_softc*) ; 

__attribute__((used)) static int
usie_detach(device_t self)
{
	struct usie_softc *sc = device_get_softc(self);
	uint8_t x;

	/* detach ifnet */
	if (sc->sc_ifp != NULL) {
		usie_if_stop(sc);
		usbd_transfer_unsetup(sc->sc_if_xfer, USIE_IF_N_XFER);
		bpfdetach(sc->sc_ifp);
		if_detach(sc->sc_ifp);
		if_free(sc->sc_ifp);
		sc->sc_ifp = NULL;
	}
	/* detach ucom */
	if (sc->sc_nucom > 0)
		ucom_detach(&sc->sc_super_ucom, sc->sc_ucom);

	/* stop all USB transfers */
	usbd_transfer_unsetup(sc->sc_if_xfer, USIE_IF_N_XFER);

	for (x = 0; x != USIE_UCOM_MAX; x++)
		usbd_transfer_unsetup(sc->sc_uc_xfer[x], USIE_UC_N_XFER);


	device_claim_softc(self);

	usie_free_softc(sc);

	return (0);
}