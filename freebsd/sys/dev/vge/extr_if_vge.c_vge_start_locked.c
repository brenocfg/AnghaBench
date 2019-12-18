#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vge_txdesc {TYPE_2__* tx_desc; } ;
struct TYPE_6__ {int vge_tx_prodidx; int vge_tx_cnt; int /*<<< orphan*/  vge_tx_ring_map; int /*<<< orphan*/  vge_tx_ring_tag; struct vge_txdesc* vge_txdesc; } ;
struct vge_softc {int vge_flags; int vge_timer; TYPE_3__ vge_cdata; } ;
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct vge_softc* if_softc; } ;
struct TYPE_5__ {TYPE_1__* vge_frag; } ;
struct TYPE_4__ {int /*<<< orphan*/  vge_addrhi; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct vge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int VGE_FLAG_LINK ; 
 int /*<<< orphan*/  VGE_LOCK_ASSERT (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_TXDESC_Q ; 
 int /*<<< orphan*/  VGE_TXQCSRS ; 
 int /*<<< orphan*/  VGE_TXQCSR_WAK0 ; 
 int VGE_TX_DESC_CNT ; 
 int /*<<< orphan*/  VGE_TX_DESC_DEC (int) ; 
 int /*<<< orphan*/  VGE_TX_DESC_INC (int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 scalar_t__ vge_encap (struct vge_softc*,struct mbuf**) ; 

__attribute__((used)) static void
vge_start_locked(struct ifnet *ifp)
{
	struct vge_softc *sc;
	struct vge_txdesc *txd;
	struct mbuf *m_head;
	int enq, idx;

	sc = ifp->if_softc;

	VGE_LOCK_ASSERT(sc);

	if ((sc->vge_flags & VGE_FLAG_LINK) == 0 ||
	    (ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING)
		return;

	idx = sc->vge_cdata.vge_tx_prodidx;
	VGE_TX_DESC_DEC(idx);
	for (enq = 0; !IFQ_DRV_IS_EMPTY(&ifp->if_snd) &&
	    sc->vge_cdata.vge_tx_cnt < VGE_TX_DESC_CNT - 1; ) {
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m_head);
		if (m_head == NULL)
			break;
		/*
		 * Pack the data into the transmit ring. If we
		 * don't have room, set the OACTIVE flag and wait
		 * for the NIC to drain the ring.
		 */
		if (vge_encap(sc, &m_head)) {
			if (m_head == NULL)
				break;
			IFQ_DRV_PREPEND(&ifp->if_snd, m_head);
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}

		txd = &sc->vge_cdata.vge_txdesc[idx];
		txd->tx_desc->vge_frag[0].vge_addrhi |= htole32(VGE_TXDESC_Q);
		VGE_TX_DESC_INC(idx);

		enq++;
		/*
		 * If there's a BPF listener, bounce a copy of this frame
		 * to him.
		 */
		ETHER_BPF_MTAP(ifp, m_head);
	}

	if (enq > 0) {
		bus_dmamap_sync(sc->vge_cdata.vge_tx_ring_tag,
		    sc->vge_cdata.vge_tx_ring_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		/* Issue a transmit command. */
		CSR_WRITE_2(sc, VGE_TXQCSRS, VGE_TXQCSR_WAK0);
		/*
		 * Set a timeout in case the chip goes out to lunch.
		 */
		sc->vge_timer = 5;
	}
}