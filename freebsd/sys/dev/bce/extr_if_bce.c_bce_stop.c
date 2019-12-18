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
struct ifnet {int if_drv_flags; } ;
struct bce_softc {int /*<<< orphan*/  bce_link_up; scalar_t__ watchdog_timer; int /*<<< orphan*/  bce_tick_callout; struct ifnet* bce_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_LOCK_ASSERT (struct bce_softc*) ; 
 int /*<<< orphan*/  BCE_MISC_ENABLE_CLR_BITS ; 
 int /*<<< orphan*/  BCE_MISC_ENABLE_CLR_DEFAULT ; 
 int /*<<< orphan*/  BCE_VERBOSE_RESET ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  REG_RD (struct bce_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bce_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bce_disable_intr (struct bce_softc*) ; 
 int /*<<< orphan*/  bce_free_pg_chain (struct bce_softc*) ; 
 int /*<<< orphan*/  bce_free_rx_chain (struct bce_softc*) ; 
 int /*<<< orphan*/  bce_free_tx_chain (struct bce_softc*) ; 
 scalar_t__ bce_hdr_split ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bce_stop(struct bce_softc *sc)
{
	struct ifnet *ifp;

	DBENTER(BCE_VERBOSE_RESET);

	BCE_LOCK_ASSERT(sc);

	ifp = sc->bce_ifp;

	callout_stop(&sc->bce_tick_callout);

	/* Disable the transmit/receive blocks. */
	REG_WR(sc, BCE_MISC_ENABLE_CLR_BITS, BCE_MISC_ENABLE_CLR_DEFAULT);
	REG_RD(sc, BCE_MISC_ENABLE_CLR_BITS);
	DELAY(20);

	bce_disable_intr(sc);

	/* Free RX buffers. */
	if (bce_hdr_split == TRUE) {
		bce_free_pg_chain(sc);
	}
	bce_free_rx_chain(sc);

	/* Free TX buffers. */
	bce_free_tx_chain(sc);

	sc->watchdog_timer = 0;

	sc->bce_link_up = FALSE;

	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);

	DBEXIT(BCE_VERBOSE_RESET);
}