#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int size; int type; } ;
struct TYPE_13__ {TYPE_3__ gso; } ;
struct TYPE_14__ {scalar_t__ flags; scalar_t__ type; TYPE_4__ u; } ;
struct xnb_pkt {int size; int car_size; int flags; int list_len; scalar_t__ car; scalar_t__ cdr; TYPE_5__ extra; } ;
struct netif_tx_request {int flags; int size; } ;
struct TYPE_10__ {int size; scalar_t__ features; void* type; } ;
struct TYPE_11__ {TYPE_1__ gso; } ;
struct netif_extra_info {TYPE_2__ u; scalar_t__ type; scalar_t__ flags; } ;
struct TYPE_16__ {scalar_t__ req_prod_pvt; int /*<<< orphan*/  req_cons; } ;
struct TYPE_15__ {TYPE_7__ txb; TYPE_7__ txf; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int NETTXF_extra_info ; 
 int NETTXF_more_data ; 
 struct netif_tx_request* RING_GET_REQUEST (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS (TYPE_7__*) ; 
 scalar_t__ XEN_NETIF_EXTRA_TYPE_GSO ; 
 void* XEN_NETIF_GSO_TYPE_TCPV4 ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 int xnb_pkt_is_valid (struct xnb_pkt*) ; 
 int xnb_ring2pkt (struct xnb_pkt*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_6__ xnb_unit_pvt ; 

__attribute__((used)) static void
xnb_ring2pkt_extra(char *buffer, size_t buflen)
{
	struct xnb_pkt pkt;
	int num_consumed;
	struct netif_tx_request *req;
	struct netif_extra_info *ext;
	RING_IDX start_idx = xnb_unit_pvt.txf.req_prod_pvt;

	req = RING_GET_REQUEST(&xnb_unit_pvt.txf,
	    xnb_unit_pvt.txf.req_prod_pvt);
	req->flags = NETTXF_extra_info | NETTXF_more_data;
	req->size = 150;
	xnb_unit_pvt.txf.req_prod_pvt++;

	ext = (struct netif_extra_info*) RING_GET_REQUEST(&xnb_unit_pvt.txf,
	    xnb_unit_pvt.txf.req_prod_pvt);
	ext->flags = 0;
	ext->type = XEN_NETIF_EXTRA_TYPE_GSO;
	ext->u.gso.size = 250;
	ext->u.gso.type = XEN_NETIF_GSO_TYPE_TCPV4;
	ext->u.gso.features = 0;
	xnb_unit_pvt.txf.req_prod_pvt++;

	req = RING_GET_REQUEST(&xnb_unit_pvt.txf,
	    xnb_unit_pvt.txf.req_prod_pvt);
	req->flags = 0;
	req->size = 50;
	xnb_unit_pvt.txf.req_prod_pvt++;

	RING_PUSH_REQUESTS(&xnb_unit_pvt.txf);

	num_consumed = xnb_ring2pkt(&pkt, &xnb_unit_pvt.txb,
	                            xnb_unit_pvt.txb.req_cons);
	XNB_ASSERT(num_consumed == 3);
	XNB_ASSERT(pkt.extra.flags == 0);
	XNB_ASSERT(pkt.extra.type == XEN_NETIF_EXTRA_TYPE_GSO);
	XNB_ASSERT(pkt.extra.u.gso.size == 250);
	XNB_ASSERT(pkt.extra.u.gso.type = XEN_NETIF_GSO_TYPE_TCPV4);
	XNB_ASSERT(pkt.size == 150);
	XNB_ASSERT(pkt.car_size == 100);
	XNB_ASSERT(pkt.flags == NETTXF_extra_info);
	XNB_ASSERT(xnb_pkt_is_valid(&pkt));
	XNB_ASSERT(pkt.list_len == 2);
	XNB_ASSERT(pkt.car == start_idx);
	XNB_ASSERT(pkt.cdr == start_idx + 2);
	XNB_ASSERT(RING_GET_REQUEST(&xnb_unit_pvt.txb, pkt.cdr) == req);
}