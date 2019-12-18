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
struct stge_softc {struct ifnet* sc_ifp; } ;
struct ifnet {int if_capenable; } ;

/* Variables and functions */
 int CSR_READ_4 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct stge_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int MC_AutoVLANuntagging ; 
 int MC_MASK ; 
 int /*<<< orphan*/  STGE_MACCtrl ; 

__attribute__((used)) static void
stge_vlan_setup(struct stge_softc *sc)
{
	struct ifnet *ifp;
	uint32_t v;

	ifp = sc->sc_ifp;
	/*
	 * The NIC always copy a VLAN tag regardless of STGE_MACCtrl
	 * MC_AutoVLANuntagging bit.
	 * MC_AutoVLANtagging bit selects which VLAN source to use
	 * between STGE_VLANTag and TFC. However TFC TFD_VLANTagInsert
	 * bit has priority over MC_AutoVLANtagging bit. So we always
	 * use TFC instead of STGE_VLANTag register.
	 */
	v = CSR_READ_4(sc, STGE_MACCtrl) & MC_MASK;
	if ((ifp->if_capenable & IFCAP_VLAN_HWTAGGING) != 0)
		v |= MC_AutoVLANuntagging;
	else
		v &= ~MC_AutoVLANuntagging;
	CSR_WRITE_4(sc, STGE_MACCtrl, v);
}