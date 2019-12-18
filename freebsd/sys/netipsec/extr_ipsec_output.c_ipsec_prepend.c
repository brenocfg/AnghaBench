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
struct mbuf {int m_data; int m_len; TYPE_1__ m_pkthdr; struct mbuf* m_next; int /*<<< orphan*/  m_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSEC_ASSERT (int,char*) ; 
 scalar_t__ IPSEC_TRAILINGSPACE ; 
 int MHLEN ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int M_LEADINGSPACE (struct mbuf*) ; 
 scalar_t__ M_SIZE (struct mbuf*) ; 
 int /*<<< orphan*/  m_align (struct mbuf*,scalar_t__) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_gethdr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_move_pkthdr (struct mbuf*,struct mbuf*) ; 

__attribute__((used)) static struct mbuf *
ipsec_prepend(struct mbuf *m, int len, int how)
{
	struct mbuf *n;

	M_ASSERTPKTHDR(m);
	IPSEC_ASSERT(len < MHLEN, ("wrong length"));
	if (M_LEADINGSPACE(m) >= len) {
		/* No need to allocate new mbuf. */
		m->m_data -= len;
		m->m_len += len;
		m->m_pkthdr.len += len;
		return (m);
	}
	n = m_gethdr(how, m->m_type);
	if (n == NULL) {
		m_freem(m);
		return (NULL);
	}
	m_move_pkthdr(n, m);
	n->m_next = m;
	if (len + IPSEC_TRAILINGSPACE < M_SIZE(n))
		m_align(n, len + IPSEC_TRAILINGSPACE);
	n->m_len = len;
	n->m_pkthdr.len += len;
	return (n);
}