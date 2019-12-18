#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct ifnet* rcvif; } ;
struct mbuf {scalar_t__ m_len; TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_flags; int if_drv_flags; int /*<<< orphan*/  (* if_input ) (struct ifnet* const,struct mbuf*) ;} ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_5__ {struct ifnet* ifp; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETDOWN ; 
 scalar_t__ ETHER_HDR_LEN ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet* const,int /*<<< orphan*/ ,int) ; 
 struct mbuf* m_pullup (struct mbuf*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ifnet* const,struct mbuf*) ; 

__attribute__((used)) static int
ng_eiface_rcvdata(hook_p hook, item_p item)
{
	const priv_p priv = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	struct ifnet *const ifp = priv->ifp;
	struct mbuf *m;

	NGI_GET_M(item, m);
	NG_FREE_ITEM(item);

	if (!((ifp->if_flags & IFF_UP) &&
	    (ifp->if_drv_flags & IFF_DRV_RUNNING))) {
		NG_FREE_M(m);
		return (ENETDOWN);
	}

	if (m->m_len < ETHER_HDR_LEN) {
		m = m_pullup(m, ETHER_HDR_LEN);
		if (m == NULL)
			return (EINVAL);
	}

	/* Note receiving interface */
	m->m_pkthdr.rcvif = ifp;

	/* Update interface stats */
	if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);

	(*ifp->if_input)(ifp, m);

	/* Done */
	return (0);
}