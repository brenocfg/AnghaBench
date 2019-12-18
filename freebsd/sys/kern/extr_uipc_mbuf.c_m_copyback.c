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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int len; } ;
struct mbuf {int m_len; int m_flags; TYPE_1__ m_pkthdr; struct mbuf* m_next; int /*<<< orphan*/  m_type; } ;
typedef  int c_caddr_t ;

/* Variables and functions */
 int MLEN ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_PKTHDR ; 
 int M_TRAILINGSPACE (struct mbuf*) ; 
 int /*<<< orphan*/  bcopy (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 int /*<<< orphan*/  caddr_t ; 
 struct mbuf* m_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* min (int,int) ; 
 scalar_t__ mtod (struct mbuf*,int /*<<< orphan*/ ) ; 

void
m_copyback(struct mbuf *m0, int off, int len, c_caddr_t cp)
{
	int mlen;
	struct mbuf *m = m0, *n;
	int totlen = 0;

	if (m0 == NULL)
		return;
	while (off > (mlen = m->m_len)) {
		off -= mlen;
		totlen += mlen;
		if (m->m_next == NULL) {
			n = m_get(M_NOWAIT, m->m_type);
			if (n == NULL)
				goto out;
			bzero(mtod(n, caddr_t), MLEN);
			n->m_len = min(MLEN, len + off);
			m->m_next = n;
		}
		m = m->m_next;
	}
	while (len > 0) {
		if (m->m_next == NULL && (len > m->m_len - off)) {
			m->m_len += min(len - (m->m_len - off),
			    M_TRAILINGSPACE(m));
		}
		mlen = min (m->m_len - off, len);
		bcopy(cp, off + mtod(m, caddr_t), (u_int)mlen);
		cp += mlen;
		len -= mlen;
		mlen += off;
		off = 0;
		totlen += mlen;
		if (len == 0)
			break;
		if (m->m_next == NULL) {
			n = m_get(M_NOWAIT, m->m_type);
			if (n == NULL)
				break;
			n->m_len = min(MLEN, len);
			m->m_next = n;
		}
		m = m->m_next;
	}
out:	if (((m = m0)->m_flags & M_PKTHDR) && (m->m_pkthdr.len < totlen))
		m->m_pkthdr.len = totlen;
}