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
struct TYPE_3__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_drv_flags; TYPE_2__* if_softc; } ;
typedef  TYPE_2__* priv_p ;
struct TYPE_4__ {int /*<<< orphan*/  hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ ,struct mbuf*) ; 
 struct mbuf* sppp_dequeue (struct ifnet*) ; 

__attribute__((used)) static void
ng_sppp_start (struct ifnet *ifp)
{
	struct mbuf *m;
	int len, error = 0;
	priv_p priv = ifp->if_softc;
	
	/* Check interface flags */
	/*
	 * This has side effects. It is not good idea to stop sending if we
	 * are not UP. If we are not running we still want to send LCP term
	 * packets.
	 */
/*	if (!((ifp->if_flags & IFF_UP) && */
/*	    (ifp->if_drv_flags & IFF_DRV_RUNNING))) { */
/*		return;*/
/*	}*/
	
	if (ifp->if_drv_flags & IFF_DRV_OACTIVE)
		return;
		
	if (!priv->hook)
		return;
		
	ifp->if_drv_flags |= IFF_DRV_OACTIVE;

	while ((m = sppp_dequeue (ifp)) != NULL) {
		BPF_MTAP (ifp, m);
		len = m->m_pkthdr.len;
		
		NG_SEND_DATA_ONLY (error, priv->hook, m);
		
		if (error) {
			ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
			return;
		}
	}
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
}