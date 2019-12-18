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
typedef  int uint32_t ;
struct ifnet {int dummy; } ;
struct are_softc {int sc_rxint_mask; int sc_txint_mask; struct ifnet* are_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARE_LOCK (struct are_softc*) ; 
 int /*<<< orphan*/  ARE_UNLOCK (struct are_softc*) ; 
 int CSR_READ_4 (struct are_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_STATUS ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct are_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  are_rx (struct are_softc*) ; 
 int /*<<< orphan*/  are_start (struct ifnet*) ; 
 int /*<<< orphan*/  are_tx (struct are_softc*) ; 

__attribute__((used)) static void
are_intr(void *arg)
{
	struct are_softc		*sc = arg;
	uint32_t		status;
	struct ifnet		*ifp = sc->are_ifp;

	ARE_LOCK(sc);

	/* mask out interrupts */

	status = CSR_READ_4(sc, CSR_STATUS);
	if (status) {
		CSR_WRITE_4(sc, CSR_STATUS, status);
	}
	if (status & sc->sc_rxint_mask) {
		are_rx(sc);
	}
	if (status & sc->sc_txint_mask) {
		are_tx(sc);
	}

	/* Try to get more packets going. */
	are_start(ifp);

	ARE_UNLOCK(sc);
}