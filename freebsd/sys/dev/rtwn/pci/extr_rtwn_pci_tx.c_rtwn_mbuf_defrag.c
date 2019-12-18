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
struct TYPE_2__ {scalar_t__ len; } ;
struct mbuf {int m_flags; scalar_t__ m_len; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MCLBYTES ; 
 scalar_t__ MJUMPAGESIZE ; 
 int /*<<< orphan*/  MT_DATA ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mbuf* m_defrag (struct mbuf*,int) ; 
 scalar_t__ m_dup_pkthdr (struct mbuf*,struct mbuf*,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_getjcl (int,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
rtwn_mbuf_defrag(struct mbuf *m0, int how)
{
	struct mbuf *m = NULL;

	KASSERT(m0->m_flags & M_PKTHDR,
	    ("M_PKTHDR flag is absent (m %p)!", m0));

	/* NB: we need _exactly_ one mbuf (no less, no more). */
	if (m0->m_pkthdr.len > MJUMPAGESIZE) {
		/* XXX MJUM9BYTES? */
		return (NULL);
	} else if (m0->m_pkthdr.len > MCLBYTES) {
		m = m_getjcl(how, MT_DATA, M_PKTHDR, MJUMPAGESIZE);
		if (m == NULL)
			return (NULL);

		if (m_dup_pkthdr(m, m0, how) == 0) {
			m_freem(m);
			return (NULL);
		}

		m_copydata(m0, 0, m0->m_pkthdr.len, mtod(m, caddr_t));
		m->m_len = m->m_pkthdr.len;
		m_freem(m0);

		return (m);
	} else
		return (m_defrag(m0, how));
}