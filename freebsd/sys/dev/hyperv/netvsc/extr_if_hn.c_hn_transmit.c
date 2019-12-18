#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct rm_priotracker {int dummy; } ;
struct TYPE_3__ {int len; int csum_flags; int flowid; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;
struct ifnet {int /*<<< orphan*/  if_bpf; struct hn_softc* if_softc; } ;
struct hn_tx_ring {int /*<<< orphan*/  hn_tx_task; int /*<<< orphan*/  hn_tx_taskq; int /*<<< orphan*/  hn_tx_lock; int /*<<< orphan*/  hn_direct_tx_size; scalar_t__ hn_sched_tx; scalar_t__ hn_oactive; int /*<<< orphan*/  hn_mbuf_br; } ;
struct hn_softc {int hn_xvf_flags; int hn_tx_ring_inuse; struct hn_tx_ring* hn_tx_ring; int /*<<< orphan*/  hn_vf_lock; TYPE_2__* hn_vf_ifp; } ;
struct TYPE_4__ {int (* if_transmit ) (TYPE_2__*,struct mbuf*) ;} ;

/* Variables and functions */
 int CSUM_IP6_TCP ; 
 int CSUM_IP6_UDP ; 
 int CSUM_IP_TCP ; 
 int CSUM_IP_UDP ; 
 int CSUM_TSO ; 
 int EIO ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int HN_XVFFLAG_ACCBPF ; 
 int HN_XVFFLAG_ENABLED ; 
 int /*<<< orphan*/  IFCOUNTER_OBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_OQDROPS ; 
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 scalar_t__ M_HASHTYPE_NONE ; 
 int M_MCAST ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_true (int) ; 
 scalar_t__ bpf_peers_present (int /*<<< orphan*/ ) ; 
 int drbr_enqueue (struct ifnet*,int /*<<< orphan*/ ,struct mbuf*) ; 
 struct mbuf* hn_check_tcpsyn (struct mbuf*,int*) ; 
 struct mbuf* hn_set_hlen (struct mbuf*) ; 
 struct mbuf* hn_tso_fixup (struct mbuf*) ; 
 int hn_xmit (struct hn_tx_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 struct mbuf* m_copypacket (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ mtx_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm_rlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_runlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 scalar_t__ rss_hash2bucket (int,scalar_t__,int*) ; 
 int stub1 (TYPE_2__*,struct mbuf*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hn_transmit(struct ifnet *ifp, struct mbuf *m)
{
	struct hn_softc *sc = ifp->if_softc;
	struct hn_tx_ring *txr;
	int error, idx = 0;

	if (sc->hn_xvf_flags & HN_XVFFLAG_ENABLED) {
		struct rm_priotracker pt;

		rm_rlock(&sc->hn_vf_lock, &pt);
		if (__predict_true(sc->hn_xvf_flags & HN_XVFFLAG_ENABLED)) {
			struct mbuf *m_bpf = NULL;
			int obytes, omcast;

			obytes = m->m_pkthdr.len;
			omcast = (m->m_flags & M_MCAST) != 0;

			if (sc->hn_xvf_flags & HN_XVFFLAG_ACCBPF) {
				if (bpf_peers_present(ifp->if_bpf)) {
					m_bpf = m_copypacket(m, M_NOWAIT);
					if (m_bpf == NULL) {
						/*
						 * Failed to grab a shallow
						 * copy; tap now.
						 */
						ETHER_BPF_MTAP(ifp, m);
					}
				}
			} else {
				ETHER_BPF_MTAP(ifp, m);
			}

			error = sc->hn_vf_ifp->if_transmit(sc->hn_vf_ifp, m);
			rm_runlock(&sc->hn_vf_lock, &pt);

			if (m_bpf != NULL) {
				if (!error)
					ETHER_BPF_MTAP(ifp, m_bpf);
				m_freem(m_bpf);
			}

			if (error == ENOBUFS) {
				if_inc_counter(ifp, IFCOUNTER_OQDROPS, 1);
			} else if (error) {
				if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
			} else {
				if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
				if_inc_counter(ifp, IFCOUNTER_OBYTES, obytes);
				if (omcast) {
					if_inc_counter(ifp, IFCOUNTER_OMCASTS,
					    omcast);
				}
			}
			return (error);
		}
		rm_runlock(&sc->hn_vf_lock, &pt);
	}

#if defined(INET6) || defined(INET)
	/*
	 * Perform TSO packet header fixup or get l2/l3 header length now,
	 * since packet headers should be cache-hot.
	 */
	if (m->m_pkthdr.csum_flags & CSUM_TSO) {
		m = hn_tso_fixup(m);
		if (__predict_false(m == NULL)) {
			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
			return EIO;
		}
	} else if (m->m_pkthdr.csum_flags &
	    (CSUM_IP_UDP | CSUM_IP_TCP | CSUM_IP6_UDP | CSUM_IP6_TCP)) {
		m = hn_set_hlen(m);
		if (__predict_false(m == NULL)) {
			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
			return EIO;
		}
	}
#endif

	/*
	 * Select the TX ring based on flowid
	 */
	if (M_HASHTYPE_GET(m) != M_HASHTYPE_NONE) {
#ifdef RSS
		uint32_t bid;

		if (rss_hash2bucket(m->m_pkthdr.flowid, M_HASHTYPE_GET(m),
		    &bid) == 0)
			idx = bid % sc->hn_tx_ring_inuse;
		else
#endif
		{
#if defined(INET6) || defined(INET)
			int tcpsyn = 0;

			if (m->m_pkthdr.len < 128 &&
			    (m->m_pkthdr.csum_flags &
			     (CSUM_IP_TCP | CSUM_IP6_TCP)) &&
			    (m->m_pkthdr.csum_flags & CSUM_TSO) == 0) {
				m = hn_check_tcpsyn(m, &tcpsyn);
				if (__predict_false(m == NULL)) {
					if_inc_counter(ifp,
					    IFCOUNTER_OERRORS, 1);
					return (EIO);
				}
			}
#else
			const int tcpsyn = 0;
#endif
			if (tcpsyn)
				idx = 0;
			else
				idx = m->m_pkthdr.flowid % sc->hn_tx_ring_inuse;
		}
	}
	txr = &sc->hn_tx_ring[idx];

	error = drbr_enqueue(ifp, txr->hn_mbuf_br, m);
	if (error) {
		if_inc_counter(ifp, IFCOUNTER_OQDROPS, 1);
		return error;
	}

	if (txr->hn_oactive)
		return 0;

	if (txr->hn_sched_tx)
		goto do_sched;

	if (mtx_trylock(&txr->hn_tx_lock)) {
		int sched;

		sched = hn_xmit(txr, txr->hn_direct_tx_size);
		mtx_unlock(&txr->hn_tx_lock);
		if (!sched)
			return 0;
	}
do_sched:
	taskqueue_enqueue(txr->hn_tx_taskq, &txr->hn_tx_task);
	return 0;
}