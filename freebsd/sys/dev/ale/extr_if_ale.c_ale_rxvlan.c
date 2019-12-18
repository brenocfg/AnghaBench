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
typedef  int /*<<< orphan*/  uint32_t ;
struct ifnet {int if_capenable; } ;
struct ale_softc {struct ifnet* ale_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_LOCK_ASSERT (struct ale_softc*) ; 
 int /*<<< orphan*/  ALE_MAC_CFG ; 
 int /*<<< orphan*/  CSR_READ_4 (struct ale_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ale_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int /*<<< orphan*/  MAC_CFG_VLAN_TAG_STRIP ; 

__attribute__((used)) static void
ale_rxvlan(struct ale_softc *sc)
{
	struct ifnet *ifp;
	uint32_t reg;

	ALE_LOCK_ASSERT(sc);

	ifp = sc->ale_ifp;
	reg = CSR_READ_4(sc, ALE_MAC_CFG);
	reg &= ~MAC_CFG_VLAN_TAG_STRIP;
	if ((ifp->if_capenable & IFCAP_VLAN_HWTAGGING) != 0)
		reg |= MAC_CFG_VLAN_TAG_STRIP;
	CSR_WRITE_4(sc, ALE_MAC_CFG, reg);
}