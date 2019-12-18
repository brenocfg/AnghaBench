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
struct ifnet {struct dme_softc* if_softc; } ;
struct dme_softc {int /*<<< orphan*/  dme_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DME_LOCK (struct dme_softc*) ; 
 int /*<<< orphan*/  DME_UNLOCK (struct dme_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static int
dme_ifmedia_upd(struct ifnet *ifp)
{
	struct dme_softc *sc;
	struct mii_data *mii;

	sc = ifp->if_softc;
	mii = device_get_softc(sc->dme_miibus);

	DME_LOCK(sc);
	mii_mediachg(mii);
	DME_UNLOCK(sc);

	return (0);
}