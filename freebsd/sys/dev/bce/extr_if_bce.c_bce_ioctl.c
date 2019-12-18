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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u32 ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int ifr_reqcap; scalar_t__ ifr_mtu; } ;
struct ifnet {int if_drv_flags; int if_flags; int if_capenable; int if_capabilities; int /*<<< orphan*/  if_hwassist; scalar_t__ if_mtu; struct bce_softc* if_softc; } ;
struct bce_softc {int bce_flags; int bce_phy_flags; int /*<<< orphan*/  bce_miibus; int /*<<< orphan*/  bce_ifmedia; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_DRV_MSG_CODE_RESET ; 
 int /*<<< orphan*/  BCE_IF_HWASSIST ; 
 int /*<<< orphan*/  BCE_INFO_MISC ; 
 int /*<<< orphan*/  BCE_LOCK (struct bce_softc*) ; 
 scalar_t__ BCE_MAX_JUMBO_MTU ; 
 int BCE_MFW_ENABLE_FLAG ; 
 scalar_t__ BCE_MIN_MTU ; 
 int BCE_PHY_REMOTE_CAP_FLAG ; 
 int /*<<< orphan*/  BCE_UNLOCK (struct bce_softc*) ; 
 int /*<<< orphan*/  BCE_VERBOSE_MISC ; 
 int /*<<< orphan*/  BCE_VERBOSE_SPECIAL ; 
 int /*<<< orphan*/  CSUM_TSO ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBPRINT (struct bce_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int EINVAL ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
#define  SIOCADDMULTI 134 
#define  SIOCDELMULTI 133 
#define  SIOCGIFMEDIA 132 
#define  SIOCSIFCAP 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  VLAN_CAPABILITIES (struct ifnet*) ; 
 int /*<<< orphan*/  bce_chipinit (struct bce_softc*) ; 
 int /*<<< orphan*/  bce_init_locked (struct bce_softc*) ; 
 int /*<<< orphan*/  bce_mgmt_init_locked (struct bce_softc*) ; 
 int /*<<< orphan*/  bce_reset (struct bce_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bce_set_rx_mode (struct bce_softc*) ; 
 int /*<<< orphan*/  bce_stop (struct bce_softc*) ; 
 int /*<<< orphan*/  bce_tso_enable ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
bce_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct bce_softc *sc = ifp->if_softc;
	struct ifreq *ifr = (struct ifreq *) data;
	struct mii_data *mii;
	int mask, error = 0;

	DBENTER(BCE_VERBOSE_MISC);

	switch(command) {

	/* Set the interface MTU. */
	case SIOCSIFMTU:
		/* Check that the MTU setting is supported. */
		if ((ifr->ifr_mtu < BCE_MIN_MTU) ||
			(ifr->ifr_mtu > BCE_MAX_JUMBO_MTU)) {
			error = EINVAL;
			break;
		}

		DBPRINT(sc, BCE_INFO_MISC,
		    "SIOCSIFMTU: Changing MTU from %d to %d\n",
		    (int) ifp->if_mtu, (int) ifr->ifr_mtu);

		BCE_LOCK(sc);
		ifp->if_mtu = ifr->ifr_mtu;
		if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			bce_init_locked(sc);
		}
		BCE_UNLOCK(sc);
		break;

	/* Set interface flags. */
	case SIOCSIFFLAGS:
		DBPRINT(sc, BCE_VERBOSE_SPECIAL, "Received SIOCSIFFLAGS\n");

		BCE_LOCK(sc);

		/* Check if the interface is up. */
		if (ifp->if_flags & IFF_UP) {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				/* Change promiscuous/multicast flags as necessary. */
				bce_set_rx_mode(sc);
			} else {
				/* Start the HW */
				bce_init_locked(sc);
			}
		} else {
			/* The interface is down, check if driver is running. */
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				bce_stop(sc);

				/* If MFW is running, restart the controller a bit. */
				if (sc->bce_flags & BCE_MFW_ENABLE_FLAG) {
					bce_reset(sc, BCE_DRV_MSG_CODE_RESET);
					bce_chipinit(sc);
					bce_mgmt_init_locked(sc);
				}
			}
		}

