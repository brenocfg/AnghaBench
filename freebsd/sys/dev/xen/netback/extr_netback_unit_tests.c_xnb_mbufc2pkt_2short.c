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
struct xnb_pkt {size_t size; scalar_t__ car; size_t car_size; int list_len; scalar_t__ cdr; } ;
struct TYPE_2__ {size_t len; } ;
struct mbuf {size_t m_len; int /*<<< orphan*/ * m_next; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_flags; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int MHLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 struct mbuf* m_getm (struct mbuf*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_m_freem (struct mbuf**) ; 
 int /*<<< orphan*/  xnb_mbufc2pkt (struct mbuf*,struct xnb_pkt*,scalar_t__,int) ; 
 int xnb_pkt_is_valid (struct xnb_pkt*) ; 

__attribute__((used)) static void
xnb_mbufc2pkt_2short(char *buffer, size_t buflen) {
	struct xnb_pkt pkt;
	size_t size1 = MHLEN - 5;
	size_t size2 = MHLEN - 15;
	int free_slots = 32;
	RING_IDX start = 14;
	struct mbuf *mbufc, *mbufc2;

	mbufc = m_getm(NULL, size1, M_WAITOK, MT_DATA);
	XNB_ASSERT(mbufc != NULL);
	if (mbufc == NULL)
		return;
	mbufc->m_flags |= M_PKTHDR;

	mbufc2 = m_getm(mbufc, size2, M_WAITOK, MT_DATA);
	XNB_ASSERT(mbufc2 != NULL);
	if (mbufc2 == NULL) {
		safe_m_freem(&mbufc);
		return;
	}
	mbufc2->m_pkthdr.len = size1 + size2;
	mbufc2->m_len = size1;

	xnb_mbufc2pkt(mbufc2, &pkt, start, free_slots);
	XNB_ASSERT(xnb_pkt_is_valid(&pkt));
	XNB_ASSERT(pkt.size == size1 + size2);
	XNB_ASSERT(pkt.car == start);
	/*
	 * The second m_getm may allocate a new mbuf and append
	 * it to the chain, or it may simply extend the first mbuf.
	 */
	if (mbufc2->m_next != NULL) {
		XNB_ASSERT(pkt.car_size == size1);
		XNB_ASSERT(pkt.list_len == 1);
		XNB_ASSERT(pkt.cdr == start + 1);
	}

	safe_m_freem(&mbufc2);
}