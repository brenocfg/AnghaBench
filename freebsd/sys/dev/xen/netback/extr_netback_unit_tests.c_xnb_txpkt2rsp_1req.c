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
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct xnb_pkt {int dummy; } ;
struct netif_tx_response {scalar_t__ id; scalar_t__ status; } ;
struct netif_tx_request {int size; scalar_t__ id; scalar_t__ flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  rsp_cons; int /*<<< orphan*/  req_prod_pvt; } ;
struct TYPE_10__ {scalar_t__ rsp_prod_pvt; int /*<<< orphan*/  req_cons; } ;
struct TYPE_9__ {TYPE_1__* txs; TYPE_3__ txb; TYPE_5__ txf; } ;
struct TYPE_8__ {scalar_t__ req_prod; } ;

/* Variables and functions */
 scalar_t__ NETIF_RSP_OKAY ; 
 struct netif_tx_request* RING_GET_REQUEST (TYPE_5__*,int /*<<< orphan*/ ) ; 
 struct netif_tx_response* RING_GET_RESPONSE (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS (TYPE_5__*) ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 scalar_t__ xnb_ring2pkt (struct xnb_pkt*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xnb_txpkt2rsp (struct xnb_pkt*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ xnb_unit_pvt ; 

__attribute__((used)) static void
xnb_txpkt2rsp_1req(char *buffer, size_t buflen)
{
	uint16_t num_consumed;
	struct xnb_pkt pkt;
	struct netif_tx_request *req;
	struct netif_tx_response *rsp;

	req = RING_GET_REQUEST(&xnb_unit_pvt.txf,
	    xnb_unit_pvt.txf.req_prod_pvt);
	req->size = 1000;
	req->flags = 0;
	xnb_unit_pvt.txf.req_prod_pvt++;

	RING_PUSH_REQUESTS(&xnb_unit_pvt.txf);

	num_consumed = xnb_ring2pkt(&pkt, &xnb_unit_pvt.txb,
	                            xnb_unit_pvt.txb.req_cons);
	xnb_unit_pvt.txb.req_cons += num_consumed;

	xnb_txpkt2rsp(&pkt, &xnb_unit_pvt.txb, 0);
	rsp = RING_GET_RESPONSE(&xnb_unit_pvt.txb, xnb_unit_pvt.txf.rsp_cons);

	XNB_ASSERT(
	    xnb_unit_pvt.txb.rsp_prod_pvt == xnb_unit_pvt.txs->req_prod);
	XNB_ASSERT(rsp->id == req->id);
	XNB_ASSERT(rsp->status == NETIF_RSP_OKAY);
}