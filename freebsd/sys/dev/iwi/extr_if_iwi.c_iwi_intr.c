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
struct iwi_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * txq; scalar_t__ sc_busy_timer; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int CSR_READ_4 (struct iwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct iwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWI_CSR_INTR ; 
 int /*<<< orphan*/  IWI_FLAG_BUSY ; 
 int IWI_INTR_CMD_DONE ; 
 int IWI_INTR_FATAL_ERROR ; 
 int IWI_INTR_FW_INITED ; 
 int IWI_INTR_PARITY_ERROR ; 
 int IWI_INTR_RADIO_OFF ; 
 int IWI_INTR_RX_DONE ; 
 int IWI_INTR_TX1_DONE ; 
 int IWI_INTR_TX2_DONE ; 
 int IWI_INTR_TX3_DONE ; 
 int IWI_INTR_TX4_DONE ; 
 int /*<<< orphan*/  IWI_LOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  IWI_LOCK_DECL ; 
 int /*<<< orphan*/  IWI_UNLOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iwi_fatal_error_intr (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_radio_off_intr (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_rx_intr (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_tx_intr (struct iwi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct iwi_softc*) ; 

__attribute__((used)) static void
iwi_intr(void *arg)
{
	struct iwi_softc *sc = arg;
	uint32_t r;
	IWI_LOCK_DECL;

	IWI_LOCK(sc);

	if ((r = CSR_READ_4(sc, IWI_CSR_INTR)) == 0 || r == 0xffffffff) {
		IWI_UNLOCK(sc);
		return;
	}

	/* acknowledge interrupts */
	CSR_WRITE_4(sc, IWI_CSR_INTR, r);

	if (r & IWI_INTR_FATAL_ERROR) {
		iwi_fatal_error_intr(sc);
		goto done;
	}

	if (r & IWI_INTR_FW_INITED) {
		if (!(r & (IWI_INTR_FATAL_ERROR | IWI_INTR_PARITY_ERROR)))
			wakeup(sc);
	}

	if (r & IWI_INTR_RADIO_OFF)
		iwi_radio_off_intr(sc);

	if (r & IWI_INTR_CMD_DONE) {
		sc->flags &= ~IWI_FLAG_BUSY;
		sc->sc_busy_timer = 0;
		wakeup(sc);
	}

	if (r & IWI_INTR_TX1_DONE)
		iwi_tx_intr(sc, &sc->txq[0]);

	if (r & IWI_INTR_TX2_DONE)
		iwi_tx_intr(sc, &sc->txq[1]);

	if (r & IWI_INTR_TX3_DONE)
		iwi_tx_intr(sc, &sc->txq[2]);

	if (r & IWI_INTR_TX4_DONE)
		iwi_tx_intr(sc, &sc->txq[3]);

	if (r & IWI_INTR_RX_DONE)
		iwi_rx_intr(sc);

	if (r & IWI_INTR_PARITY_ERROR) {
		/* XXX rate-limit */
		device_printf(sc->sc_dev, "parity error\n");
	}
done:
	IWI_UNLOCK(sc);
}