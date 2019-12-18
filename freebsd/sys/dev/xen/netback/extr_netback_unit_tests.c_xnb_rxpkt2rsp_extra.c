#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct xnb_pkt {int dummy; } ;
struct netif_rx_response {scalar_t__ id; int flags; size_t status; } ;
struct netif_rx_request {scalar_t__ gref; scalar_t__ id; } ;
struct TYPE_11__ {scalar_t__ size; scalar_t__ type; } ;
struct TYPE_12__ {TYPE_3__ gso; } ;
struct netif_extra_info {scalar_t__ type; int flags; TYPE_4__ u; } ;
struct TYPE_9__ {size_t len; scalar_t__ tso_segsz; int /*<<< orphan*/  csum_flags; } ;
struct mbuf {size_t m_len; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_flags; } ;
struct TYPE_14__ {scalar_t__ rsp_prod_pvt; scalar_t__ req_cons; } ;
struct TYPE_13__ {TYPE_6__ rxb; int /*<<< orphan*/  gnttab; TYPE_2__* rxs; int /*<<< orphan*/  rxf; } ;
struct TYPE_10__ {scalar_t__ rsp_prod; scalar_t__ req_prod; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  CSUM_TSO ; 
 int /*<<< orphan*/  DOMID_FIRST_RESERVED ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int NETRXF_csum_blank ; 
 int NETRXF_data_validated ; 
 int NETRXF_extra_info ; 
 int NETRXF_more_data ; 
 struct netif_rx_request* RING_GET_REQUEST (int /*<<< orphan*/ *,scalar_t__) ; 
 struct netif_rx_response* RING_GET_RESPONSE (TYPE_6__*,scalar_t__) ; 
 scalar_t__ TCP_MSS ; 
 int XEN_NETIF_EXTRA_FLAG_MORE ; 
 scalar_t__ XEN_NETIF_EXTRA_TYPE_GSO ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 struct mbuf* m_getm (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_m_freem (struct mbuf**) ; 
 int /*<<< orphan*/  xnb_mbufc2pkt (struct mbuf*,struct xnb_pkt*,scalar_t__,int) ; 
 int xnb_rxpkt2gnttab (struct xnb_pkt*,struct mbuf*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int xnb_rxpkt2rsp (struct xnb_pkt*,int /*<<< orphan*/ ,int,TYPE_6__*) ; 
 TYPE_5__ xnb_unit_pvt ; 

__attribute__((used)) static void
xnb_rxpkt2rsp_extra(char *buffer, size_t buflen)
{
	struct xnb_pkt pkt;
	int nr_entries, nr_reqs;
	size_t size = 14;
	int free_slots = 15;
	RING_IDX start = 3;
	uint16_t id = 49;
	uint16_t gref = 65;
	uint16_t mss = TCP_MSS - 40;
	struct mbuf *mbufc;
	struct netif_rx_request *req;
	struct netif_rx_response *rsp;
	struct netif_extra_info *ext;

	mbufc = m_getm(NULL, size, M_WAITOK, MT_DATA);
	XNB_ASSERT(mbufc != NULL);
	if (mbufc == NULL)
		return;

	mbufc->m_flags |= M_PKTHDR;
	mbufc->m_pkthdr.len = size;
	mbufc->m_pkthdr.csum_flags |= CSUM_TSO;
	mbufc->m_pkthdr.tso_segsz = mss;
	mbufc->m_len = size;

	xnb_mbufc2pkt(mbufc, &pkt, start, free_slots);
	req = RING_GET_REQUEST(&xnb_unit_pvt.rxf, start);
	req->id = id;
	req->gref = gref;
	req = RING_GET_REQUEST(&xnb_unit_pvt.rxf, start + 1);
	req->id = id + 1;
	req->gref = gref + 1;
	xnb_unit_pvt.rxb.req_cons = start;
	xnb_unit_pvt.rxb.rsp_prod_pvt = start;
	xnb_unit_pvt.rxs->req_prod = start + 2;
	xnb_unit_pvt.rxs->rsp_prod = start;

	nr_entries = xnb_rxpkt2gnttab(&pkt, mbufc, xnb_unit_pvt.gnttab,
			&xnb_unit_pvt.rxb, DOMID_FIRST_RESERVED);

	nr_reqs = xnb_rxpkt2rsp(&pkt, xnb_unit_pvt.gnttab, nr_entries,
	    &xnb_unit_pvt.rxb);

	XNB_ASSERT(nr_reqs == 2);
	XNB_ASSERT(xnb_unit_pvt.rxb.rsp_prod_pvt == start + 2);
	rsp = RING_GET_RESPONSE(&xnb_unit_pvt.rxb, start);
	XNB_ASSERT(rsp->id == id);
	XNB_ASSERT((rsp->flags & NETRXF_more_data) == 0);
	XNB_ASSERT((rsp->flags & NETRXF_extra_info));
	XNB_ASSERT((rsp->flags & NETRXF_data_validated));
	XNB_ASSERT((rsp->flags & NETRXF_csum_blank));
	XNB_ASSERT(rsp->status == size);

	ext = (struct netif_extra_info*)
		RING_GET_RESPONSE(&xnb_unit_pvt.rxb, start + 1);
	XNB_ASSERT(ext->type == XEN_NETIF_EXTRA_TYPE_GSO);
	XNB_ASSERT(! (ext->flags & XEN_NETIF_EXTRA_FLAG_MORE));
	XNB_ASSERT(ext->u.gso.size == mss);
	XNB_ASSERT(ext->u.gso.type == XEN_NETIF_EXTRA_TYPE_GSO);

	safe_m_freem(&mbufc);
}