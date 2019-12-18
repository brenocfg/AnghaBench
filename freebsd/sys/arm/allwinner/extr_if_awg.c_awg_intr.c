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
struct awg_softc {int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AWG_LOCK (struct awg_softc*) ; 
 int /*<<< orphan*/  AWG_UNLOCK (struct awg_softc*) ; 
 int /*<<< orphan*/  EMAC_INT_STA ; 
 int RD4 (struct awg_softc*,int /*<<< orphan*/ ) ; 
 int RX_INT ; 
 int TX_BUF_UA_INT ; 
 int TX_INT ; 
 int /*<<< orphan*/  WR4 (struct awg_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  awg_rxintr (struct awg_softc*) ; 
 int /*<<< orphan*/  awg_start_locked (struct awg_softc*) ; 
 int /*<<< orphan*/  awg_txeof (struct awg_softc*) ; 
 int /*<<< orphan*/  if_sendq_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
awg_intr(void *arg)
{
	struct awg_softc *sc;
	uint32_t val;

	sc = arg;

	AWG_LOCK(sc);
	val = RD4(sc, EMAC_INT_STA);
	WR4(sc, EMAC_INT_STA, val);

	if (val & RX_INT)
		awg_rxintr(sc);

	if (val & TX_INT)
		awg_txeof(sc);

	if (val & (TX_INT | TX_BUF_UA_INT)) {
		if (!if_sendq_empty(sc->ifp))
			awg_start_locked(sc);
	}

	AWG_UNLOCK(sc);
}