#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xnb_pkt {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  rxs_backup ;
typedef  int /*<<< orphan*/  rxb_backup ;
typedef  int /*<<< orphan*/  netif_rx_sring_t ;
typedef  int /*<<< orphan*/  netif_rx_back_ring_t ;
struct TYPE_2__ {int /*<<< orphan*/ * rxs; int /*<<< orphan*/  rxb; int /*<<< orphan*/  gnttab; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_FIRST_RESERVED ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 struct mbuf* m_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  safe_m_freem (struct mbuf**) ; 
 int /*<<< orphan*/  xnb_mbufc2pkt (struct mbuf*,struct xnb_pkt*,int /*<<< orphan*/ ,int) ; 
 int xnb_rxpkt2gnttab (struct xnb_pkt*,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xnb_rxpkt2rsp (struct xnb_pkt*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_1__ xnb_unit_pvt ; 

__attribute__((used)) static void
xnb_rxpkt2rsp_empty(char *buffer, size_t buflen)
{
	struct xnb_pkt pkt;
	int nr_entries;
	int nr_reqs;
	int free_slots = 60;
	netif_rx_back_ring_t rxb_backup = xnb_unit_pvt.rxb;
	netif_rx_sring_t rxs_backup = *xnb_unit_pvt.rxs;
	struct mbuf *mbuf;

	mbuf = m_get(M_WAITOK, MT_DATA);

	xnb_mbufc2pkt(mbuf, &pkt, 0, free_slots);
	nr_entries = xnb_rxpkt2gnttab(&pkt, mbuf, xnb_unit_pvt.gnttab,
			&xnb_unit_pvt.rxb, DOMID_FIRST_RESERVED);

	nr_reqs = xnb_rxpkt2rsp(&pkt, xnb_unit_pvt.gnttab, nr_entries,
	    &xnb_unit_pvt.rxb);
	XNB_ASSERT(nr_reqs == 0);
	XNB_ASSERT(
	    memcmp(&rxb_backup, &xnb_unit_pvt.rxb, sizeof(rxb_backup)) == 0);
	XNB_ASSERT(
	    memcmp(&rxs_backup, xnb_unit_pvt.rxs, sizeof(rxs_backup)) == 0);

	safe_m_freem(&mbuf);
}