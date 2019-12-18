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
struct rtwn_softc {struct r12a_softc* sc_priv; } ;
struct r12a_softc {int rs_flags; } ;
struct ifnet {int if_capabilities; int if_capenable; } ;
struct ieee80211vap {struct ifnet* iv_ifp; } ;

/* Variables and functions */
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int R12A_RXCKSUM6_EN ; 
 int R12A_RXCKSUM_EN ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 

void
r12a_vap_preattach(struct rtwn_softc *sc, struct ieee80211vap *vap)
{
	struct r12a_softc *rs = sc->sc_priv;
	struct ifnet *ifp = vap->iv_ifp;

	ifp->if_capabilities = IFCAP_RXCSUM | IFCAP_RXCSUM_IPV6;
	RTWN_LOCK(sc);
	if (rs->rs_flags & R12A_RXCKSUM_EN)
		ifp->if_capenable |= IFCAP_RXCSUM;
	if (rs->rs_flags & R12A_RXCKSUM6_EN)
		ifp->if_capenable |= IFCAP_RXCSUM_IPV6;
	RTWN_UNLOCK(sc);
}