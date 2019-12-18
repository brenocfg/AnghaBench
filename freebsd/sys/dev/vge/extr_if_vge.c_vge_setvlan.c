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
typedef  int /*<<< orphan*/  uint8_t ;
struct vge_softc {struct ifnet* vge_ifp; } ;
struct ifnet {int if_capenable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_1 (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int /*<<< orphan*/  VGE_LOCK_ASSERT (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_RXCFG ; 
 int /*<<< orphan*/  VGE_VTAG_OPT2 ; 

__attribute__((used)) static void
vge_setvlan(struct vge_softc *sc)
{
	struct ifnet *ifp;
	uint8_t cfg;

	VGE_LOCK_ASSERT(sc);

	ifp = sc->vge_ifp;
	cfg = CSR_READ_1(sc, VGE_RXCFG);
	if ((ifp->if_capenable & IFCAP_VLAN_HWTAGGING) != 0)
		cfg |= VGE_VTAG_OPT2;
	else
		cfg &= ~VGE_VTAG_OPT2;
	CSR_WRITE_1(sc, VGE_RXCFG, cfg);
}