#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211com {int /*<<< orphan*/  ic_vaps; } ;
struct ndis_softc {scalar_t__ ndis_80211; int /*<<< orphan*/  ndis_rxlock; struct ifnet* ifp; struct ieee80211com ndis_ic; int /*<<< orphan*/  ndis_rxqueue; } ;
struct mbuf {int dummy; } ;
struct ifnet {int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct ieee80211vap {int /*<<< orphan*/  iv_bss; int /*<<< orphan*/  (* iv_deliver_data ) (struct ieee80211vap*,int /*<<< orphan*/ ,struct mbuf*) ;} ;
typedef  int /*<<< orphan*/  ndis_miniport_block ;
struct TYPE_3__ {int /*<<< orphan*/ * do_devext; } ;
typedef  TYPE_1__ device_object ;

/* Variables and functions */
 int /*<<< orphan*/  KeAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct mbuf* mbufq_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211vap*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  stub2 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static void
ndis_inputtask(device_object *dobj, void *arg)
{
	ndis_miniport_block	*block;
	struct ndis_softc	*sc = arg;
	struct mbuf		*m;
	uint8_t			irql;

	block = dobj->do_devext;

	KeAcquireSpinLock(&sc->ndis_rxlock, &irql);
	while ((m = mbufq_dequeue(&sc->ndis_rxqueue)) != NULL) {
		KeReleaseSpinLock(&sc->ndis_rxlock, irql);
		if ((sc->ndis_80211 != 0)) {
			struct ieee80211com *ic = &sc->ndis_ic;
			struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);

			if (vap != NULL)
				vap->iv_deliver_data(vap, vap->iv_bss, m);
		} else {
			struct ifnet *ifp = sc->ifp;

			(*ifp->if_input)(ifp, m);
		}
		KeAcquireSpinLock(&sc->ndis_rxlock, &irql);
	}
	KeReleaseSpinLock(&sc->ndis_rxlock, irql);
}