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
struct usb_ether {int /*<<< orphan*/  ue_rxq; struct ifnet* ue_ifp; } ;
struct TYPE_2__ {unsigned int len; struct ifnet* rcvif; } ;
struct mbuf {unsigned int m_len; TYPE_1__ m_pkthdr; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  UE_LOCK_ASSERT (struct usb_ether*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 

int
uether_rxmbuf(struct usb_ether *ue, struct mbuf *m, 
    unsigned int len)
{
	struct ifnet *ifp = ue->ue_ifp;

	UE_LOCK_ASSERT(ue, MA_OWNED);

	/* finalize mbuf */
	if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
	m->m_pkthdr.rcvif = ifp;
	m->m_pkthdr.len = m->m_len = len;

	/* enqueue for later when the lock can be released */
	(void)mbufq_enqueue(&ue->ue_rxq, m);
	return (0);
}