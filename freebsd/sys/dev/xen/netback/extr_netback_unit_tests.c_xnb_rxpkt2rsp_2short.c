#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct xnb_pkt {int dummy; } ;
struct netif_rx_response {scalar_t__ id; size_t status; scalar_t__ offset; int flags; } ;
struct netif_rx_request {scalar_t__ id; scalar_t__ gref; } ;
struct TYPE_8__ {size_t len; } ;
struct mbuf {size_t m_len; TYPE_2__* m_next; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_flags; } ;
struct TYPE_12__ {void* rsp_prod_pvt; void* req_cons; } ;
struct TYPE_11__ {TYPE_5__ rxb; int /*<<< orphan*/  gnttab; TYPE_3__* rxs; int /*<<< orphan*/  rxf; } ;
struct TYPE_10__ {void* rsp_prod; void* req_prod; } ;
struct TYPE_9__ {size_t m_len; } ;
typedef  void* RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_FIRST_RESERVED ; 
 int MHLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int NETRXF_extra_info ; 
 int NETRXF_more_data ; 
 struct netif_rx_request* RING_GET_REQUEST (int /*<<< orphan*/ *,void*) ; 
 struct netif_rx_response* RING_GET_RESPONSE (TYPE_5__*,void*) ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 struct mbuf* m_getm (struct mbuf*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_m_freem (struct mbuf**) ; 
 int /*<<< orphan*/  xnb_mbufc2pkt (struct mbuf*,struct xnb_pkt*,void*,int) ; 
 int xnb_rxpkt2gnttab (struct xnb_pkt*,struct mbuf*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int xnb_rxpkt2rsp (struct xnb_pkt*,int /*<<< orphan*/ ,int,TYPE_5__*) ; 
 TYPE_4__ xnb_unit_pvt ; 

__attribute__((used)) static void
xnb_rxpkt2rsp_2short(char *buffer, size_t buflen) {
	struct xnb_pkt pkt;
	int nr_reqs, nr_entries;
	size_t size1 = MHLEN - 5;
	size_t size2 = MHLEN - 15;
	int free_slots = 32;
	RING_IDX start = 14;
	uint16_t id = 47;
	uint16_t gref = 54;
	struct netif_rx_request *req;
	struct netif_rx_response *rsp;
	struct mbuf *mbufc;

	mbufc = m_getm(NULL, size1, M_WAITOK, MT_DATA);
	XNB_ASSERT(mbufc != NULL);
	if (mbufc == NULL)
		return;
	mbufc->m_flags |= M_PKTHDR;

	m_getm(mbufc, size2, M_WAITOK, MT_DATA);
	XNB_ASSERT(mbufc->m_next != NULL);
	mbufc->m_pkthdr.len = size1 + size2;
	mbufc->m_len = size1;
	mbufc->m_next->m_len = size2;

	xnb_mbufc2pkt(mbufc, &pkt, start, free_slots);

	req = RING_GET_REQUEST(&xnb_unit_pvt.rxf, start);
	req->gref = gref;
	req->id = id;
	xnb_unit_pvt.rxb.req_cons = start;
	xnb_unit_pvt.rxb.rsp_prod_pvt = start;
	xnb_unit_pvt.rxs->req_prod = start + 1;
	xnb_unit_pvt.rxs->rsp_prod = start;

	nr_entries = xnb_rxpkt2gnttab(&pkt, mbufc, xnb_unit_pvt.gnttab,
			&xnb_unit_pvt.rxb, DOMID_FIRST_RESERVED);

	nr_reqs = xnb_rxpkt2rsp(&pkt, xnb_unit_pvt.gnttab, nr_entries,
	    &xnb_unit_pvt.rxb);

	XNB_ASSERT(nr_entries == 2);
	XNB_ASSERT(nr_reqs == 1);
	rsp = RING_GET_RESPONSE(&xnb_unit_pvt.rxb, start);
	XNB_ASSERT(rsp->id == id);
	XNB_ASSERT(rsp->status == size1 + size2);
	XNB_ASSERT(rsp->offset == 0);
	XNB_ASSERT(! (rsp->flags & (NETRXF_more_data | NETRXF_extra_info)));

	safe_m_freem(&mbufc);
}