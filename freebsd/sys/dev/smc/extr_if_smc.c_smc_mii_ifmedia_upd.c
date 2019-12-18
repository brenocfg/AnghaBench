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
struct smc_softc {int /*<<< orphan*/ * smc_miibus; } ;
struct mii_data {int dummy; } ;
struct ifnet {struct smc_softc* if_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ *) ; 
 int mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static int
smc_mii_ifmedia_upd(struct ifnet *ifp)
{
	struct smc_softc	*sc;
	struct mii_data		*mii;

	sc = ifp->if_softc;
	if (sc->smc_miibus == NULL)
		return (ENXIO);

	mii = device_get_softc(sc->smc_miibus);
	return (mii_mediachg(mii));
}