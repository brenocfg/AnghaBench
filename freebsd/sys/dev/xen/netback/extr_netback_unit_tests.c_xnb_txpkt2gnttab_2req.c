#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct xnb_pkt {int dummy; } ;
struct netif_tx_request {int size; int gref; scalar_t__ offset; scalar_t__ flags; } ;
struct mbuf {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  req_prod_pvt; } ;
struct TYPE_11__ {int /*<<< orphan*/  req_cons; } ;
struct TYPE_8__ {scalar_t__ offset; } ;
struct TYPE_10__ {int len; TYPE_1__ dest; } ;
struct TYPE_9__ {TYPE_3__* gnttab; TYPE_4__ txb; int /*<<< orphan*/  ifp; TYPE_6__ txf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_FIRST_RESERVED ; 
 scalar_t__ NETTXF_more_data ; 
 struct netif_tx_request* RING_GET_REQUEST (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS (TYPE_6__*) ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 scalar_t__ mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_m_freem (struct mbuf**) ; 
 scalar_t__ virt_to_offset (scalar_t__) ; 
 int /*<<< orphan*/  vm_offset_t ; 
 struct mbuf* xnb_pkt2mbufc (struct xnb_pkt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xnb_ring2pkt (struct xnb_pkt*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int xnb_txpkt2gnttab (struct xnb_pkt*,struct mbuf*,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ xnb_unit_pvt ; 

__attribute__((used)) static void
xnb_txpkt2gnttab_2req(char *buffer, size_t buflen)
{
	int n_entries;
	struct xnb_pkt pkt;
	struct mbuf *pMbuf;

	struct netif_tx_request *req = RING_GET_REQUEST(&xnb_unit_pvt.txf,
	    xnb_unit_pvt.txf.req_prod_pvt);
	req->flags = NETTXF_more_data;
	req->size = 1900;
	req->gref = 7;
	req->offset = 0;
	xnb_unit_pvt.txf.req_prod_pvt++;

	req = RING_GET_REQUEST(&xnb_unit_pvt.txf,
	    xnb_unit_pvt.txf.req_prod_pvt);
	req->flags = 0;
	req->size = 500;
	req->gref = 8;
	req->offset = 0;
	xnb_unit_pvt.txf.req_prod_pvt++;

	RING_PUSH_REQUESTS(&xnb_unit_pvt.txf);

	xnb_ring2pkt(&pkt, &xnb_unit_pvt.txb, xnb_unit_pvt.txb.req_cons);

	pMbuf = xnb_pkt2mbufc(&pkt, xnb_unit_pvt.ifp);
	n_entries = xnb_txpkt2gnttab(&pkt, pMbuf, xnb_unit_pvt.gnttab,
	    &xnb_unit_pvt.txb, DOMID_FIRST_RESERVED);

	XNB_ASSERT(n_entries == 2);
	XNB_ASSERT(xnb_unit_pvt.gnttab[0].len == 1400);
	XNB_ASSERT(xnb_unit_pvt.gnttab[0].dest.offset == virt_to_offset(
	      mtod(pMbuf, vm_offset_t)));

	XNB_ASSERT(xnb_unit_pvt.gnttab[1].len == 500);
	XNB_ASSERT(xnb_unit_pvt.gnttab[1].dest.offset == virt_to_offset(
	      mtod(pMbuf, vm_offset_t) + 1400));
	safe_m_freem(&pMbuf);
}