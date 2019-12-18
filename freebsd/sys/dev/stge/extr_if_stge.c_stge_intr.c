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
typedef  int uint16_t ;
struct stge_softc {int sc_IntEnable; int /*<<< orphan*/  sc_dev; scalar_t__ sc_suspended; struct ifnet* sc_ifp; } ;
struct ifnet {int if_capenable; int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int CSR_READ_2 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct stge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct stge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMAC_RxDMAPollNow ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int IS_HostError ; 
 int IS_InterruptStatus ; 
 int IS_RFDListEnd ; 
 int IS_RxDMAComplete ; 
 int IS_TxComplete ; 
 int IS_TxDMAComplete ; 
 int /*<<< orphan*/  STGE_DMACtrl ; 
 int /*<<< orphan*/  STGE_IntEnable ; 
 int /*<<< orphan*/  STGE_IntStatus ; 
 int /*<<< orphan*/  STGE_IntStatusAck ; 
 int /*<<< orphan*/  STGE_LOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_UNLOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stge_init_locked (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_rxeof (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_start_locked (struct ifnet*) ; 
 int stge_tx_error (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_txeof (struct stge_softc*) ; 

__attribute__((used)) static void
stge_intr(void *arg)
{
	struct stge_softc *sc;
	struct ifnet *ifp;
	int reinit;
	uint16_t status;

	sc = (struct stge_softc *)arg;
	ifp = sc->sc_ifp;

	STGE_LOCK(sc);

#ifdef DEVICE_POLLING
	if ((ifp->if_capenable & IFCAP_POLLING) != 0)
		goto done_locked;
#endif
	status = CSR_READ_2(sc, STGE_IntStatus);
	if (sc->sc_suspended || (status & IS_InterruptStatus) == 0)
		goto done_locked;

	/* Disable interrupts. */
	for (reinit = 0;;) {
		status = CSR_READ_2(sc, STGE_IntStatusAck);
		status &= sc->sc_IntEnable;
		if (status == 0)
			break;
		/* Host interface errors. */
		if ((status & IS_HostError) != 0) {
			device_printf(sc->sc_dev,
			    "Host interface error, resetting...\n");
			reinit = 1;
			goto force_init;
		}

		/* Receive interrupts. */
		if ((status & IS_RxDMAComplete) != 0) {
			stge_rxeof(sc);
			if ((status & IS_RFDListEnd) != 0)
				CSR_WRITE_4(sc, STGE_DMACtrl,
				    DMAC_RxDMAPollNow);
		}

		/* Transmit interrupts. */
		if ((status & (IS_TxDMAComplete | IS_TxComplete)) != 0)
			stge_txeof(sc);

		/* Transmission errors.*/
		if ((status & IS_TxComplete) != 0) {
			if ((reinit = stge_tx_error(sc)) != 0)
				break;
		}
	}

force_init:
	if (reinit != 0) {
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		stge_init_locked(sc);
	}

	/* Re-enable interrupts. */
	CSR_WRITE_2(sc, STGE_IntEnable, sc->sc_IntEnable);

	/* Try to get more packets going. */
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		stge_start_locked(ifp);

done_locked:
	STGE_UNLOCK(sc);
}