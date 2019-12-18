#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  len; TYPE_3__* rcvif; } ;
struct mbuf {int /*<<< orphan*/  m_len; TYPE_1__ m_pkthdr; } ;
struct llan_xfer {struct mbuf* rx_mbuf; } ;
struct llan_softc {size_t rx_dma_slot; int rx_valid_val; int rx_buf_len; int /*<<< orphan*/  io_lock; TYPE_2__* rx_buf; int /*<<< orphan*/  unit; TYPE_3__* ifp; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* if_input ) (TYPE_3__*,struct mbuf*) ;} ;
struct TYPE_6__ {int control; int /*<<< orphan*/  length; scalar_t__ offset; scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_VIO_SIGNAL ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  if_inc_counter (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ llan_add_rxbuf (struct llan_softc*,struct llan_xfer*) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phyp_hcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct mbuf*) ; 

__attribute__((used)) static void
llan_intr(void *xsc)
{
	struct llan_softc *sc = xsc;
	struct llan_xfer *rx;
	struct mbuf *m;

	mtx_lock(&sc->io_lock);
restart:
	phyp_hcall(H_VIO_SIGNAL, sc->unit, 0);

	while ((sc->rx_buf[sc->rx_dma_slot].control >> 7) == sc->rx_valid_val) {
		rx = (struct llan_xfer *)sc->rx_buf[sc->rx_dma_slot].handle;
		m = rx->rx_mbuf;
		m_adj(m, sc->rx_buf[sc->rx_dma_slot].offset - 8);
		m->m_len = sc->rx_buf[sc->rx_dma_slot].length;

		/* llan_add_rxbuf does DMA sync and unload as well as requeue */
		if (llan_add_rxbuf(sc, rx) != 0) {
			if_inc_counter(sc->ifp, IFCOUNTER_IERRORS, 1);
			continue;
		}

		if_inc_counter(sc->ifp, IFCOUNTER_IPACKETS, 1);
		m_adj(m, sc->rx_buf[sc->rx_dma_slot].offset);
		m->m_len = sc->rx_buf[sc->rx_dma_slot].length;
		m->m_pkthdr.rcvif = sc->ifp;
		m->m_pkthdr.len = m->m_len;
		sc->rx_dma_slot++;

		if (sc->rx_dma_slot >= sc->rx_buf_len/sizeof(sc->rx_buf[0])) {
			sc->rx_dma_slot = 0;
			sc->rx_valid_val = !sc->rx_valid_val;
		}

		mtx_unlock(&sc->io_lock);
		(*sc->ifp->if_input)(sc->ifp, m);
		mtx_lock(&sc->io_lock);
	}

	phyp_hcall(H_VIO_SIGNAL, sc->unit, 1);

	/*
	 * H_VIO_SIGNAL enables interrupts for future packets only.
	 * Make sure none were queued between the end of the loop and the
	 * enable interrupts call.
	 */
	if ((sc->rx_buf[sc->rx_dma_slot].control >> 7) == sc->rx_valid_val)
		goto restart;

	mtx_unlock(&sc->io_lock);
}