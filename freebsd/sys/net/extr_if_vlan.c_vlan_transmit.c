#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vlan_snd_tag {TYPE_2__* tag; } ;
struct TYPE_3__ {int len; int csum_flags; struct m_snd_tag* snd_tag; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;
struct m_snd_tag {struct ifnet* ifp; } ;
struct ifvlan {int /*<<< orphan*/  ifv_pcp; int /*<<< orphan*/  ifv_vid; } ;
struct ifnet {int (* if_transmit ) (struct ifnet*,struct mbuf*) ;struct ifvlan* if_softc; } ;
struct TYPE_4__ {struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int CSUM_SND_TAG ; 
 int EAGAIN ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  IFCOUNTER_OBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int M_BCAST ; 
 int M_MCAST ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 struct ifnet* PARENT (struct ifvlan*) ; 
 int /*<<< orphan*/ * TRUNK (struct ifvlan*) ; 
 int /*<<< orphan*/  UP_AND_RUNNING (struct ifnet*) ; 
 int /*<<< orphan*/  ether_8021q_frame (struct mbuf**,struct ifnet*,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct m_snd_tag* m_snd_tag_ref (TYPE_2__*) ; 
 int /*<<< orphan*/  m_snd_tag_rele (struct m_snd_tag*) ; 
 struct vlan_snd_tag* mst_to_vst (struct m_snd_tag*) ; 
 int stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static int
vlan_transmit(struct ifnet *ifp, struct mbuf *m)
{
	struct ifvlan *ifv;
	struct ifnet *p;
	int error, len, mcast;

	NET_EPOCH_ASSERT();

	ifv = ifp->if_softc;
	if (TRUNK(ifv) == NULL) {
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		m_freem(m);
		return (ENETDOWN);
	}
	p = PARENT(ifv);
	len = m->m_pkthdr.len;
	mcast = (m->m_flags & (M_MCAST | M_BCAST)) ? 1 : 0;

	BPF_MTAP(ifp, m);

#if defined(KERN_TLS) || defined(RATELIMIT)
	if (m->m_pkthdr.csum_flags & CSUM_SND_TAG) {
		struct vlan_snd_tag *vst;
		struct m_snd_tag *mst;

		MPASS(m->m_pkthdr.snd_tag->ifp == ifp);
		mst = m->m_pkthdr.snd_tag;
		vst = mst_to_vst(mst);
		if (vst->tag->ifp != p) {
			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
			m_freem(m);
			return (EAGAIN);
		}

		m->m_pkthdr.snd_tag = m_snd_tag_ref(vst->tag);
		m_snd_tag_rele(mst);
	}
#endif

	/*
	 * Do not run parent's if_transmit() if the parent is not up,
	 * or parent's driver will cause a system crash.
	 */
	if (!UP_AND_RUNNING(p)) {
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		m_freem(m);
		return (ENETDOWN);
	}

	if (!ether_8021q_frame(&m, ifp, p, ifv->ifv_vid, ifv->ifv_pcp)) {
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		return (0);
	}

	/*
	 * Send it, precisely as ether_output() would have.
	 */
	error = (p->if_transmit)(p, m);
	if (error == 0) {
		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
		if_inc_counter(ifp, IFCOUNTER_OBYTES, len);
		if_inc_counter(ifp, IFCOUNTER_OMCASTS, mcast);
	} else
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	return (error);
}