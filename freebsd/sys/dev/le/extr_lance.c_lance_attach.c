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
struct lance_softc {int /*<<< orphan*/  sc_enaddr; struct ifnet* sc_ifp; } ;
struct ifnet {int if_hdrlen; int /*<<< orphan*/  if_capenable; int /*<<< orphan*/  if_capabilities; } ;
struct ether_vlan_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCAP_VLAN_MTU ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 

void
lance_attach(struct lance_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;

	/* Attach the interface. */
	ether_ifattach(ifp, sc->sc_enaddr);

	/* Claim 802.1q capability. */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);
	ifp->if_capabilities |= IFCAP_VLAN_MTU;
	ifp->if_capenable |= IFCAP_VLAN_MTU;
}