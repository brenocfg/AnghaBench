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
struct mbuf {struct mbuf* m_nextpkt; } ;
struct ifaltq {scalar_t__ ifq_len; scalar_t__ ifq_tail; struct mbuf* ifq_head; } ;
struct ifnet {struct ifaltq if_snd; } ;

/* Variables and functions */
 scalar_t__ ALTQ_IS_ENABLED (struct ifaltq*) ; 
 int /*<<< orphan*/  ALTQ_PURGE (struct ifaltq*) ; 
 int /*<<< orphan*/  IFQ_LOCK (struct ifaltq*) ; 
 int /*<<< orphan*/  IFQ_UNLOCK (struct ifaltq*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

void
if_qflush(struct ifnet *ifp)
{
	struct mbuf *m, *n;
	struct ifaltq *ifq;
	
	ifq = &ifp->if_snd;
	IFQ_LOCK(ifq);
#ifdef ALTQ
	if (ALTQ_IS_ENABLED(ifq))
		ALTQ_PURGE(ifq);
#endif
	n = ifq->ifq_head;
	while ((m = n) != NULL) {
		n = m->m_nextpkt;
		m_freem(m);
	}
	ifq->ifq_head = 0;
	ifq->ifq_tail = 0;
	ifq->ifq_len = 0;
	IFQ_UNLOCK(ifq);
}