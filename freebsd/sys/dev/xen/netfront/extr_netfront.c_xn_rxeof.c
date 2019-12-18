#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct netif_rx_response {int flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
struct TYPE_9__ {TYPE_2__ gso; } ;
struct netif_extra_info {int type; TYPE_3__ u; } ;
struct TYPE_11__ {int /*<<< orphan*/  rsp_cons; TYPE_1__* sring; } ;
struct lro_ctrl {scalar_t__ lro_cnt; } ;
struct netfront_rxq {TYPE_5__ ring; struct lro_ctrl lro; struct netfront_info* info; } ;
struct netfront_rx_info {struct netif_extra_info* extras; struct netif_rx_response rx; } ;
struct netfront_info {struct ifnet* xn_ifp; } ;
struct mbufq {int dummy; } ;
struct TYPE_10__ {int csum_flags; int csum_data; int /*<<< orphan*/  tso_segsz; struct ifnet* rcvif; } ;
struct mbuf {TYPE_4__ m_pkthdr; } ;
struct ifnet {int if_capenable; int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  rsp_prod; } ;
typedef  int /*<<< orphan*/  RING_IDX ;

/* Variables and functions */
 int CSUM_DATA_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 int CSUM_TSO ; 
 int IFCAP_LRO ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int /*<<< orphan*/  INT_MAX ; 
 int NETRXF_data_validated ; 
 int NETRXF_extra_info ; 
 int /*<<< orphan*/  RING_FINAL_CHECK_FOR_RESPONSES (TYPE_5__*,int) ; 
 int /*<<< orphan*/  RING_GET_RESPONSE (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int XEN_NETIF_EXTRA_TYPE_GSO ; 
 int /*<<< orphan*/  XN_RX_LOCK_ASSERT (struct netfront_rxq*) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 struct mbuf* mbufq_dequeue (struct mbufq*) ; 
 int /*<<< orphan*/  mbufq_drain (struct mbufq*) ; 
 int /*<<< orphan*/  mbufq_enqueue (struct mbufq*,struct mbuf*) ; 
 int /*<<< orphan*/  mbufq_init (struct mbufq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct netif_rx_response*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct netif_extra_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netfront_carrier_ok (struct netfront_info*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  stub2 (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  tcp_lro_flush_all (struct lro_ctrl*) ; 
 scalar_t__ tcp_lro_rx (struct lro_ctrl*,struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xn_alloc_rx_buffers (struct netfront_rxq*) ; 
 int xn_get_responses (struct netfront_rxq*,struct netfront_rx_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf**) ; 

__attribute__((used)) static void
xn_rxeof(struct netfront_rxq *rxq)
{
	struct ifnet *ifp;
	struct netfront_info *np = rxq->info;
#if (defined(INET) || defined(INET6))
	struct lro_ctrl *lro = &rxq->lro;
#endif
	struct netfront_rx_info rinfo;
	struct netif_rx_response *rx = &rinfo.rx;
	struct netif_extra_info *extras = rinfo.extras;
	RING_IDX i, rp;
	struct mbuf *m;
	struct mbufq mbufq_rxq, mbufq_errq;
	int err, work_to_do;

	XN_RX_LOCK_ASSERT(rxq);

	if (!netfront_carrier_ok(np))
		return;

	/* XXX: there should be some sane limit. */
	mbufq_init(&mbufq_errq, INT_MAX);
	mbufq_init(&mbufq_rxq, INT_MAX);

	ifp = np->xn_ifp;

	do {
		rp = rxq->ring.sring->rsp_prod;
		rmb();	/* Ensure we see queued responses up to 'rp'. */

		i = rxq->ring.rsp_cons;
		while ((i != rp)) {
			memcpy(rx, RING_GET_RESPONSE(&rxq->ring, i), sizeof(*rx));
			memset(extras, 0, sizeof(rinfo.extras));

			m = NULL;
			err = xn_get_responses(rxq, &rinfo, rp, &i, &m);

			if (__predict_false(err)) {
				if (m)
					(void )mbufq_enqueue(&mbufq_errq, m);
				if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
				continue;
			}

			m->m_pkthdr.rcvif = ifp;
			if (rx->flags & NETRXF_data_validated) {
				/*
				 * According to mbuf(9) the correct way to tell
				 * the stack that the checksum of an inbound
				 * packet is correct, without it actually being
				 * present (because the underlying interface
				 * doesn't provide it), is to set the
				 * CSUM_DATA_VALID and CSUM_PSEUDO_HDR flags,
				 * and the csum_data field to 0xffff.
				 */
				m->m_pkthdr.csum_flags |= (CSUM_DATA_VALID
				    | CSUM_PSEUDO_HDR);
				m->m_pkthdr.csum_data = 0xffff;
			}
			if ((rx->flags & NETRXF_extra_info) != 0 &&
			    (extras[XEN_NETIF_EXTRA_TYPE_GSO - 1].type ==
			    XEN_NETIF_EXTRA_TYPE_GSO)) {
				m->m_pkthdr.tso_segsz =
				extras[XEN_NETIF_EXTRA_TYPE_GSO - 1].u.gso.size;
				m->m_pkthdr.csum_flags |= CSUM_TSO;
			}

			(void )mbufq_enqueue(&mbufq_rxq, m);
		}

		rxq->ring.rsp_cons = i;

		xn_alloc_rx_buffers(rxq);

		RING_FINAL_CHECK_FOR_RESPONSES(&rxq->ring, work_to_do);
	} while (work_to_do);

	mbufq_drain(&mbufq_errq);
	/*
	 * Process all the mbufs after the remapping is complete.
	 * Break the mbuf chain first though.
	 */
	while ((m = mbufq_dequeue(&mbufq_rxq)) != NULL) {
		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
#if (defined(INET) || defined(INET6))
		/* Use LRO if possible */
		if ((ifp->if_capenable & IFCAP_LRO) == 0 ||
		    lro->lro_cnt == 0 || tcp_lro_rx(lro, m, 0)) {
			/*
			 * If LRO fails, pass up to the stack
			 * directly.
			 */
			(*ifp->if_input)(ifp, m);
		}
#else
		(*ifp->if_input)(ifp, m);
#endif
	}

#if (defined(INET) || defined(INET6))
	/*
	 * Flush any outstanding LRO work
	 */
	tcp_lro_flush_all(lro);
#endif
}