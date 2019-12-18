#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mq {struct mbuf* tail; int /*<<< orphan*/  count; struct mbuf* head; } ;
struct mbuf {int m_flags; int m_data; int __m_extbuf; int __m_extlen; struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGETHDR (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_STACK ; 
 int /*<<< orphan*/  ND (char*,struct mbuf*,...) ; 
 int /*<<< orphan*/  _pkt_copy (int,void*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static inline void
mq_append(struct mq *q, struct mbuf *m)
{
#ifdef USERSPACE
	// buffers from netmap need to be copied
	// XXX note that the routine is not expected to fail
	ND("append %p to %p", m, q);
	if (m->m_flags & M_STACK) {
		struct mbuf *m_new;
		void *p;
		int l, ofs;

		ofs = m->m_data - m->__m_extbuf;
		// XXX allocate
		MGETHDR(m_new, M_NOWAIT, MT_DATA);
		ND("*** WARNING, volatile buf %p ext %p %d dofs %d m_new %p",
			m, m->__m_extbuf, m->__m_extlen, ofs, m_new);
		p = m_new->__m_extbuf;	/* new pointer */
		l = m_new->__m_extlen;	/* new len */
		if (l <= m->__m_extlen) {
			panic("extlen too large");
		}

		*m_new = *m;	// copy
		m_new->m_flags &= ~M_STACK;
		m_new->__m_extbuf = p; // point to new buffer
		_pkt_copy(m->__m_extbuf, p, m->__m_extlen);
		m_new->m_data = p + ofs;
		m = m_new;
	}
#endif /* USERSPACE */
	if (q->head == NULL)
		q->head = m;
	else
		q->tail->m_nextpkt = m;
	q->count++;
	q->tail = m;
	m->m_nextpkt = NULL;
}