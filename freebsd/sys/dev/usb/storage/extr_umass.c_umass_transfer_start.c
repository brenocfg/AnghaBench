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
struct umass_softc {size_t sc_last_xfer_index; scalar_t__* sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  UDMASS_GEN ; 
 int /*<<< orphan*/  umass_cancel_ccb (struct umass_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_start (scalar_t__) ; 

__attribute__((used)) static void
umass_transfer_start(struct umass_softc *sc, uint8_t xfer_index)
{
	DPRINTF(sc, UDMASS_GEN, "transfer index = "
	    "%d\n", xfer_index);

	if (sc->sc_xfer[xfer_index]) {
		sc->sc_last_xfer_index = xfer_index;
		usbd_transfer_start(sc->sc_xfer[xfer_index]);
	} else {
		umass_cancel_ccb(sc);
	}
}