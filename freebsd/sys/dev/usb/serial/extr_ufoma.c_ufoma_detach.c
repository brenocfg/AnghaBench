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
struct ufoma_softc {int /*<<< orphan*/  sc_cv; scalar_t__ sc_modetable; int /*<<< orphan*/  sc_bulk_xfer; int /*<<< orphan*/  sc_ctrl_xfer; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_super_ucom; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  UFOMA_BULK_ENDPT_MAX ; 
 int /*<<< orphan*/  UFOMA_CTRL_ENDPT_MAX ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_claim_softc (int /*<<< orphan*/ ) ; 
 struct ufoma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucom_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ufoma_free_softc (struct ufoma_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ufoma_detach(device_t dev)
{
	struct ufoma_softc *sc = device_get_softc(dev);

	ucom_detach(&sc->sc_super_ucom, &sc->sc_ucom);
	usbd_transfer_unsetup(sc->sc_ctrl_xfer, UFOMA_CTRL_ENDPT_MAX);
	usbd_transfer_unsetup(sc->sc_bulk_xfer, UFOMA_BULK_ENDPT_MAX);

	if (sc->sc_modetable) {
		free(sc->sc_modetable, M_USBDEV);
	}
	cv_destroy(&sc->sc_cv);

	device_claim_softc(dev);

	ufoma_free_softc(sc);

	return (0);
}