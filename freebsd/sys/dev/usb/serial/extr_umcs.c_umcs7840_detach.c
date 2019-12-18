#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct umcs7840_softc {int sc_numports; int /*<<< orphan*/  sc_intr_xfer; TYPE_2__* sc_ucom; TYPE_1__* sc_ports; int /*<<< orphan*/  sc_super_ucom; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {size_t sc_portno; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int UMCS7840_N_TRANSFERS ; 
 int /*<<< orphan*/  device_claim_softc (int /*<<< orphan*/ ) ; 
 struct umcs7840_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucom_detach (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  umcs7840_free_softc (struct umcs7840_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
umcs7840_detach(device_t dev)
{
	struct umcs7840_softc *sc = device_get_softc(dev);
	int subunit;

	ucom_detach(&sc->sc_super_ucom, sc->sc_ucom);

	for (subunit = 0; subunit < sc->sc_numports; ++subunit)
		usbd_transfer_unsetup(sc->sc_ports[sc->sc_ucom[subunit].sc_portno].sc_xfer, UMCS7840_N_TRANSFERS);
	usbd_transfer_unsetup(&sc->sc_intr_xfer, 1);

	device_claim_softc(dev);

	umcs7840_free_softc(sc);

	return (0);
}