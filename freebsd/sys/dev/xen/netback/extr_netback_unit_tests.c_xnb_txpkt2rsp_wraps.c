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
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct xnb_pkt {int dummy; } ;
struct netif_tx_response {int id; scalar_t__ status; } ;
struct netif_tx_request {int size; int id; void* flags; } ;
struct TYPE_12__ {unsigned int req_prod_pvt; unsigned int rsp_cons; } ;
struct TYPE_11__ {unsigned int rsp_prod_pvt; unsigned int req_cons; } ;
struct TYPE_10__ {TYPE_5__ txf; TYPE_3__ txb; TYPE_1__* txs; } ;
struct TYPE_9__ {unsigned int req_prod; unsigned int req_event; unsigned int rsp_prod; unsigned int rsp_event; } ;

/* Variables and functions */
 scalar_t__ NETIF_RSP_OKAY ; 
 void* NETTXF_more_data ; 
 struct netif_tx_request* RING_GET_REQUEST (TYPE_5__*,unsigned int) ; 
 struct netif_tx_response* RING_GET_RESPONSE (TYPE_3__*,int) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS (TYPE_5__*) ; 
 unsigned int RING_SIZE (TYPE_5__*) ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 int xnb_ring2pkt (struct xnb_pkt*,TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  xnb_txpkt2rsp (struct xnb_pkt*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ xnb_unit_pvt ; 

__attribute__((used)) static void
xnb_txpkt2rsp_wraps(char *buffer, size_t buflen)
{
	struct xnb_pkt pkt;
	int num_consumed;
	struct netif_tx_request *req;
	struct netif_tx_response *rsp;
	unsigned int rsize;

	/*
	 * Manually tweak the ring indices to create a ring with no responses
	 * and the next request slot at position 2 from the end
	 */
	rsize = RING_SIZE(&xnb_unit_pvt.txf);
	xnb_unit_pvt.txf.req_prod_pvt = rsize - 2;
	xnb_unit_pvt.txf.rsp_cons = rsize - 2;
	xnb_unit_pvt.txs->req_prod = rsize - 2;
	xnb_unit_pvt.txs->req_event = rsize - 1;
	xnb_unit_pvt.txs->rsp_prod = rsize - 2;
	xnb_unit_pvt.txs->rsp_event = rsize - 1;
	xnb_unit_pvt.txb.rsp_prod_pvt = rsize - 2;
	xnb_unit_pvt.txb.req_cons = rsize - 2;

	req = RING_GET_REQUEST(&xnb_unit_pvt.txf,
	    xnb_unit_pvt.txf.req_prod_pvt);
	req->flags = NETTXF_more_data;
	req->size = 550;
	req->id = 1;
	xnb_unit_pvt.txf.req_prod_pvt++;

	req = RING_GET_REQUEST(&xnb_unit_pvt.txf,
	    xnb_unit_pvt.txf.req_prod_pvt);
	req->flags = NETTXF_more_data;
	req->size = 100;
	req->id = 2;
	xnb_unit_pvt.txf.req_prod_pvt++;

	req = RING_GET_REQUEST(&xnb_unit_pvt.txf,
	    xnb_unit_pvt.txf.req_prod_pvt);
	req->flags = 0;
	req->size = 50;
	req->id = 3;
	xnb_unit_pvt.txf.req_prod_pvt++;

	RING_PUSH_REQUESTS(&xnb_unit_pvt.txf);

	num_consumed = xnb_ring2pkt(&pkt, &xnb_unit_pvt.txb,
	                            xnb_unit_pvt.txb.req_cons);

	xnb_txpkt2rsp(&pkt, &xnb_unit_pvt.txb, 0);

	XNB_ASSERT(
	    xnb_unit_pvt.txb.rsp_prod_pvt == xnb_unit_pvt.txs->req_prod);
	rsp = RING_GET_RESPONSE(&xnb_unit_pvt.txb,
	    xnb_unit_pvt.txf.rsp_cons + 2);
	XNB_ASSERT(rsp->id == req->id);
	XNB_ASSERT(rsp->status == NETIF_RSP_OKAY);
}