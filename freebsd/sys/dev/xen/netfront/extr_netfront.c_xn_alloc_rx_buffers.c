#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct netif_rx_request {unsigned short id; scalar_t__ gref; } ;
struct TYPE_5__ {scalar_t__ req_prod_pvt; scalar_t__ rsp_cons; } ;
struct netfront_rxq {int /*<<< orphan*/  xen_intr_handle; TYPE_2__ ring; int /*<<< orphan*/  rx_refill; TYPE_1__* info; scalar_t__* grant_ref; int /*<<< orphan*/  gref_head; struct mbuf** mbufs; } ;
struct mbuf {int dummy; } ;
typedef  scalar_t__ grant_ref_t ;
struct TYPE_4__ {scalar_t__ carrier; int /*<<< orphan*/  xbdev; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 scalar_t__ GNTTAB_LIST_END ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ NET_RX_RING_SIZE ; 
 scalar_t__ NET_RX_SLOTS_MIN ; 
 struct netif_rx_request* RING_GET_REQUEST (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS_AND_CHECK_NOTIFY (TYPE_2__*,int) ; 
 int /*<<< orphan*/  XN_RX_LOCK_ASSERT (struct netfront_rxq*) ; 
 scalar_t__ __predict_false (int) ; 
 unsigned long atop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset_curcpu (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct netfront_rxq*) ; 
 scalar_t__ gnttab_claim_grant_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_grant_foreign_access_ref (scalar_t__,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_offset_t ; 
 int /*<<< orphan*/  vtophys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  xen_intr_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_get_otherend_id (int /*<<< orphan*/ ) ; 
 struct mbuf* xn_alloc_one_rx_buffer (struct netfront_rxq*) ; 
 int /*<<< orphan*/  xn_alloc_rx_buffers_callout ; 
 unsigned short xn_rxidx (scalar_t__) ; 

__attribute__((used)) static void
xn_alloc_rx_buffers(struct netfront_rxq *rxq)
{
	RING_IDX req_prod;
	int notify;

	XN_RX_LOCK_ASSERT(rxq);

	if (__predict_false(rxq->info->carrier == 0))
		return;

	for (req_prod = rxq->ring.req_prod_pvt;
	     req_prod - rxq->ring.rsp_cons < NET_RX_RING_SIZE;
	     req_prod++) {
		struct mbuf *m;
		unsigned short id;
		grant_ref_t ref;
		struct netif_rx_request *req;
		unsigned long pfn;

		m = xn_alloc_one_rx_buffer(rxq);
		if (m == NULL)
			break;

		id = xn_rxidx(req_prod);

		KASSERT(rxq->mbufs[id] == NULL, ("non-NULL xn_rx_chain"));
		rxq->mbufs[id] = m;

		ref = gnttab_claim_grant_reference(&rxq->gref_head);
		KASSERT(ref != GNTTAB_LIST_END,
		    ("reserved grant references exhuasted"));
		rxq->grant_ref[id] = ref;

		pfn = atop(vtophys(mtod(m, vm_offset_t)));
		req = RING_GET_REQUEST(&rxq->ring, req_prod);

		gnttab_grant_foreign_access_ref(ref,
		    xenbus_get_otherend_id(rxq->info->xbdev), pfn, 0);
		req->id = id;
		req->gref = ref;
	}

	rxq->ring.req_prod_pvt = req_prod;

	/* Not enough requests? Try again later. */
	if (req_prod - rxq->ring.rsp_cons < NET_RX_SLOTS_MIN) {
		callout_reset_curcpu(&rxq->rx_refill, hz/10,
		    xn_alloc_rx_buffers_callout, rxq);
		return;
	}

	wmb();		/* barrier so backend seens requests */

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&rxq->ring, notify);
	if (notify)
		xen_intr_signal(rxq->xen_intr_handle);
}