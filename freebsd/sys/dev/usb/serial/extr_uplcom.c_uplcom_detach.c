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
struct uplcom_softc {int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_super_ucom; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct uplcom_softc*) ; 
 int /*<<< orphan*/  UPLCOM_N_TRANSFER ; 
 int /*<<< orphan*/  device_claim_softc (int /*<<< orphan*/ ) ; 
 struct uplcom_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucom_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uplcom_free_softc (struct uplcom_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uplcom_detach(device_t dev)
{
	struct uplcom_softc *sc = device_get_softc(dev);

	DPRINTF("sc=%p\n", sc);

	ucom_detach(&sc->sc_super_ucom, &sc->sc_ucom);
	usbd_transfer_unsetup(sc->sc_xfer, UPLCOM_N_TRANSFER);

	device_claim_softc(dev);

	uplcom_free_softc(sc);

	return (0);
}