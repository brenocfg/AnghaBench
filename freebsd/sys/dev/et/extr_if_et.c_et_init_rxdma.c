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
struct et_rxstat_ring {scalar_t__ rsr_wrap; scalar_t__ rsr_index; int /*<<< orphan*/  rsr_paddr; } ;
struct et_rxstatus_data {int /*<<< orphan*/  rxsd_paddr; } ;
struct et_softc {int sc_rx_intr_npkts; int sc_rx_intr_delay; struct et_rxdesc_ring* sc_rx_ring; struct et_rxstat_ring sc_rxstat_ring; struct et_rxstatus_data sc_rx_status; int /*<<< orphan*/  ifp; } ;
struct et_rxdesc_ring {int rr_wrap; scalar_t__ rr_index; int /*<<< orphan*/  rr_paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int ET_ADDR_HI (int /*<<< orphan*/ ) ; 
 int ET_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET_RXSTAT_CNT ; 
 int /*<<< orphan*/  ET_RXSTAT_HI ; 
 int /*<<< orphan*/  ET_RXSTAT_LO ; 
 int /*<<< orphan*/  ET_RXSTAT_MINCNT ; 
 int /*<<< orphan*/  ET_RXSTAT_POS ; 
 int /*<<< orphan*/  ET_RX_INTR_DELAY ; 
 int /*<<< orphan*/  ET_RX_INTR_NPKTS ; 
 int ET_RX_NDESC ; 
 int ET_RX_NSTAT ; 
 int /*<<< orphan*/  ET_RX_RING0_CNT ; 
 int /*<<< orphan*/  ET_RX_RING0_HI ; 
 int /*<<< orphan*/  ET_RX_RING0_LO ; 
 int /*<<< orphan*/  ET_RX_RING0_MINCNT ; 
 int /*<<< orphan*/  ET_RX_RING0_POS ; 
 int ET_RX_RING0_POS_WRAP ; 
 int /*<<< orphan*/  ET_RX_RING1_CNT ; 
 int /*<<< orphan*/  ET_RX_RING1_HI ; 
 int /*<<< orphan*/  ET_RX_RING1_LO ; 
 int /*<<< orphan*/  ET_RX_RING1_MINCNT ; 
 int /*<<< orphan*/  ET_RX_RING1_POS ; 
 int ET_RX_RING1_POS_WRAP ; 
 int /*<<< orphan*/  ET_RX_STATUS_HI ; 
 int /*<<< orphan*/  ET_RX_STATUS_LO ; 
 int et_stop_rxdma (struct et_softc*) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
et_init_rxdma(struct et_softc *sc)
{
	struct et_rxstatus_data *rxsd;
	struct et_rxstat_ring *rxst_ring;
	struct et_rxdesc_ring *rx_ring;
	int error;

	error = et_stop_rxdma(sc);
	if (error) {
		if_printf(sc->ifp, "can't init RX DMA engine\n");
		return (error);
	}

	/*
	 * Install RX status
	 */
	rxsd = &sc->sc_rx_status;
	CSR_WRITE_4(sc, ET_RX_STATUS_HI, ET_ADDR_HI(rxsd->rxsd_paddr));
	CSR_WRITE_4(sc, ET_RX_STATUS_LO, ET_ADDR_LO(rxsd->rxsd_paddr));

	/*
	 * Install RX stat ring
	 */
	rxst_ring = &sc->sc_rxstat_ring;
	CSR_WRITE_4(sc, ET_RXSTAT_HI, ET_ADDR_HI(rxst_ring->rsr_paddr));
	CSR_WRITE_4(sc, ET_RXSTAT_LO, ET_ADDR_LO(rxst_ring->rsr_paddr));
	CSR_WRITE_4(sc, ET_RXSTAT_CNT, ET_RX_NSTAT - 1);
	CSR_WRITE_4(sc, ET_RXSTAT_POS, 0);
	CSR_WRITE_4(sc, ET_RXSTAT_MINCNT, ((ET_RX_NSTAT * 15) / 100) - 1);

	/* Match ET_RXSTAT_POS */
	rxst_ring->rsr_index = 0;
	rxst_ring->rsr_wrap = 0;

	/*
	 * Install the 2nd RX descriptor ring
	 */
	rx_ring = &sc->sc_rx_ring[1];
	CSR_WRITE_4(sc, ET_RX_RING1_HI, ET_ADDR_HI(rx_ring->rr_paddr));
	CSR_WRITE_4(sc, ET_RX_RING1_LO, ET_ADDR_LO(rx_ring->rr_paddr));
	CSR_WRITE_4(sc, ET_RX_RING1_CNT, ET_RX_NDESC - 1);
	CSR_WRITE_4(sc, ET_RX_RING1_POS, ET_RX_RING1_POS_WRAP);
	CSR_WRITE_4(sc, ET_RX_RING1_MINCNT, ((ET_RX_NDESC * 15) / 100) - 1);

	/* Match ET_RX_RING1_POS */
	rx_ring->rr_index = 0;
	rx_ring->rr_wrap = 1;

	/*
	 * Install the 1st RX descriptor ring
	 */
	rx_ring = &sc->sc_rx_ring[0];
	CSR_WRITE_4(sc, ET_RX_RING0_HI, ET_ADDR_HI(rx_ring->rr_paddr));
	CSR_WRITE_4(sc, ET_RX_RING0_LO, ET_ADDR_LO(rx_ring->rr_paddr));
	CSR_WRITE_4(sc, ET_RX_RING0_CNT, ET_RX_NDESC - 1);
	CSR_WRITE_4(sc, ET_RX_RING0_POS, ET_RX_RING0_POS_WRAP);
	CSR_WRITE_4(sc, ET_RX_RING0_MINCNT, ((ET_RX_NDESC * 15) / 100) - 1);

	/* Match ET_RX_RING0_POS */
	rx_ring->rr_index = 0;
	rx_ring->rr_wrap = 1;

	/*
	 * RX intr moderation
	 */
	CSR_WRITE_4(sc, ET_RX_INTR_NPKTS, sc->sc_rx_intr_npkts);
	CSR_WRITE_4(sc, ET_RX_INTR_DELAY, sc->sc_rx_intr_delay);

	return (0);
}