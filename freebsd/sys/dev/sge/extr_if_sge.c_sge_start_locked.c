#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ sge_tx_cnt; int /*<<< orphan*/  sge_tx_dmamap; int /*<<< orphan*/  sge_tx_tag; } ;
struct sge_softc {int sge_flags; int sge_timer; TYPE_1__ sge_cdata; } ;
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct sge_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sge_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int SGE_FLAG_LINK ; 
 int /*<<< orphan*/  SGE_LOCK_ASSERT (struct sge_softc*) ; 
 scalar_t__ SGE_MAXTXSEGS ; 
 scalar_t__ SGE_TX_RING_CNT ; 
 int /*<<< orphan*/  TX_CTL ; 
 int TX_CTL_ENB ; 
 int TX_CTL_POLL ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sge_encap (struct sge_softc*,struct mbuf**) ; 

__attribute__((used)) static void
sge_start_locked(struct ifnet *ifp)
{
	struct sge_softc *sc;
	struct mbuf *m_head;
	int queued = 0;

	sc = ifp->if_softc;
	SGE_LOCK_ASSERT(sc);

	if ((sc->sge_flags & SGE_FLAG_LINK) == 0 ||
	    (ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING)
		return;

	for (queued = 0; !IFQ_DRV_IS_EMPTY(&ifp->if_snd); ) {
		if (sc->sge_cdata.sge_tx_cnt > (SGE_TX_RING_CNT -
		    SGE_MAXTXSEGS)) {
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m_head);
		if (m_head == NULL)
			break;
		if (sge_encap(sc, &m_head)) {
			if (m_head == NULL)
				break;
			IFQ_DRV_PREPEND(&ifp->if_snd, m_head);
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}
		queued++;
		/*
		 * If there's a BPF listener, bounce a copy of this frame
		 * to him.
		 */
		BPF_MTAP(ifp, m_head);
	}

	if (queued > 0) {
		bus_dmamap_sync(sc->sge_cdata.sge_tx_tag,
		    sc->sge_cdata.sge_tx_dmamap,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		CSR_WRITE_4(sc, TX_CTL, 0x1a00 | TX_CTL_ENB | TX_CTL_POLL);
		sc->sge_timer = 5;
	}
}