#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct xnb_pkt {int dummy; } ;
struct netif_tx_request {size_t size; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  req_prod_pvt; } ;
struct TYPE_6__ {int /*<<< orphan*/  req_cons; } ;
struct TYPE_5__ {TYPE_2__ txb; TYPE_3__ txf; } ;

/* Variables and functions */
 struct netif_tx_request* RING_GET_REQUEST (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS (TYPE_3__*) ; 
 int xnb_ring2pkt (struct xnb_pkt*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ xnb_unit_pvt ; 

__attribute__((used)) static int
xnb_get1pkt(struct xnb_pkt *pkt, size_t size, uint16_t flags)
{
	struct netif_tx_request *req;

	req = RING_GET_REQUEST(&xnb_unit_pvt.txf,
	    xnb_unit_pvt.txf.req_prod_pvt);
	req->flags = flags;
	req->size = size;
	xnb_unit_pvt.txf.req_prod_pvt++;

	RING_PUSH_REQUESTS(&xnb_unit_pvt.txf);

	return xnb_ring2pkt(pkt, &xnb_unit_pvt.txb,
	                            xnb_unit_pvt.txb.req_cons);
}