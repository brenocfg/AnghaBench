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
struct xnb_pkt {size_t size; size_t car_size; int flags; int list_len; scalar_t__ car; } ;
struct TYPE_2__ {size_t len; } ;
struct mbuf {size_t m_len; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_flags; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 size_t MCLBYTES ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int NETRXF_extra_info ; 
 int NETRXF_more_data ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 struct mbuf* m_getm (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_m_freem (struct mbuf**) ; 
 int /*<<< orphan*/  xnb_mbufc2pkt (struct mbuf*,struct xnb_pkt*,scalar_t__,int) ; 
 int xnb_pkt_is_valid (struct xnb_pkt*) ; 

__attribute__((used)) static void
xnb_mbufc2pkt_1cluster(char *buffer, size_t buflen) {
	struct xnb_pkt pkt;
	size_t size = MCLBYTES;
	int free_slots = 32;
	RING_IDX start = 12;
	struct mbuf *mbuf;

	mbuf = m_getm(NULL, size, M_WAITOK, MT_DATA);
	mbuf->m_flags |= M_PKTHDR;
	mbuf->m_pkthdr.len = size;
	mbuf->m_len = size;

	xnb_mbufc2pkt(mbuf, &pkt, start, free_slots);
	XNB_ASSERT(xnb_pkt_is_valid(&pkt));
	XNB_ASSERT(pkt.size == size);
	XNB_ASSERT(pkt.car_size == size);
	XNB_ASSERT(! (pkt.flags &
	      (NETRXF_more_data | NETRXF_extra_info)));
	XNB_ASSERT(pkt.list_len == 1);
	XNB_ASSERT(pkt.car == start);

	safe_m_freem(&mbuf);
}