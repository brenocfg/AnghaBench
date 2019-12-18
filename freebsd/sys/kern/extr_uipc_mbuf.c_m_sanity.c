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
struct TYPE_2__ {int len; int /*<<< orphan*/  tags; } ;
struct mbuf {scalar_t__ m_len; int m_flags; TYPE_1__ m_pkthdr; struct mbuf* m_nextpkt; scalar_t__ m_data; struct mbuf* m_next; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int M_PKTHDR ; 
 int /*<<< orphan*/  M_SANITY_ACTION (char*) ; 
 scalar_t__ M_SIZE (struct mbuf*) ; 
 scalar_t__ M_START (struct mbuf*) ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_tag_delete_chain (struct mbuf*,int /*<<< orphan*/ *) ; 

int
m_sanity(struct mbuf *m0, int sanitize)
{
	struct mbuf *m;
	caddr_t a, b;
	int pktlen = 0;

#ifdef INVARIANTS
#define	M_SANITY_ACTION(s)	panic("mbuf %p: " s, m)
#else
#define	M_SANITY_ACTION(s)	printf("mbuf %p: " s, m)
#endif

	for (m = m0; m != NULL; m = m->m_next) {
		/*
		 * Basic pointer checks.  If any of these fails then some
		 * unrelated kernel memory before or after us is trashed.
		 * No way to recover from that.
		 */
		a = M_START(m);
		b = a + M_SIZE(m);
		if ((caddr_t)m->m_data < a)
			M_SANITY_ACTION("m_data outside mbuf data range left");
		if ((caddr_t)m->m_data > b)
			M_SANITY_ACTION("m_data outside mbuf data range right");
		if ((caddr_t)m->m_data + m->m_len > b)
			M_SANITY_ACTION("m_data + m_len exeeds mbuf space");

		/* m->m_nextpkt may only be set on first mbuf in chain. */
		if (m != m0 && m->m_nextpkt != NULL) {
			if (sanitize) {
				m_freem(m->m_nextpkt);
				m->m_nextpkt = (struct mbuf *)0xDEADC0DE;
			} else
				M_SANITY_ACTION("m->m_nextpkt on in-chain mbuf");
		}

		/* packet length (not mbuf length!) calculation */
		if (m0->m_flags & M_PKTHDR)
			pktlen += m->m_len;

		/* m_tags may only be attached to first mbuf in chain. */
		if (m != m0 && m->m_flags & M_PKTHDR &&
		    !SLIST_EMPTY(&m->m_pkthdr.tags)) {
			if (sanitize) {
				m_tag_delete_chain(m, NULL);
				/* put in 0xDEADC0DE perhaps? */
			} else
				M_SANITY_ACTION("m_tags on in-chain mbuf");
		}

		/* M_PKTHDR may only be set on first mbuf in chain */
		if (m != m0 && m->m_flags & M_PKTHDR) {
			if (sanitize) {
				bzero(&m->m_pkthdr, sizeof(m->m_pkthdr));
				m->m_flags &= ~M_PKTHDR;
				/* put in 0xDEADCODE and leave hdr flag in */
			} else
				M_SANITY_ACTION("M_PKTHDR on in-chain mbuf");
		}
	}
	m = m0;
	if (pktlen && pktlen != m->m_pkthdr.len) {
		if (sanitize)
			m->m_pkthdr.len = 0;
		else
			M_SANITY_ACTION("m_pkthdr.len != mbuf chain length");
	}
	return 1;

#undef	M_SANITY_ACTION
}