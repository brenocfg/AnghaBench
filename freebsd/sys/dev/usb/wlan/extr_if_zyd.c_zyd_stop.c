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
struct zyd_softc {int sc_flags; int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 size_t ZYD_BULK_RD ; 
 size_t ZYD_BULK_WR ; 
 int /*<<< orphan*/  ZYD_CR_INTERRUPT ; 
 int ZYD_FLAG_INITONCE ; 
 int ZYD_FLAG_RUNNING ; 
 int /*<<< orphan*/  ZYD_LOCK (struct zyd_softc*) ; 
 int /*<<< orphan*/  ZYD_LOCK_ASSERT (struct zyd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZYD_MAC_RXFILTER ; 
 int /*<<< orphan*/  ZYD_UNLOCK (struct zyd_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_drain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zyd_drain_mbufq (struct zyd_softc*) ; 
 int zyd_switch_radio (struct zyd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zyd_unsetup_tx_list (struct zyd_softc*) ; 
 int /*<<< orphan*/  zyd_write32_m (struct zyd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zyd_stop(struct zyd_softc *sc)
{
	int error;

	ZYD_LOCK_ASSERT(sc, MA_OWNED);

	sc->sc_flags &= ~ZYD_FLAG_RUNNING;
	zyd_drain_mbufq(sc);

	/*
	 * Drain all the transfers, if not already drained:
	 */
	ZYD_UNLOCK(sc);
	usbd_transfer_drain(sc->sc_xfer[ZYD_BULK_WR]);
	usbd_transfer_drain(sc->sc_xfer[ZYD_BULK_RD]);
	ZYD_LOCK(sc);

	zyd_unsetup_tx_list(sc);

	/* Stop now if the device was never set up */
	if (!(sc->sc_flags & ZYD_FLAG_INITONCE))
		return;

	/* switch radio transmitter OFF */
	error = zyd_switch_radio(sc, 0);
	if (error != 0)
		goto fail;
	/* disable Rx */
	zyd_write32_m(sc, ZYD_MAC_RXFILTER, 0);
	/* disable interrupts */
	zyd_write32_m(sc, ZYD_CR_INTERRUPT, 0);

fail:
	return;
}