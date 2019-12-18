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
struct mii_data {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_dunit; struct arswitch_softc* if_softc; } ;
struct arswitch_softc {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 struct mii_data* arswitch_miiforport (struct arswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static int
arswitch_ifmedia_upd(struct ifnet *ifp)
{
	struct arswitch_softc *sc = ifp->if_softc;
	struct mii_data *mii = arswitch_miiforport(sc, ifp->if_dunit);

	if (mii == NULL)
		return (ENXIO);
	mii_mediachg(mii);
	return (0);
}