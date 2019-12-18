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
struct TYPE_2__ {int len; } ;
struct mbuf {int m_flags; int m_len; TYPE_1__ m_pkthdr; int /*<<< orphan*/ * m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_CHECKSLEEP (int) ; 
 int MCLBYTES ; 
 int MHLEN ; 
 int MLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int M_PKTHDR ; 
 int arc4random () ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  m_cat (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int,int,int /*<<< orphan*/ ) ; 
 int m_defragbytes ; 
 int /*<<< orphan*/  m_defragfailure ; 
 int /*<<< orphan*/  m_defragpackets ; 
 scalar_t__ m_defragrandomfailures ; 
 int /*<<< orphan*/  m_defraguseless ; 
 scalar_t__ m_dup_pkthdr (struct mbuf*,struct mbuf*,int) ; 
 int /*<<< orphan*/  m_fixhdr (struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_get (int,int /*<<< orphan*/ ) ; 
 struct mbuf* m_getcl (int,int /*<<< orphan*/ ,int) ; 
 struct mbuf* m_gethdr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 

struct mbuf *
m_defrag(struct mbuf *m0, int how)
{
	struct mbuf *m_new = NULL, *m_final = NULL;
	int progress = 0, length;

	MBUF_CHECKSLEEP(how);
	if (!(m0->m_flags & M_PKTHDR))
		return (m0);

	m_fixhdr(m0); /* Needed sanity check */

#ifdef MBUF_STRESS_TEST
	if (m_defragrandomfailures) {
		int temp = arc4random() & 0xff;
		if (temp == 0xba)
			goto nospace;
	}
#endif

	if (m0->m_pkthdr.len > MHLEN)
		m_final = m_getcl(how, MT_DATA, M_PKTHDR);
	else
		m_final = m_gethdr(how, MT_DATA);

	if (m_final == NULL)
		goto nospace;

	if (m_dup_pkthdr(m_final, m0, how) == 0)
		goto nospace;

	m_new = m_final;

	while (progress < m0->m_pkthdr.len) {
		length = m0->m_pkthdr.len - progress;
		if (length > MCLBYTES)
			length = MCLBYTES;

		if (m_new == NULL) {
			if (length > MLEN)
				m_new = m_getcl(how, MT_DATA, 0);
			else
				m_new = m_get(how, MT_DATA);
			if (m_new == NULL)
				goto nospace;
		}

		m_copydata(m0, progress, length, mtod(m_new, caddr_t));
		progress += length;
		m_new->m_len = length;
		if (m_new != m_final)
			m_cat(m_final, m_new);
		m_new = NULL;
	}
#ifdef MBUF_STRESS_TEST
	if (m0->m_next == NULL)
		m_defraguseless++;
#endif
	m_freem(m0);
	m0 = m_final;
#ifdef MBUF_STRESS_TEST
	m_defragpackets++;
	m_defragbytes += m0->m_pkthdr.len;
#endif
	return (m0);
nospace:
#ifdef MBUF_STRESS_TEST
	m_defragfailure++;
#endif
	if (m_final)
		m_freem(m_final);
	return (NULL);
}