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
struct mbuf {int m_flags; int m_len; int /*<<< orphan*/  m_type; } ;

/* Variables and functions */
 int MCLBYTES ; 
 int MINCLSIZE ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_dup_pkthdr (struct mbuf*,struct mbuf*,int) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 struct mbuf* m_get (int,int /*<<< orphan*/ ) ; 
 struct mbuf* m_getcl (int,int /*<<< orphan*/ ,int) ; 
 struct mbuf* m_gethdr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
m_dup1(struct mbuf *m, int off, int len, int wait)
{
	struct mbuf *n;
	int copyhdr;

	if (len > MCLBYTES)
		return NULL;
	if (off == 0 && (m->m_flags & M_PKTHDR) != 0)
		copyhdr = 1;
	else
		copyhdr = 0;
	if (len >= MINCLSIZE) {
		if (copyhdr == 1)
			n = m_getcl(wait, m->m_type, M_PKTHDR);
		else
			n = m_getcl(wait, m->m_type, 0);
	} else {
		if (copyhdr == 1)
			n = m_gethdr(wait, m->m_type);
		else
			n = m_get(wait, m->m_type);
	}
	if (!n)
		return NULL; /* ENOBUFS */

	if (copyhdr && !m_dup_pkthdr(n, m, wait)) {
		m_free(n);
		return NULL;
	}
	m_copydata(m, off, len, mtod(n, caddr_t));
	n->m_len = len;
	return n;
}