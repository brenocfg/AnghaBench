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
struct TYPE_3__ {int csum_flags; struct m_snd_tag* snd_tag; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct m_snd_tag {int dummy; } ;
struct lagg_snd_tag {TYPE_2__* tag; } ;
struct ifnet {int (* if_transmit ) (struct ifnet*,struct mbuf*) ;} ;
struct TYPE_4__ {struct ifnet* ifp; } ;

/* Variables and functions */
 int CSUM_SND_TAG ; 
 int EAGAIN ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct m_snd_tag* m_snd_tag_ref (TYPE_2__*) ; 
 int /*<<< orphan*/  m_snd_tag_rele (struct m_snd_tag*) ; 
 struct lagg_snd_tag* mst_to_lst (struct m_snd_tag*) ; 
 int stub1 (struct ifnet*,struct mbuf*) ; 

int
lagg_enqueue(struct ifnet *ifp, struct mbuf *m)
{

#if defined(KERN_TLS) || defined(RATELIMIT)
	if (m->m_pkthdr.csum_flags & CSUM_SND_TAG) {
		struct lagg_snd_tag *lst;
		struct m_snd_tag *mst;

		mst = m->m_pkthdr.snd_tag;
		lst = mst_to_lst(mst);
		if (lst->tag->ifp != ifp) {
			m_freem(m);
			return (EAGAIN);
		}
		m->m_pkthdr.snd_tag = m_snd_tag_ref(lst->tag);
		m_snd_tag_rele(mst);
	}
#endif
	return (ifp->if_transmit)(ifp, m);
}