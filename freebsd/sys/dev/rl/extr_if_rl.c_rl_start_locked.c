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
struct TYPE_6__ {int /*<<< orphan*/  cur_tx; } ;
struct rl_softc {int rl_flags; int rl_watchdog_timer; TYPE_2__ rl_cdata; int /*<<< orphan*/  rl_txthresh; } ;
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct rl_softc* if_softc; } ;
struct TYPE_5__ {int len; } ;
struct TYPE_7__ {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,TYPE_3__*) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 TYPE_3__* RL_CUR_TXMBUF (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_CUR_TXSTAT (struct rl_softc*) ; 
 int RL_FLAG_LINK ; 
 int /*<<< orphan*/  RL_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 int RL_TXTHRESH (int /*<<< orphan*/ ) ; 
 scalar_t__ rl_encap (struct rl_softc*,struct mbuf**) ; 

__attribute__((used)) static void
rl_start_locked(struct ifnet *ifp)
{
	struct rl_softc		*sc = ifp->if_softc;
	struct mbuf		*m_head = NULL;

	RL_LOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING || (sc->rl_flags & RL_FLAG_LINK) == 0)
		return;

	while (RL_CUR_TXMBUF(sc) == NULL) {

		IFQ_DRV_DEQUEUE(&ifp->if_snd, m_head);

		if (m_head == NULL)
			break;

		if (rl_encap(sc, &m_head)) {
			if (m_head == NULL)
				break;
			IFQ_DRV_PREPEND(&ifp->if_snd, m_head);
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}

		/* Pass a copy of this mbuf chain to the bpf subsystem. */
		BPF_MTAP(ifp, RL_CUR_TXMBUF(sc));

		/* Transmit the frame. */
		CSR_WRITE_4(sc, RL_CUR_TXSTAT(sc),
		    RL_TXTHRESH(sc->rl_txthresh) |
		    RL_CUR_TXMBUF(sc)->m_pkthdr.len);

		RL_INC(sc->rl_cdata.cur_tx);

		/* Set a timeout in case the chip goes out to lunch. */
		sc->rl_watchdog_timer = 5;
	}

	/*
	 * We broke out of the loop because all our TX slots are
	 * full. Mark the NIC as busy until it drains some of the
	 * packets from the queue.
	 */
	if (RL_CUR_TXMBUF(sc) != NULL)
		ifp->if_drv_flags |= IFF_DRV_OACTIVE;
}