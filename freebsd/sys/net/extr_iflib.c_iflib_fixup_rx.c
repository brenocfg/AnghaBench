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
struct mbuf {scalar_t__ m_len; scalar_t__ m_data; struct mbuf* m_next; } ;

/* Variables and functions */
 scalar_t__ ETHER_HDR_LEN ; 
 scalar_t__ MCLBYTES ; 
 int /*<<< orphan*/  MGETHDR (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_MOVE_PKTHDR (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bcopy (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static struct mbuf *
iflib_fixup_rx(struct mbuf *m)
{
	struct mbuf *n;

	if (m->m_len <= (MCLBYTES - ETHER_HDR_LEN)) {
		bcopy(m->m_data, m->m_data + ETHER_HDR_LEN, m->m_len);
		m->m_data += ETHER_HDR_LEN;
		n = m;
	} else {
		MGETHDR(n, M_NOWAIT, MT_DATA);
		if (n == NULL) {
			m_freem(m);
			return (NULL);
		}
		bcopy(m->m_data, n->m_data, ETHER_HDR_LEN);
		m->m_data += ETHER_HDR_LEN;
		m->m_len -= ETHER_HDR_LEN;
		n->m_len = ETHER_HDR_LEN;
		M_MOVE_PKTHDR(n, m);
		n->m_next = m;
	}
	return (n);
}