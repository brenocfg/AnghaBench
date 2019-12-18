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
struct TYPE_2__ {scalar_t__ rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct m_tag {int dummy; } ;
typedef  unsigned short sa_family_t ;

/* Variables and functions */
 unsigned short AF_UNSPEC ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NETISR_ROUTE ; 
 int /*<<< orphan*/  PACKET_TAG_RTSOCKFAM ; 
 scalar_t__ V_loif ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct m_tag* m_tag_get (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 
 int /*<<< orphan*/  netisr_queue (int /*<<< orphan*/ ,struct mbuf*) ; 

__attribute__((used)) static void
rt_dispatch(struct mbuf *m, sa_family_t saf)
{
	struct m_tag *tag;

	/*
	 * Preserve the family from the sockaddr, if any, in an m_tag for
	 * use when injecting the mbuf into the routing socket buffer from
	 * the netisr.
	 */
	if (saf != AF_UNSPEC) {
		tag = m_tag_get(PACKET_TAG_RTSOCKFAM, sizeof(unsigned short),
		    M_NOWAIT);
		if (tag == NULL) {
			m_freem(m);
			return;
		}
		*(unsigned short *)(tag + 1) = saf;
		m_tag_prepend(m, tag);
	}
#ifdef VIMAGE
	if (V_loif)
		m->m_pkthdr.rcvif = V_loif;
	else {
		m_freem(m);
		return;
	}
#endif
	netisr_queue(NETISR_ROUTE, m);	/* mbuf is free'd on failure. */
}