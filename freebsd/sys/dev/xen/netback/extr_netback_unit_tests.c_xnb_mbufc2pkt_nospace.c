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
struct TYPE_2__ {size_t len; } ;
struct mbuf {scalar_t__ m_len; struct mbuf* m_next; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_flags; } ;
typedef  int RING_IDX ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ MAX (int /*<<< orphan*/ ,size_t) ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_TRAILINGSPACE (struct mbuf*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 struct mbuf* m_getm (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_m_freem (struct mbuf**) ; 
 int xnb_mbufc2pkt (struct mbuf*,struct xnb_pkt*,int,int) ; 
 int /*<<< orphan*/  xnb_pkt_is_valid (struct xnb_pkt*) ; 

__attribute__((used)) static void
xnb_mbufc2pkt_nospace(char *buffer, size_t buflen) {
	struct xnb_pkt pkt;
	size_t size = 14 * MCLBYTES / 3;
	size_t size_remaining;
	int free_slots = 2;
	RING_IDX start = 3;
	struct mbuf *mbufc, *m;
	int error;

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

	error = xnb_mbufc2pkt(mbufc, &pkt, start, free_slots);
	XNB_ASSERT(error == EAGAIN);
	XNB_ASSERT(! xnb_pkt_is_valid(&pkt));

	safe_m_freem(&mbufc);
}