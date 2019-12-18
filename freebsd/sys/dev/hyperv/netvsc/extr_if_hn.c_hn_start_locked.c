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
struct TYPE_2__ {int len; int csum_flags; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;
struct hn_txdesc {int dummy; } ;
struct hn_tx_ring {int hn_suspended; scalar_t__ hn_agg_pktleft; int /*<<< orphan*/ * hn_agg_txd; int /*<<< orphan*/  hn_no_txdescs; int /*<<< orphan*/  hn_tx_lock; struct hn_softc* hn_sc; } ;
struct hn_softc {struct hn_tx_ring* hn_tx_ring; struct ifnet* hn_ifp; } ;

/* Variables and functions */
 int CSUM_IP6_TCP ; 
 int CSUM_IP6_UDP ; 
 int CSUM_IP_TCP ; 
 int CSUM_IP_UDP ; 
 int CSUM_TSO ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  atomic_set_int (int*,int) ; 
 int hn_encap (struct ifnet*,struct hn_tx_ring*,struct hn_txdesc*,struct mbuf**) ; 
 int hn_flush_txagg (struct ifnet*,struct hn_tx_ring*) ; 
 struct mbuf* hn_set_hlen (struct mbuf*) ; 
 struct mbuf* hn_tso_fixup (struct mbuf*) ; 
 struct hn_txdesc* hn_txdesc_get (struct hn_tx_ring*) ; 
 int hn_txpkt (struct ifnet*,struct hn_tx_ring*,struct hn_txdesc*) ; 
 int hn_use_if_start ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hn_start_locked(struct hn_tx_ring *txr, int len)
{
	struct hn_softc *sc = txr->hn_sc;
	struct ifnet *ifp = sc->hn_ifp;
	int sched = 0;

	KASSERT(hn_use_if_start,
	    ("hn_start_locked is called, when if_start is disabled"));
	KASSERT(txr == &sc->hn_tx_ring[0], ("not the first TX ring"));
	mtx_assert(&txr->hn_tx_lock, MA_OWNED);
	KASSERT(txr->hn_agg_txd == NULL, ("lingering aggregating txdesc"));

	if (__predict_false(txr->hn_suspended))
		return (0);

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING)
		return (0);

	while (!IFQ_DRV_IS_EMPTY(&ifp->if_snd)) {
		struct hn_txdesc *txd;
		struct mbuf *m_head;
		int error;

		IFQ_DRV_DEQUEUE(&ifp->if_snd, m_head);
		if (m_head == NULL)
			break;

		if (len > 0 && m_head->m_pkthdr.len > len) {
			/*
			 * This sending could be time consuming; let callers
			 * dispatch this packet sending (and sending of any
			 * following up packets) to tx taskqueue.
			 */
			IFQ_DRV_PREPEND(&ifp->if_snd, m_head);
			sched = 1;
			break;
		}

#if defined(INET6) || defined(INET)
		if (m_head->m_pkthdr.csum_flags & CSUM_TSO) {
			m_head = hn_tso_fixup(m_head);
			if (__predict_false(m_head == NULL)) {
				if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
				continue;
			}
		} else if (m_head->m_pkthdr.csum_flags &
		    (CSUM_IP_UDP | CSUM_IP_TCP | CSUM_IP6_UDP | CSUM_IP6_TCP)) {
			m_head = hn_set_hlen(m_head);
			if (__predict_false(m_head == NULL)) {
				if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
				continue;
			}
		}
#endif

		txd = hn_txdesc_get(txr);
		if (txd == NULL) {
			txr->hn_no_txdescs++;
			IFQ_DRV_PREPEND(&ifp->if_snd, m_head);
			atomic_set_int(&ifp->if_drv_flags, IFF_DRV_OACTIVE);
			break;
		}

		error = hn_encap(ifp, txr, txd, &m_head);
		if (error) {
			/* Both txd and m_head are freed */
			KASSERT(txr->hn_agg_txd == NULL,
			    ("encap failed w/ pending aggregating txdesc"));
			continue;
		}

		if (txr->hn_agg_pktleft == 0) {
			if (txr->hn_agg_txd != NULL) {
				KASSERT(m_head == NULL,
				    ("pending mbuf for aggregating txdesc"));
				error = hn_flush_txagg(ifp, txr);
				if (__predict_false(error)) {
					atomic_set_int(&ifp->if_drv_flags,
					    IFF_DRV_OACTIVE);
					break;
				}
			} else {
				KASSERT(m_head != NULL, ("mbuf was freed"));
				error = hn_txpkt(ifp, txr, txd);
				if (__predict_false(error)) {
					/* txd is freed, but m_head is not */
					IFQ_DRV_PREPEND(&ifp->if_snd, m_head);
					atomic_set_int(&ifp->if_drv_flags,
					    IFF_DRV_OACTIVE);
					break;
				}
			}
		}
#ifdef INVARIANTS
		else {
			KASSERT(txr->hn_agg_txd != NULL,
			    ("no aggregating txdesc"));
			KASSERT(m_head == NULL,
			    ("pending mbuf for aggregating txdesc"));
		}
#endif
	}

	/* Flush pending aggerated transmission. */
	if (txr->hn_agg_txd != NULL)
		hn_flush_txagg(ifp, txr);
	return (sched);
}