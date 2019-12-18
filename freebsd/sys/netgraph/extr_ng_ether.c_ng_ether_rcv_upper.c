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
struct TYPE_4__ {int len; struct ifnet* rcvif; } ;
struct mbuf {int m_len; TYPE_1__ m_pkthdr; } ;
struct ifnet {scalar_t__ if_bridge; } ;
struct ether_header {int dummy; } ;
struct epoch_tracker {int dummy; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_5__ {struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_INPUT (struct ifnet*,struct mbuf*) ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ether_demux (struct ifnet*,struct mbuf*) ; 
 struct mbuf* m_pullup (struct mbuf*,int) ; 

__attribute__((used)) static int
ng_ether_rcv_upper(hook_p hook, item_p item)
{
	struct epoch_tracker et;
	struct mbuf *m;
	const node_p node = NG_HOOK_NODE(hook);
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ifnet *ifp = priv->ifp;

	NGI_GET_M(item, m);
	NG_FREE_ITEM(item);

	/* Check length and pull off header */
	if (m->m_pkthdr.len < sizeof(struct ether_header)) {
		NG_FREE_M(m);
		return (EINVAL);
	}
	if (m->m_len < sizeof(struct ether_header) &&
	    (m = m_pullup(m, sizeof(struct ether_header))) == NULL)
		return (ENOBUFS);

	m->m_pkthdr.rcvif = ifp;

	/* Pass the packet to the bridge, it may come back to us */
	if (ifp->if_bridge) {
		BRIDGE_INPUT(ifp, m);
		if (m == NULL)
			return (0);
	}

	/* Route packet back in */
	NET_EPOCH_ENTER(et);
	ether_demux(ifp, m);
	NET_EPOCH_EXIT(et);
	return (0);
}