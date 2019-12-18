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
struct ural_softc {int /*<<< orphan*/ * sc_xfer; scalar_t__ sc_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int RAL_DISABLE_RX ; 
 int /*<<< orphan*/  RAL_LOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  RAL_LOCK_ASSERT (struct ural_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_MAC_CSR1 ; 
 int RAL_RESET_ASIC ; 
 int RAL_RESET_BBP ; 
 int /*<<< orphan*/  RAL_TXRX_CSR2 ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct ural_softc*) ; 
 size_t URAL_BULK_RD ; 
 size_t URAL_BULK_WR ; 
 int hz ; 
 int /*<<< orphan*/  ural_pause (struct ural_softc*,int) ; 
 int /*<<< orphan*/  ural_unsetup_tx_list (struct ural_softc*) ; 
 int /*<<< orphan*/  ural_write (struct ural_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_transfer_drain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ural_stop(struct ural_softc *sc)
{

	RAL_LOCK_ASSERT(sc, MA_OWNED);

	sc->sc_running = 0;

	/*
	 * Drain all the transfers, if not already drained:
	 */
	RAL_UNLOCK(sc);
	usbd_transfer_drain(sc->sc_xfer[URAL_BULK_WR]);
	usbd_transfer_drain(sc->sc_xfer[URAL_BULK_RD]);
	RAL_LOCK(sc);

	ural_unsetup_tx_list(sc);

	/* disable Rx */
	ural_write(sc, RAL_TXRX_CSR2, RAL_DISABLE_RX);
	/* reset ASIC and BBP (but won't reset MAC registers!) */
	ural_write(sc, RAL_MAC_CSR1, RAL_RESET_ASIC | RAL_RESET_BBP);
	/* wait a little */
	ural_pause(sc, hz / 10);
	ural_write(sc, RAL_MAC_CSR1, 0);
	/* wait a little */
	ural_pause(sc, hz / 10);
}