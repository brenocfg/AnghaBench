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
struct rum_softc {int /*<<< orphan*/ * sc_xfer; scalar_t__ sc_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT2573_DISABLE_RX ; 
 int /*<<< orphan*/  RT2573_MAC_CSR1 ; 
 int RT2573_RESET_ASIC ; 
 int RT2573_RESET_BBP ; 
 int /*<<< orphan*/  RT2573_TXRX_CSR0 ; 
 size_t RUM_BULK_RD ; 
 size_t RUM_BULK_WR ; 
 int /*<<< orphan*/  RUM_LOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_UNLOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  rum_setbits (struct rum_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rum_unsetup_tx_list (struct rum_softc*) ; 
 int /*<<< orphan*/  rum_write (struct rum_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_transfer_drain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rum_stop(struct rum_softc *sc)
{

	RUM_LOCK(sc);
	if (!sc->sc_running) {
		RUM_UNLOCK(sc);
		return;
	}
	sc->sc_running = 0;
	RUM_UNLOCK(sc);

	/*
	 * Drain the USB transfers, if not already drained:
	 */
	usbd_transfer_drain(sc->sc_xfer[RUM_BULK_WR]);
	usbd_transfer_drain(sc->sc_xfer[RUM_BULK_RD]);

	RUM_LOCK(sc);
	rum_unsetup_tx_list(sc);

	/* disable Rx */
	rum_setbits(sc, RT2573_TXRX_CSR0, RT2573_DISABLE_RX);

	/* reset ASIC */
	rum_write(sc, RT2573_MAC_CSR1, RT2573_RESET_ASIC | RT2573_RESET_BBP);
	rum_write(sc, RT2573_MAC_CSR1, 0);
	RUM_UNLOCK(sc);
}