#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ifnet {int if_dunit; struct adapter* if_softc; } ;
struct if_clone {int dummy; } ;
struct adapter {int /*<<< orphan*/  media; int /*<<< orphan*/  ifp_lock; int /*<<< orphan*/ * ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifc_free_unit (struct if_clone*,int) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_trace_lock ; 

__attribute__((used)) static int
t4_cloner_destroy(struct if_clone *ifc, struct ifnet *ifp)
{
	struct adapter *sc;
	int unit = ifp->if_dunit;

	sx_xlock(&t4_trace_lock);
	sc = ifp->if_softc;
	if (sc != NULL) {
		mtx_lock(&sc->ifp_lock);
		sc->ifp = NULL;
		ifp->if_softc = NULL;
		mtx_unlock(&sc->ifp_lock);
		ifmedia_removeall(&sc->media);
	}
	ether_ifdetach(ifp);
	if_free(ifp);
	ifc_free_unit(ifc, unit);
	sx_xunlock(&t4_trace_lock);

	return (0);
}