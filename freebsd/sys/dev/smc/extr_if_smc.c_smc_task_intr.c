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
typedef  int u_int ;
struct smc_softc {int smc_mask; int /*<<< orphan*/  smc_tx; int /*<<< orphan*/  smc_tq; int /*<<< orphan*/  smc_watchdog; int /*<<< orphan*/  smc_rx; int /*<<< orphan*/  smc_dev; } ;
struct ifnet {int if_capenable; struct smc_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK ; 
 int ALLOC_INT ; 
 int /*<<< orphan*/  ECR ; 
 int ECR_MULCOL_MASK ; 
 int ECR_MULCOL_SHIFT ; 
 int ECR_SNGLCOL_MASK ; 
 int ECR_SNGLCOL_SHIFT ; 
 int /*<<< orphan*/  EPHSR ; 
 int EPHSR_TX_SUC ; 
 int FIFO_EMPTY ; 
 int /*<<< orphan*/  FIFO_TX ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IST ; 
 int /*<<< orphan*/  MMUCR ; 
 int MMUCR_CMD_RELEASE_PKT ; 
 int /*<<< orphan*/  MSK ; 
 int /*<<< orphan*/  PNR ; 
 int /*<<< orphan*/  PTR ; 
 int PTR_AUTO_INCR ; 
 int PTR_READ ; 
 int RCV_INT ; 
 int RX_OVRN_INT ; 
 int /*<<< orphan*/  SMC_LOCK (struct smc_softc*) ; 
 int /*<<< orphan*/  SMC_UNLOCK (struct smc_softc*) ; 
 int /*<<< orphan*/  TCR ; 
 int TCR_PAD_EN ; 
 int TCR_TXENA ; 
 int TX_EMPTY_INT ; 
 int TX_INT ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smc_mmu_wait (struct smc_softc*) ; 
 int smc_read_1 (struct smc_softc*,int /*<<< orphan*/ ) ; 
 int smc_read_2 (struct smc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_select_bank (struct smc_softc*,int) ; 
 int /*<<< orphan*/  smc_write_1 (struct smc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smc_write_2 (struct smc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
smc_task_intr(void *context, int pending)
{
	struct smc_softc	*sc;
	struct ifnet		*ifp;
	u_int			status, packet, counter, tcr;

	(void)pending;
	ifp = (struct ifnet *)context;
	sc = ifp->if_softc;

	SMC_LOCK(sc);
	
	smc_select_bank(sc, 2);

	/*
	 * Find out what interrupts are flagged.
	 */
	status = smc_read_1(sc, IST) & sc->smc_mask;

	/*
	 * Transmit error
	 */
	if (status & TX_INT) {
		/*
		 * Kill off the packet if there is one and re-enable transmit.
		 */
		packet = smc_read_1(sc, FIFO_TX);
		if ((packet & FIFO_EMPTY) == 0) {
			callout_stop(&sc->smc_watchdog);
			smc_select_bank(sc, 2);
			smc_write_1(sc, PNR, packet);
			smc_write_2(sc, PTR, 0 | PTR_READ | 
			    PTR_AUTO_INCR);
			smc_select_bank(sc, 0);
			tcr = smc_read_2(sc, EPHSR);
#if 0
			if ((tcr & EPHSR_TX_SUC) == 0)
				device_printf(sc->smc_dev,
				    "bad packet\n");
#endif
			smc_select_bank(sc, 2);
			smc_mmu_wait(sc);
			smc_write_2(sc, MMUCR, MMUCR_CMD_RELEASE_PKT);

			smc_select_bank(sc, 0);
			tcr = smc_read_2(sc, TCR);
			tcr |= TCR_TXENA | TCR_PAD_EN;
			smc_write_2(sc, TCR, tcr);
			smc_select_bank(sc, 2);
			taskqueue_enqueue(sc->smc_tq, &sc->smc_tx);
		}

		/*
		 * Ack the interrupt.
		 */
		smc_write_1(sc, ACK, TX_INT);
	}

	/*
	 * Receive
	 */
	if (status & RCV_INT) {
		smc_write_1(sc, ACK, RCV_INT);
		sc->smc_mask &= ~RCV_INT;
		taskqueue_enqueue(sc->smc_tq, &sc->smc_rx);
	}

	/*
	 * Allocation
	 */
	if (status & ALLOC_INT) {
		smc_write_1(sc, ACK, ALLOC_INT);
		sc->smc_mask &= ~ALLOC_INT;
		taskqueue_enqueue(sc->smc_tq, &sc->smc_tx);
	}

	/*
	 * Receive overrun
	 */
	if (status & RX_OVRN_INT) {
		smc_write_1(sc, ACK, RX_OVRN_INT);
		if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
	}

	/*
	 * Transmit empty
	 */
	if (status & TX_EMPTY_INT) {
		smc_write_1(sc, ACK, TX_EMPTY_INT);
		sc->smc_mask &= ~TX_EMPTY_INT;
		callout_stop(&sc->smc_watchdog);

		/*
		 * Update collision stats.
		 */
		smc_select_bank(sc, 0);
		counter = smc_read_2(sc, ECR);
		smc_select_bank(sc, 2);
		if_inc_counter(ifp, IFCOUNTER_COLLISIONS,
		    ((counter & ECR_SNGLCOL_MASK) >> ECR_SNGLCOL_SHIFT) +
		    ((counter & ECR_MULCOL_MASK) >> ECR_MULCOL_SHIFT));

		/*
		 * See if there are any packets to transmit.
		 */
		taskqueue_enqueue(sc->smc_tq, &sc->smc_tx);
	}

	/*
	 * Update the interrupt mask.
	 */
	smc_select_bank(sc, 2);
	if ((ifp->if_capenable & IFCAP_POLLING) == 0)
		smc_write_1(sc, MSK, sc->smc_mask);

	SMC_UNLOCK(sc);
}