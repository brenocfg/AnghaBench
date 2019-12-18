#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct xnb_pkt {int dummy; } ;
struct netif_rx_response {scalar_t__ id; scalar_t__ offset; int flags; size_t status; } ;
struct netif_rx_request {int gref; scalar_t__ id; } ;
struct TYPE_7__ {size_t len; } ;
struct mbuf {size_t m_len; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_flags; } ;
struct TYPE_10__ {scalar_t__ rsp_prod_pvt; scalar_t__ req_cons; } ;
struct TYPE_9__ {TYPE_4__ rxb; int /*<<< orphan*/  gnttab; TYPE_2__* rxs; int /*<<< orphan*/  rxf; } ;
struct TYPE_8__ {scalar_t__ rsp_prod; scalar_t__ req_prod; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_FIRST_RESERVED ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int NETRXF_extra_info ; 
 int NETRXF_more_data ; 
 struct netif_rx_request* RING_GET_REQUEST (int /*<<< orphan*/ *,scalar_t__) ; 
 struct netif_rx_response* RING_GET_RESPONSE (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 struct mbuf* m_getm (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_m_freem (struct mbuf**) ; 
 int /*<<< orphan*/  xnb_mbufc2pkt (struct mbuf*,struct xnb_pkt*,scalar_t__,int) ; 
 int xnb_rxpkt2gnttab (struct xnb_pkt*,struct mbuf*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int xnb_rxpkt2rsp (struct xnb_pkt*,int /*<<< orphan*/ ,int,TYPE_4__*) ; 
 TYPE_3__ xnb_unit_pvt ; 

__attribute__((used)) static void
xnb_rxpkt2rsp_short(char *buffer, size_t buflen)
{
	struct xnb_pkt pkt;
	int nr_entries, nr_reqs;
	size_t size = 128;
	int free_slots = 60;
	RING_IDX start = 5;
	struct netif_rx_request *req;
	struct netif_rx_response *rsp;
	struct mbuf *mbuf;

	mbuf = m_getm(NULL, size, M_WAITOK, MT_DATA);
	mbuf->m_flags |= M_PKTHDR;
	mbuf->m_pkthdr.len = size;
	mbuf->m_len = size;

	xnb_mbufc2pkt(mbuf, &pkt, start, free_slots);
	req = RING_GET_REQUEST(&xnb_unit_pvt.rxf, start);
	req->gref = 7;
	xnb_unit_pvt.rxb.req_cons = start;
	xnb_unit_pvt.rxb.rsp_prod_pvt = start;
	xnb_unit_pvt.rxs->req_prod = start + 1;
	xnb_unit_pvt.rxs->rsp_prod = start;

	nr_entries = xnb_rxpkt2gnttab(&pkt, mbuf, xnb_unit_pvt.gnttab,
			&xnb_unit_pvt.rxb, DOMID_FIRST_RESERVED);

	nr_reqs = xnb_rxpkt2rsp(&pkt, xnb_unit_pvt.gnttab, nr_entries,
	    &xnb_unit_pvt.rxb);

	XNB_ASSERT(nr_reqs == 1);
	XNB_ASSERT(xnb_unit_pvt.rxb.rsp_prod_pvt == start + 1);
	rsp = RING_GET_RESPONSE(&xnb_unit_pvt.rxb, start);
	XNB_ASSERT(rsp->id == req->id);
	XNB_ASSERT(rsp->offset == 0);
	XNB_ASSERT((rsp->flags & (NETRXF_more_data | NETRXF_extra_info)) == 0);
	XNB_ASSERT(rsp->status == size);

	safe_m_freem(&mbuf);
}