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
struct ifnet {struct dtsec_softc* if_softc; } ;
struct dtsec_softc {int /*<<< orphan*/  sc_mii; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_LOCK (struct dtsec_softc*) ; 
 int /*<<< orphan*/  DTSEC_UNLOCK (struct dtsec_softc*) ; 
 int /*<<< orphan*/  mii_mediachg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtsec_ifmedia_upd(struct ifnet *ifp)
{
	struct dtsec_softc *sc = ifp->if_softc;

	DTSEC_LOCK(sc);
	mii_mediachg(sc->sc_mii);
	DTSEC_UNLOCK(sc);

	return (0);
}