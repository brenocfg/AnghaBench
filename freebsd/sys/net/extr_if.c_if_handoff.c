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
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;
struct ifqueue {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  (* if_start ) (struct ifnet*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_OMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_OQDROPS ; 
 int IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IF_LOCK (struct ifqueue*) ; 
 int /*<<< orphan*/  IF_UNLOCK (struct ifqueue*) ; 
 int M_BCAST ; 
 int M_MCAST ; 
 int /*<<< orphan*/  _IF_ENQUEUE (struct ifqueue*,struct mbuf*) ; 
 scalar_t__ _IF_QFULL (struct ifqueue*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*) ; 

int
if_handoff(struct ifqueue *ifq, struct mbuf *m, struct ifnet *ifp, int adjust)
{
	int active = 0;

	IF_LOCK(ifq);
	if (_IF_QFULL(ifq)) {
		IF_UNLOCK(ifq);
		if_inc_counter(ifp, IFCOUNTER_OQDROPS, 1);
		m_freem(m);
		return (0);
	}
	if (ifp != NULL) {
		if_inc_counter(ifp, IFCOUNTER_OBYTES, m->m_pkthdr.len + adjust);
		if (m->m_flags & (M_BCAST|M_MCAST))
			if_inc_counter(ifp, IFCOUNTER_OMCASTS, 1);
		active = ifp->if_drv_flags & IFF_DRV_OACTIVE;
	}
	_IF_ENQUEUE(ifq, m);
	IF_UNLOCK(ifq);
	if (ifp != NULL && !active)
		(*(ifp)->if_start)(ifp);
	return (1);
}