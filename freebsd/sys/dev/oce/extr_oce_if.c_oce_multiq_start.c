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
struct oce_wq {int /*<<< orphan*/  tx_lock; } ;
struct TYPE_3__ {int flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {TYPE_2__* if_softc; } ;
struct TYPE_4__ {int nwqs; struct oce_wq** wq; int /*<<< orphan*/  link_status; } ;
typedef  TYPE_2__* POCE_SOFTC ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 scalar_t__ M_HASHTYPE_NONE ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int oce_multiq_transmit (struct ifnet*,struct mbuf*,struct oce_wq*) ; 

__attribute__((used)) static int
oce_multiq_start(struct ifnet *ifp, struct mbuf *m)
{
	POCE_SOFTC sc = ifp->if_softc;
	struct oce_wq *wq = NULL;
	int queue_index = 0;
	int status = 0;

	if (!sc->link_status)
		return ENXIO;

	if (M_HASHTYPE_GET(m) != M_HASHTYPE_NONE)
		queue_index = m->m_pkthdr.flowid % sc->nwqs;

	wq = sc->wq[queue_index];

	LOCK(&wq->tx_lock);
	status = oce_multiq_transmit(ifp, m, wq);
	UNLOCK(&wq->tx_lock);

	return status;

}