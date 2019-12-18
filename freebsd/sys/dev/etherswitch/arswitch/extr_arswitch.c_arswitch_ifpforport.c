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
struct ifnet {int dummy; } ;
struct arswitch_softc {int numphys; struct ifnet** ifp; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ifnet *
arswitch_ifpforport(struct arswitch_softc *sc, int port)
{
	int phy = port-1;

	if (phy < 0 || phy >= sc->numphys)
		return (NULL);
	return (sc->ifp[phy]);
}