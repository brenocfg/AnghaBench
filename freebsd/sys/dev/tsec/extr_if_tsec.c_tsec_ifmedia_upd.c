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
struct tsec_softc {struct mii_data* tsec_mii; } ;
struct mii_data {int dummy; } ;
struct ifnet {struct tsec_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSEC_TRANSMIT_LOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_TRANSMIT_UNLOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static int
tsec_ifmedia_upd(struct ifnet *ifp)
{
	struct tsec_softc *sc = ifp->if_softc;
	struct mii_data *mii;

	TSEC_TRANSMIT_LOCK(sc);

	mii = sc->tsec_mii;
	mii_mediachg(mii);

	TSEC_TRANSMIT_UNLOCK(sc);
	return (0);
}