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
struct u3g_softc {int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_super_ucom; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct u3g_softc*) ; 
 size_t U3G_MAXPORTS ; 
 int /*<<< orphan*/  U3G_N_TRANSFER ; 
 int /*<<< orphan*/  device_claim_softc (int /*<<< orphan*/ ) ; 
 struct u3g_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u3g_free_softc (struct u3g_softc*) ; 
 int /*<<< orphan*/  ucom_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
u3g_detach(device_t dev)
{
	struct u3g_softc *sc = device_get_softc(dev);
	uint8_t subunit;

	DPRINTF("sc=%p\n", sc);

	/* NOTE: It is not dangerous to detach more ports than attached! */
	ucom_detach(&sc->sc_super_ucom, sc->sc_ucom);

	for (subunit = 0; subunit != U3G_MAXPORTS; subunit++)
		usbd_transfer_unsetup(sc->sc_xfer[subunit], U3G_N_TRANSFER);

	device_claim_softc(dev);

	u3g_free_softc(sc);

	return (0);
}