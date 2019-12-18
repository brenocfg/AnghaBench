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
struct cfumass_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFUMASS_LOCK (struct cfumass_softc*) ; 
 int /*<<< orphan*/  CFUMASS_UNLOCK (struct cfumass_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_drain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cfumass_transfer_stop_and_drain(struct cfumass_softc *sc, uint8_t xfer_index)
{

	usbd_transfer_stop(sc->sc_xfer[xfer_index]);
	CFUMASS_UNLOCK(sc);
	usbd_transfer_drain(sc->sc_xfer[xfer_index]);
	CFUMASS_LOCK(sc);
}