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
typedef  void u_char ;
struct TYPE_2__ {size_t len; } ;
struct mbuf {size_t m_len; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_data; struct mbuf* m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t MCLBYTES ; 
 int /*<<< orphan*/  MGET (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGETHDR (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MHLEN ; 
 size_t MLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bcopy (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_getcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
pack_buf(void *h, size_t hlen, void *t, size_t tlen)
{
	struct mbuf *m, *m0, *last;
	u_char *buf = (u_char *)t;
	size_t n;

	/* header should fit into a normal mbuf */
	MGETHDR(m0, M_NOWAIT, MT_DATA);
	if (m0 == NULL)
		return NULL;

	KASSERT(hlen <= MHLEN, ("hlen > MHLEN"));

	bcopy(h, m0->m_data, hlen);
	m0->m_len = hlen;
	m0->m_pkthdr.len = hlen;

	last = m0;
	while ((n = tlen) != 0) {
		if (n > MLEN) {
			m = m_getcl(M_NOWAIT, MT_DATA, 0);
			if (n > MCLBYTES)
				n = MCLBYTES;
		} else
			MGET(m, M_NOWAIT, MT_DATA);

		if(m == NULL)
			goto drop;

		last->m_next = m;
		last = m;

		bcopy(buf, m->m_data, n);
		buf += n;
		tlen -= n;
		m->m_len = n;
		m0->m_pkthdr.len += n;
	}

	return (m0);

  drop:
	m_freem(m0);
	return NULL;
}