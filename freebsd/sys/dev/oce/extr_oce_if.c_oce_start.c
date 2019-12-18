#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; TYPE_4__* if_softc; } ;
struct TYPE_9__ {TYPE_3__** wq; TYPE_1__* ifp; int /*<<< orphan*/  link_status; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_stops; } ;
struct TYPE_8__ {TYPE_2__ tx_stats; int /*<<< orphan*/  tx_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  if_snd; } ;
typedef  TYPE_4__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int oce_tx (TYPE_4__*,struct mbuf**,int) ; 

void
oce_start(struct ifnet *ifp)
{
	POCE_SOFTC sc = ifp->if_softc;
	struct mbuf *m;
	int rc = 0;
	int def_q = 0; /* Defualt tx queue is 0*/

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
			IFF_DRV_RUNNING)
		return;

	if (!sc->link_status)
		return;
	
	do {
		IF_DEQUEUE(&sc->ifp->if_snd, m);
		if (m == NULL)
			break;

		LOCK(&sc->wq[def_q]->tx_lock);
		rc = oce_tx(sc, &m, def_q);
		UNLOCK(&sc->wq[def_q]->tx_lock);
		if (rc) {
			if (m != NULL) {
				sc->wq[def_q]->tx_stats.tx_stops ++;
				ifp->if_drv_flags |= IFF_DRV_OACTIVE;
				IFQ_DRV_PREPEND(&ifp->if_snd, m);
				m = NULL;
			}
			break;
		}
		if (m != NULL)
			ETHER_BPF_MTAP(ifp, m);

	} while (TRUE);

	return;
}