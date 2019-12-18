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
struct mtkswitch_softc {struct ifnet** ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int MTKSWITCH_MAX_PHYS ; 
 int mtkswitch_phyforport (int) ; 

__attribute__((used)) static inline struct ifnet *
mtkswitch_ifpforport(struct mtkswitch_softc *sc, int port)
{
	int phy = mtkswitch_phyforport(port);

	if (phy < 0 || phy >= MTKSWITCH_MAX_PHYS)
		return (NULL);

	return (sc->ifp[phy]);
}