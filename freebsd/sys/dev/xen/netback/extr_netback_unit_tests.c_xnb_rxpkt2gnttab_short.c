#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct xnb_pkt {int dummy; } ;
struct netif_rx_request {int gref; } ;
struct TYPE_8__ {size_t len; } ;
struct mbuf {size_t m_len; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_flags; } ;
struct TYPE_12__ {scalar_t__ offset; scalar_t__ domid; } ;
struct TYPE_10__ {scalar_t__ gmfn; } ;
struct TYPE_11__ {scalar_t__ domid; scalar_t__ offset; TYPE_3__ u; } ;
struct TYPE_14__ {size_t len; int flags; TYPE_5__ dest; TYPE_4__ source; } ;
struct TYPE_9__ {int /*<<< orphan*/  req_prod_pvt; } ;
struct TYPE_13__ {TYPE_7__* gnttab; int /*<<< orphan*/  rxb; TYPE_2__ txf; int /*<<< orphan*/  rxf; } ;
typedef  int RING_IDX ;

/* Variables and functions */
 scalar_t__ DOMID_FIRST_RESERVED ; 
 scalar_t__ DOMID_SELF ; 
 int GNTCOPY_dest_gref ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct netif_rx_request* RING_GET_REQUEST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 struct mbuf* m_getm (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_m_freem (struct mbuf**) ; 
 scalar_t__ virt_to_mfn (int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_offset_t ; 
 int /*<<< orphan*/  xnb_mbufc2pkt (struct mbuf*,struct xnb_pkt*,int,int) ; 
 int xnb_rxpkt2gnttab (struct xnb_pkt*,struct mbuf*,TYPE_7__*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_6__ xnb_unit_pvt ; 

__attribute__((used)) static void
xnb_rxpkt2gnttab_short(char *buffer, size_t buflen) {
	struct xnb_pkt pkt;
	int nr_entries;
	size_t size = 128;
	int free_slots = 60;
	RING_IDX start = 9;
	struct netif_rx_request *req;
	struct mbuf *mbuf;

	mbuf = m_getm(NULL, size, M_WAITOK, MT_DATA);
	mbuf->m_flags |= M_PKTHDR;
	mbuf->m_pkthdr.len = size;
	mbuf->m_len = size;

	xnb_mbufc2pkt(mbuf, &pkt, start, free_slots);
	req = RING_GET_REQUEST(&xnb_unit_pvt.rxf,
			       xnb_unit_pvt.txf.req_prod_pvt);
	req->gref = 7;

	nr_entries = xnb_rxpkt2gnttab(&pkt, mbuf, xnb_unit_pvt.gnttab,
				      &xnb_unit_pvt.rxb, DOMID_FIRST_RESERVED);

	XNB_ASSERT(nr_entries == 1);
	XNB_ASSERT(xnb_unit_pvt.gnttab[0].len == size);
	/* flags should indicate gref's for dest */
	XNB_ASSERT(xnb_unit_pvt.gnttab[0].flags & GNTCOPY_dest_gref);
	XNB_ASSERT(xnb_unit_pvt.gnttab[0].dest.offset == 0);
	XNB_ASSERT(xnb_unit_pvt.gnttab[0].source.domid == DOMID_SELF);
	XNB_ASSERT(xnb_unit_pvt.gnttab[0].source.offset == virt_to_offset(
		   mtod(mbuf, vm_offset_t)));
	XNB_ASSERT(xnb_unit_pvt.gnttab[0].source.u.gmfn ==
		   virt_to_mfn(mtod(mbuf, vm_offset_t)));
	XNB_ASSERT(xnb_unit_pvt.gnttab[0].dest.domid == DOMID_FIRST_RESERVED);

	safe_m_freem(&mbuf);
}