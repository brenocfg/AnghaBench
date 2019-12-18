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
struct rm_priotracker {int dummy; } ;
struct ifnet {struct hn_softc* if_softc; } ;
struct hn_softc {int hn_tx_ring_inuse; int hn_xvf_flags; int /*<<< orphan*/  hn_vf_lock; TYPE_1__* hn_vf_ifp; int /*<<< orphan*/ * hn_tx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* if_qflush ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int HN_XVFFLAG_ENABLED ; 
 int /*<<< orphan*/  hn_tx_ring_qflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_qflush (struct ifnet*) ; 
 int /*<<< orphan*/  rm_rlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_runlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void
hn_xmit_qflush(struct ifnet *ifp)
{
	struct hn_softc *sc = ifp->if_softc;
	struct rm_priotracker pt;
	int i;

	for (i = 0; i < sc->hn_tx_ring_inuse; ++i)
		hn_tx_ring_qflush(&sc->hn_tx_ring[i]);
	if_qflush(ifp);

	rm_rlock(&sc->hn_vf_lock, &pt);
	if (sc->hn_xvf_flags & HN_XVFFLAG_ENABLED)
		sc->hn_vf_ifp->if_qflush(sc->hn_vf_ifp);
	rm_runlock(&sc->hn_vf_lock, &pt);
}