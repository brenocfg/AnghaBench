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
typedef  int /*<<< orphan*/  uint16_t ;
struct sge_softc {struct ifnet* sge_ifp; } ;
struct ifnet {int if_capabilities; int if_capenable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_2 (struct sge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct sge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int /*<<< orphan*/  RXMAC_STRIP_VLAN ; 
 int /*<<< orphan*/  RxMacControl ; 
 int /*<<< orphan*/  SGE_LOCK_ASSERT (struct sge_softc*) ; 

__attribute__((used)) static void
sge_setvlan(struct sge_softc *sc)
{
	struct ifnet *ifp;
	uint16_t rxfilt;

	SGE_LOCK_ASSERT(sc);

	ifp = sc->sge_ifp;
	if ((ifp->if_capabilities & IFCAP_VLAN_HWTAGGING) == 0)
		return;
	rxfilt = CSR_READ_2(sc, RxMacControl);
	if ((ifp->if_capenable & IFCAP_VLAN_HWTAGGING) != 0)
		rxfilt |= RXMAC_STRIP_VLAN;
	else
		rxfilt &= ~RXMAC_STRIP_VLAN;
	CSR_WRITE_2(sc, RxMacControl, rxfilt);
}