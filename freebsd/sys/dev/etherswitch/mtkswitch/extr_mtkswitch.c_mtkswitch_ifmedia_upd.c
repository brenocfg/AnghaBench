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
struct mtkswitch_softc {int dummy; } ;
struct mii_data {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_dunit; struct mtkswitch_softc* if_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 struct mii_data* mtkswitch_miiforport (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtkswitch_ifmedia_upd(struct ifnet *ifp)
{
	struct mtkswitch_softc *sc = ifp->if_softc;
	struct mii_data *mii = mtkswitch_miiforport(sc, ifp->if_dunit);
        
	if (mii == NULL)
		return (ENXIO);
	mii_mediachg(mii);
	return (0);
}