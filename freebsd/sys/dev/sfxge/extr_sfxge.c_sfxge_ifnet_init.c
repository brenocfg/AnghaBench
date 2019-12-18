#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sfxge_softc {struct ifnet* ifnet; int /*<<< orphan*/  dev; int /*<<< orphan*/  enp; } ;
struct ifnet {int if_flags; int if_hwassist; int /*<<< orphan*/  if_get_counter; int /*<<< orphan*/  if_qflush; int /*<<< orphan*/  if_transmit; int /*<<< orphan*/  if_capenable; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_hw_tsomaxsegsize; int /*<<< orphan*/  if_hw_tsomaxsegcount; int /*<<< orphan*/  if_hw_tsomax; int /*<<< orphan*/  if_ioctl; struct sfxge_softc* if_softc; int /*<<< orphan*/  if_init; } ;
struct TYPE_3__ {int /*<<< orphan*/  enc_mac_addr; scalar_t__ enc_hw_tx_insert_vlan_enabled; } ;
typedef  TYPE_1__ efx_nic_cfg_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSUM_IP ; 
 int CSUM_TCP ; 
 int CSUM_TCP_IPV6 ; 
 int CSUM_TSO ; 
 int CSUM_UDP ; 
 int CSUM_UDP_IPV6 ; 
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IFCAP_LRO ; 
 int /*<<< orphan*/  IFCAP_VLAN_HWTAGGING ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SFXGE_CAP ; 
 int /*<<< orphan*/  SFXGE_CAP_ENABLE ; 
 int /*<<< orphan*/  SFXGE_TSO_MAX_SIZE ; 
 int /*<<< orphan*/  SFXGE_TX_MAPPING_MAX_SEG ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 TYPE_1__* efx_nic_cfg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_get_counter ; 
 int /*<<< orphan*/  sfxge_if_init ; 
 int /*<<< orphan*/  sfxge_if_ioctl ; 
 int /*<<< orphan*/  sfxge_if_qflush ; 
 int /*<<< orphan*/  sfxge_if_transmit ; 
 int sfxge_port_ifmedia_init (struct sfxge_softc*) ; 

__attribute__((used)) static int
sfxge_ifnet_init(struct ifnet *ifp, struct sfxge_softc *sc)
{
	const efx_nic_cfg_t *encp = efx_nic_cfg_get(sc->enp);
	device_t dev;
	int rc;

	dev = sc->dev;
	sc->ifnet = ifp;

	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_init = sfxge_if_init;
	ifp->if_softc = sc;
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = sfxge_if_ioctl;

	ifp->if_capabilities = SFXGE_CAP;
	ifp->if_capenable = SFXGE_CAP_ENABLE;
	ifp->if_hw_tsomax = SFXGE_TSO_MAX_SIZE;
	ifp->if_hw_tsomaxsegcount = SFXGE_TX_MAPPING_MAX_SEG;
	ifp->if_hw_tsomaxsegsize = PAGE_SIZE;

#ifdef SFXGE_LRO
	ifp->if_capabilities |= IFCAP_LRO;
	ifp->if_capenable |= IFCAP_LRO;
#endif

	if (encp->enc_hw_tx_insert_vlan_enabled) {
		ifp->if_capabilities |= IFCAP_VLAN_HWTAGGING;
		ifp->if_capenable |= IFCAP_VLAN_HWTAGGING;
	}
	ifp->if_hwassist = CSUM_TCP | CSUM_UDP | CSUM_IP | CSUM_TSO |
			   CSUM_TCP_IPV6 | CSUM_UDP_IPV6;

	ether_ifattach(ifp, encp->enc_mac_addr);

	ifp->if_transmit = sfxge_if_transmit;
	ifp->if_qflush = sfxge_if_qflush;

	ifp->if_get_counter = sfxge_get_counter;

	DBGPRINT(sc->dev, "ifmedia_init");
	if ((rc = sfxge_port_ifmedia_init(sc)) != 0)
		goto fail;

	return (0);

fail:
	ether_ifdetach(sc->ifnet);
	return (rc);
}