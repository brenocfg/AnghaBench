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
struct ifnet {int if_flags; } ;
struct cpswp_softc {struct ifnet* ifp; } ;
struct cpsw_softc {TYPE_1__* port; int /*<<< orphan*/  dualemac; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IFF_UP ; 
 struct cpswp_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpsw_ports_down(struct cpsw_softc *sc)
{
	struct cpswp_softc *psc;
	struct ifnet *ifp1, *ifp2;

	if (!sc->dualemac)
		return (1);
	psc = device_get_softc(sc->port[0].dev);
	ifp1 = psc->ifp;
	psc = device_get_softc(sc->port[1].dev);
	ifp2 = psc->ifp;
	if ((ifp1->if_flags & IFF_UP) == 0 && (ifp2->if_flags & IFF_UP) == 0)
		return (1);

	return (0);
}