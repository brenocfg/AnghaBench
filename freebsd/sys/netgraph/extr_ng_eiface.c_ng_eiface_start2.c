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
struct mbuf {int dummy; } ;
struct ifnet {int if_flags; int if_drv_flags; int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_softc; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_2__ {int /*<<< orphan*/  ether; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int IFF_MONITOR ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  NG_OUTBOUND_THREAD_REF () ; 
 int /*<<< orphan*/  NG_OUTBOUND_THREAD_UNREF () ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_tag_delete_chain (struct mbuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ng_eiface_start2(node_p node, hook_p hook, void *arg1, int arg2)
{
	struct ifnet *ifp = arg1;
	const priv_p priv = (priv_p)ifp->if_softc;
	int error = 0;
	struct mbuf *m;

	/* Check interface flags */

	if (!((ifp->if_flags & IFF_UP) &&
	    (ifp->if_drv_flags & IFF_DRV_RUNNING)))
		return;

	for (;;) {
		/*
		 * Grab a packet to transmit.
		 */
		IF_DEQUEUE(&ifp->if_snd, m);

		/* If there's nothing to send, break. */
		if (m == NULL)
			break;

		/* Peel the mbuf off any stale tags */
		m_tag_delete_chain(m, NULL);

		/*
		 * Berkeley packet filter.
		 * Pass packet to bpf if there is a listener.
		 * XXX is this safe? locking?
		 */
		BPF_MTAP(ifp, m);

		if (ifp->if_flags & IFF_MONITOR) {
			if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
			m_freem(m);
			continue;
		}

		/*
		 * Send packet; if hook is not connected, mbuf will get
		 * freed.
		 */
		NG_OUTBOUND_THREAD_REF();
		NG_SEND_DATA_ONLY(error, priv->ether, m);
		NG_OUTBOUND_THREAD_UNREF();

		/* Update stats */
		if (error == 0)
			if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
		else
			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	}

	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	return;
}