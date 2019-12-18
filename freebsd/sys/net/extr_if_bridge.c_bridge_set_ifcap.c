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
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_capenable; int (* if_ioctl ) (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  if_xname; } ;
struct bridge_softc {int /*<<< orphan*/  sc_ifp; } ;
struct bridge_iflist {struct ifnet* bif_ifp; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int BRIDGE_IFCAPS_MASK ; 
 int BRIDGE_IFCAPS_STRIP ; 
 int /*<<< orphan*/  BRIDGE_UNLOCK_ASSERT (struct bridge_softc*) ; 
 int /*<<< orphan*/  SIOCSIFCAP ; 
 int /*<<< orphan*/  bzero (struct ifreq*,int) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bridge_set_ifcap(struct bridge_softc *sc, struct bridge_iflist *bif, int set)
{
	struct ifnet *ifp = bif->bif_ifp;
	struct ifreq ifr;
	int error, mask, stuck;

	BRIDGE_UNLOCK_ASSERT(sc);

	bzero(&ifr, sizeof(ifr));
	ifr.ifr_reqcap = set;

	if (ifp->if_capenable != set) {
		error = (*ifp->if_ioctl)(ifp, SIOCSIFCAP, (caddr_t)&ifr);
		if (error)
			if_printf(sc->sc_ifp,
			    "error setting capabilities on %s: %d\n",
			    ifp->if_xname, error);
		mask = BRIDGE_IFCAPS_MASK | BRIDGE_IFCAPS_STRIP;
		stuck = ifp->if_capenable & mask & ~set;
		if (stuck != 0)
			if_printf(sc->sc_ifp,
			    "can't disable some capabilities on %s: 0x%x\n",
			    ifp->if_xname, stuck);
	}
}