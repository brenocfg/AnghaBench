#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct ugensa_softc {size_t sc_nports; TYPE_1__* sc_sub; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_super_ucom; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  UGENSA_N_TRANSFER ; 
 int /*<<< orphan*/  device_claim_softc (int /*<<< orphan*/ ) ; 
 struct ugensa_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucom_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ugensa_free_softc (struct ugensa_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ugensa_detach(device_t dev)
{
	struct ugensa_softc *sc = device_get_softc(dev);
	uint8_t x;

	ucom_detach(&sc->sc_super_ucom, sc->sc_ucom);

	for (x = 0; x < sc->sc_nports; x++) {
		usbd_transfer_unsetup(sc->sc_sub[x].sc_xfer, UGENSA_N_TRANSFER);
	}

	device_claim_softc(dev);

	ugensa_free_softc(sc);

	return (0);
}