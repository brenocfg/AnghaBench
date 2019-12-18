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
struct sockaddr_in6 {int dummy; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int nd6_output_ifp (struct ifnet*,struct ifnet*,struct mbuf*,struct sockaddr_in6*,int /*<<< orphan*/ *) ; 

int
nd6_flush_holdchain(struct ifnet *ifp, struct mbuf *chain,
    struct sockaddr_in6 *dst)
{
	struct mbuf *m, *m_head;
	int error = 0;

	m_head = chain;

	while (m_head) {
		m = m_head;
		m_head = m_head->m_nextpkt;
		error = nd6_output_ifp(ifp, ifp, m, dst, NULL);
	}

	/*
	 * XXX
	 * note that intermediate errors are blindly ignored
	 */
	return (error);
}