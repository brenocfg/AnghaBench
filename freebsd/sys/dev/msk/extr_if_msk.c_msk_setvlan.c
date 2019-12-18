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
struct msk_softc {int dummy; } ;
struct msk_if_softc {int /*<<< orphan*/  msk_port; struct msk_softc* msk_softc; } ;
struct ifnet {int if_capenable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int /*<<< orphan*/  MR_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_GMF_CTRL_T ; 
 int /*<<< orphan*/  RX_VLAN_STRIP_OFF ; 
 int /*<<< orphan*/  RX_VLAN_STRIP_ON ; 
 int /*<<< orphan*/  TX_GMF_CTRL_T ; 
 int /*<<< orphan*/  TX_VLAN_TAG_OFF ; 
 int /*<<< orphan*/  TX_VLAN_TAG_ON ; 

__attribute__((used)) static void
msk_setvlan(struct msk_if_softc *sc_if, struct ifnet *ifp)
{
	struct msk_softc *sc;

	sc = sc_if->msk_softc;
	if ((ifp->if_capenable & IFCAP_VLAN_HWTAGGING) != 0) {
		CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, RX_GMF_CTRL_T),
		    RX_VLAN_STRIP_ON);
		CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, TX_GMF_CTRL_T),
		    TX_VLAN_TAG_ON);
	} else {
		CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, RX_GMF_CTRL_T),
		    RX_VLAN_STRIP_OFF);
		CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, TX_GMF_CTRL_T),
		    TX_VLAN_TAG_OFF);
	}
}