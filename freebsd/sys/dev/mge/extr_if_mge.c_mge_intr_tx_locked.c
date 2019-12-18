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
struct mge_softc {size_t tx_desc_used_idx; int /*<<< orphan*/  mge_tx_dtag; scalar_t__ tx_desc_used_count; int /*<<< orphan*/  mge_desc_dtag; struct mge_desc_wrapper* mge_tx_desc; scalar_t__ wd_timer; struct ifnet* ifp; } ;
struct mge_desc_wrapper {struct mbuf* buffer; int /*<<< orphan*/  buffer_dmap; int /*<<< orphan*/  desc_dmap; struct mge_desc* mge_desc; } ;
struct mge_desc {int cmd_status; } ;
struct mbuf {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int MGE_DMA_OWNED ; 
 int MGE_ERR_MASK ; 
 int MGE_ERR_SUMMARY ; 
 int /*<<< orphan*/  MGE_TRANSMIT_LOCK_ASSERT (struct mge_softc*) ; 
 int MGE_TX_DESC_NUM ; 
 int MGE_TX_ERROR_LC ; 
 int MGE_TX_ERROR_RL ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mge_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
mge_intr_tx_locked(struct mge_softc *sc)
{
	struct ifnet *ifp = sc->ifp;
	struct mge_desc_wrapper *dw;
	struct mge_desc *desc;
	uint32_t status;
	int send = 0;

	MGE_TRANSMIT_LOCK_ASSERT(sc);

	/* Disable watchdog */
	sc->wd_timer = 0;

	while (sc->tx_desc_used_count) {
		/* Get the descriptor */
		dw = &sc->mge_tx_desc[sc->tx_desc_used_idx];
		desc = dw->mge_desc;
		bus_dmamap_sync(sc->mge_desc_dtag, dw->desc_dmap,
		    BUS_DMASYNC_POSTREAD);

		/* Get descriptor status */
		status = desc->cmd_status;

		if (status & MGE_DMA_OWNED)
			break;

		sc->tx_desc_used_idx =
			(++sc->tx_desc_used_idx) % MGE_TX_DESC_NUM;
		sc->tx_desc_used_count--;

		/* Update collision statistics */
		if (status & MGE_ERR_SUMMARY) {
			if ((status & MGE_ERR_MASK) == MGE_TX_ERROR_LC)
				if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 1);
			if ((status & MGE_ERR_MASK) == MGE_TX_ERROR_RL)
				if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 16);
		}

		bus_dmamap_sync(sc->mge_tx_dtag, dw->buffer_dmap,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->mge_tx_dtag, dw->buffer_dmap);
		m_freem(dw->buffer);
		dw->buffer = (struct mbuf*)NULL;
		send++;

		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
	}

	if (send) {
		/* Now send anything that was pending */
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		mge_start_locked(ifp);
	}
}