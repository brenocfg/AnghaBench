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
typedef  int u_int16_t ;
struct wi_softc {int sc_flags; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_enabled; scalar_t__ wi_gone; } ;

/* Variables and functions */
 int CSR_READ_2 (struct wi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct wi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WI_EVENT_ACK ; 
 int /*<<< orphan*/  WI_EVENT_STAT ; 
 int WI_EV_ALLOC ; 
 int WI_EV_INFO ; 
 int WI_EV_RX ; 
 int WI_EV_TX_EXC ; 
 int WI_FLAGS_RUNNING ; 
 int WI_INTRS ; 
 int /*<<< orphan*/  WI_INT_EN ; 
 int /*<<< orphan*/  WI_LOCK (struct wi_softc*) ; 
 int /*<<< orphan*/  WI_UNLOCK (struct wi_softc*) ; 
 int /*<<< orphan*/ * mbufq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wi_info_intr (struct wi_softc*) ; 
 int /*<<< orphan*/  wi_rx_intr (struct wi_softc*) ; 
 int /*<<< orphan*/  wi_start (struct wi_softc*) ; 
 int /*<<< orphan*/  wi_tx_ex_intr (struct wi_softc*) ; 
 int /*<<< orphan*/  wi_tx_intr (struct wi_softc*) ; 

void
wi_intr(void *arg)
{
	struct wi_softc *sc = arg;
	u_int16_t status;

	WI_LOCK(sc);

	if (sc->wi_gone || !sc->sc_enabled ||
	    (sc->sc_flags & WI_FLAGS_RUNNING) == 0) {
		CSR_WRITE_2(sc, WI_INT_EN, 0);
		CSR_WRITE_2(sc, WI_EVENT_ACK, 0xFFFF);
		WI_UNLOCK(sc);
		return;
	}

	/* Disable interrupts. */
	CSR_WRITE_2(sc, WI_INT_EN, 0);

	status = CSR_READ_2(sc, WI_EVENT_STAT);
	if (status & WI_EV_RX)
		wi_rx_intr(sc);
	if (status & WI_EV_ALLOC)
		wi_tx_intr(sc);
	if (status & WI_EV_TX_EXC)
		wi_tx_ex_intr(sc);
	if (status & WI_EV_INFO)
		wi_info_intr(sc);
	if (mbufq_first(&sc->sc_snd) != NULL)
		wi_start(sc);

	/* Re-enable interrupts. */
	CSR_WRITE_2(sc, WI_INT_EN, WI_INTRS);

	WI_UNLOCK(sc);

	return;
}