		BCE_UNLOCK(sc);
		break;

	/* Add/Delete multicast address */
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		DBPRINT(sc, BCE_VERBOSE_MISC,
		    "Received SIOCADDMULTI/SIOCDELMULTI\n");

		BCE_LOCK(sc);
		if (ifp->if_drv_flags & IFF_DRV_RUNNING)
			bce_set_rx_mode(sc);
		BCE_UNLOCK(sc);

		break;

	/* Set/Get Interface media */
	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		DBPRINT(sc, BCE_VERBOSE_MISC,
		    "Received SIOCSIFMEDIA/SIOCGIFMEDIA\n");
		if ((sc->bce_phy_flags & BCE_PHY_REMOTE_CAP_FLAG) != 0)
			error = ifmedia_ioctl(ifp, ifr, &sc->bce_ifmedia,
			    command);
		else {
			mii = device_get_softc(sc->bce_miibus);
			error = ifmedia_ioctl(ifp, ifr, &mii->mii_media,
			    command);
		}
		break;

	/* Set interface capability */
	case SIOCSIFCAP:
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
		DBPRINT(sc, BCE_INFO_MISC,
		    "Received SIOCSIFCAP = 0x%08X\n", (u32) mask);

		/* Toggle the TX checksum capabilities enable flag. */
		if (mask & IFCAP_TXCSUM &&
		    ifp->if_capabilities & IFCAP_TXCSUM) {
			ifp->if_capenable ^= IFCAP_TXCSUM;
			if (IFCAP_TXCSUM & ifp->if_capenable)
				ifp->if_hwassist |= BCE_IF_HWASSIST;
			else
				ifp->if_hwassist &= ~BCE_IF_HWASSIST;
		}

		/* Toggle the RX checksum capabilities enable flag. */
		if (mask & IFCAP_RXCSUM &&
		    ifp->if_capabilities & IFCAP_RXCSUM)
			ifp->if_capenable ^= IFCAP_RXCSUM;

		/* Toggle the TSO capabilities enable flag. */
		if (bce_tso_enable && (mask & IFCAP_TSO4) &&
		    ifp->if_capabilities & IFCAP_TSO4) {
			ifp->if_capenable ^= IFCAP_TSO4;
			if (IFCAP_TSO4 & ifp->if_capenable)
				ifp->if_hwassist |= CSUM_TSO;
			else
				ifp->if_hwassist &= ~CSUM_TSO;
		}

		if (mask & IFCAP_VLAN_HWCSUM &&
		    ifp->if_capabilities & IFCAP_VLAN_HWCSUM)
			ifp->if_capenable ^= IFCAP_VLAN_HWCSUM;

		if ((mask & IFCAP_VLAN_HWTSO) != 0 &&
		    (ifp->if_capabilities & IFCAP_VLAN_HWTSO) != 0)
			ifp->if_capenable ^= IFCAP_VLAN_HWTSO;
		/*
		 * Don't actually disable VLAN tag stripping as
		 * management firmware (ASF/IPMI/UMP) requires the
		 * feature. If VLAN tag stripping is disabled driver
		 * will manually reconstruct the VLAN frame by
		 * appending stripped VLAN tag.
		 */
		if ((mask & IFCAP_VLAN_HWTAGGING) != 0 &&
		    (ifp->if_capabilities & IFCAP_VLAN_HWTAGGING)) {
			ifp->if_capenable ^= IFCAP_VLAN_HWTAGGING;
			if ((ifp->if_capenable & IFCAP_VLAN_HWTAGGING)
			    == 0)
				ifp->if_capenable &= ~IFCAP_VLAN_HWTSO;
		}
		VLAN_CAPABILITIES(ifp);
		break;
	default:
		/* We don't know how to handle the IOCTL, pass it on. */
		error = ether_ioctl(ifp, command, data);
		break;
	}

	DBEXIT(BCE_VERBOSE_MISC);
	return(error);
}