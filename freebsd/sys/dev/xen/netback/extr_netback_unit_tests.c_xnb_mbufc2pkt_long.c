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
struct xnb_pkt {size_t size; scalar_t__ car; int car_size; int flags; scalar_t__ cdr; } ;
struct TYPE_2__ {size_t len; } ;
struct mbuf {int m_len; struct mbuf* m_next; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_flags; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int MAX (int /*<<< orphan*/ ,size_t) ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_TRAILINGSPACE (struct mbuf*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int NETRXF_extra_info ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 struct mbuf* m_getm (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_m_freem (struct mbuf**) ; 
 int /*<<< orphan*/  xnb_mbufc2pkt (struct mbuf*,struct xnb_pkt*,scalar_t__,int) ; 
 int xnb_pkt_is_valid (struct xnb_pkt*) ; 

__attribute__((used)) static void
xnb_mbufc2pkt_long(char *buffer, size_t buflen) {
	struct xnb_pkt pkt;
	size_t size = 14 * MCLBYTES / 3;
	size_t size_remaining;
	int free_slots = 15;
	RING_IDX start = 3;
	struct mbuf *mbufc, *m;

	mbufc = m_getm(NULL, size, M_WAITOK, MT_DATA);
	XNB_ASSERT(mbufc != NULL);
	if (mbufc == NULL)
		return;
	mbufc->m_flags |= M_PKTHDR;

	mbufc->m_pkthdr.len = size;
	size_remaining = size;
	for (m = mbufc; m != NULL; m = m->m_next) {
		m->m_len = MAX(M_TRAILINGSPACE(m), size_remaining);
		size_remaining -= m->m_len;
	}

	xnb_mbufc2pkt(mbufc, &pkt, start, free_slots);
	XNB_ASSERT(xnb_pkt_is_valid(&pkt));
	XNB_ASSERT(pkt.size == size);
	XNB_ASSERT(pkt.car == start);
	XNB_ASSERT(pkt.car_size = mbufc->m_len);
	/*
	 * There should be >1 response in the packet, and there is no
	 * extra info.
	 */
	XNB_ASSERT(! (pkt.flags & NETRXF_extra_info));
	XNB_ASSERT(pkt.cdr == pkt.car + 1);

	safe_m_freem(&mbufc);
}