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
struct usb_ether {int /*<<< orphan*/  ue_rxq; struct ifnet* ue_ifp; } ;
struct mbuf {int /*<<< orphan*/ * m_nextpkt; } ;
struct ifnet {int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct epoch_tracker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 struct mbuf* STAILQ_NEXT (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UE_LOCK (struct usb_ether*) ; 
 int /*<<< orphan*/  UE_LOCK_ASSERT (struct usb_ether*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UE_UNLOCK (struct usb_ether*) ; 
 int /*<<< orphan*/  m_stailqpkt ; 
 struct mbuf* mbufq_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

void
uether_rxflush(struct usb_ether *ue)
{
	struct ifnet *ifp = ue->ue_ifp;
	struct epoch_tracker et;
	struct mbuf *m, *n;

	UE_LOCK_ASSERT(ue, MA_OWNED);

	n = mbufq_flush(&ue->ue_rxq);
	UE_UNLOCK(ue);
	NET_EPOCH_ENTER(et);
	while ((m = n) != NULL) {
		n = STAILQ_NEXT(m, m_stailqpkt);
		m->m_nextpkt = NULL;
		ifp->if_input(ifp, m);
	}
	NET_EPOCH_EXIT(et);
	UE_LOCK(ue);
}