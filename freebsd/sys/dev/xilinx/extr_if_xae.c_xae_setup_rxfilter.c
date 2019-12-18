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
typedef  int uint32_t ;
struct xae_softc {int* macaddr; struct ifnet* ifp; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int FFC_PM ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int READ4 (struct xae_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct xae_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XAE_ASSERT_LOCKED (struct xae_softc*) ; 
 int /*<<< orphan*/  XAE_FFC ; 
 int /*<<< orphan*/  XAE_UAW0 ; 
 int /*<<< orphan*/  XAE_UAW1 ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,struct xae_softc*) ; 
 int /*<<< orphan*/  xae_write_maddr ; 

__attribute__((used)) static void
xae_setup_rxfilter(struct xae_softc *sc)
{
	struct ifnet *ifp;
	uint32_t reg;

	XAE_ASSERT_LOCKED(sc);

	ifp = sc->ifp;

	/*
	 * Set the multicast (group) filter hash.
	 */
	if ((ifp->if_flags & (IFF_ALLMULTI | IFF_PROMISC)) != 0) {
		reg = READ4(sc, XAE_FFC);
		reg |= FFC_PM;
		WRITE4(sc, XAE_FFC, reg);
	} else {
		reg = READ4(sc, XAE_FFC);
		reg &= ~FFC_PM;
		WRITE4(sc, XAE_FFC, reg);

		if_foreach_llmaddr(ifp, xae_write_maddr, sc);
	}

	/*
	 * Set the primary address.
	 */
	reg = sc->macaddr[0];
	reg |= (sc->macaddr[1] << 8);
	reg |= (sc->macaddr[2] << 16);
	reg |= (sc->macaddr[3] << 24);
	WRITE4(sc, XAE_UAW0, reg);

	reg = sc->macaddr[4];
	reg |= (sc->macaddr[5] << 8);
	WRITE4(sc, XAE_UAW1, reg);
}