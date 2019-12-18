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
struct uvscom_softc {scalar_t__* sc_xfer; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_super_ucom; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct uvscom_softc*) ; 
 size_t UVSCOM_INTR_DT_RD ; 
 int /*<<< orphan*/  UVSCOM_N_TRANSFER ; 
 int /*<<< orphan*/  device_claim_softc (int /*<<< orphan*/ ) ; 
 struct uvscom_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucom_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_stop (scalar_t__) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvscom_free_softc (struct uvscom_softc*) ; 

__attribute__((used)) static int
uvscom_detach(device_t dev)
{
	struct uvscom_softc *sc = device_get_softc(dev);

	DPRINTF("sc=%p\n", sc);

	/* stop interrupt pipe */

	if (sc->sc_xfer[UVSCOM_INTR_DT_RD])
		usbd_transfer_stop(sc->sc_xfer[UVSCOM_INTR_DT_RD]);

	ucom_detach(&sc->sc_super_ucom, &sc->sc_ucom);
	usbd_transfer_unsetup(sc->sc_xfer, UVSCOM_N_TRANSFER);

	device_claim_softc(dev);

	uvscom_free_softc(sc);

	return (0);
}