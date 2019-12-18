#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xnb_pkt {scalar_t__ size; scalar_t__ list_len; } ;
struct mbuf {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  req_cons; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifp; TYPE_2__ txb; } ;

/* Variables and functions */
 int /*<<< orphan*/  safe_m_freem (struct mbuf**) ; 
 struct mbuf* xnb_pkt2mbufc (struct xnb_pkt*,int /*<<< orphan*/ ) ; 
 int xnb_ring2pkt (struct xnb_pkt*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ xnb_unit_pvt ; 

__attribute__((used)) static void
xnb_pkt2mbufc_empty(char *buffer, size_t buflen)
{
	int num_consumed;
	struct xnb_pkt pkt;
	struct mbuf *pMbuf;
	pkt.list_len = 0;

	/* must call xnb_ring2pkt just to intialize pkt */
	num_consumed = xnb_ring2pkt(&pkt, &xnb_unit_pvt.txb,
	                            xnb_unit_pvt.txb.req_cons);
	pkt.size = 0;
	pMbuf = xnb_pkt2mbufc(&pkt, xnb_unit_pvt.ifp);
	safe_m_freem(&pMbuf);
}