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
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int ifr_reqcap; int /*<<< orphan*/  ifr_mtu; } ;
struct bge_softc {int bge_flags; int bge_if_flags; int /*<<< orphan*/  bge_csum_features; int /*<<< orphan*/  bge_miibus; int /*<<< orphan*/  bge_ifmedia; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_CLRBIT (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BGE_FLAG_JUMBO_STD ; 
 int BGE_FLAG_TBI ; 
 int /*<<< orphan*/  BGE_IS_JUMBO_CAPABLE (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_JUMBO_MTU ; 
 int /*<<< orphan*/  BGE_LOCK (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_MBX_IRQ0_LO ; 
 int /*<<< orphan*/  BGE_PCIMISCCTL_MASK_PCI_INTR ; 
 int /*<<< orphan*/  BGE_PCI_MISC_CTL ; 
 int /*<<< orphan*/  BGE_SETBIT (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGE_UNLOCK (struct bge_softc*) ; 
 int /*<<< orphan*/  CSUM_TSO ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETHERMIN ; 
 int /*<<< orphan*/  ETHERMTU ; 
 int IFCAP_POLLING ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
#define  SIOCADDMULTI 134 
#define  SIOCDELMULTI 133 
#define  SIOCGIFMEDIA 132 
#define  SIOCSIFCAP 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  bge_init (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_init_locked (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_poll ; 
 int /*<<< orphan*/  bge_setmulti (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_setpromisc (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_setvlan (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_stop (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_writembx (struct bge_softc*,int /*<<< orphan*/ ,int) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int ether_poll_deregister (int /*<<< orphan*/ ) ; 
 int ether_poll_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int if_getcapabilities (int /*<<< orphan*/ ) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_getmtu (int /*<<< orphan*/ ) ; 
 struct bge_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenablebit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_sethwassistbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setmtu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_togglecapenable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_vlancap (int /*<<< orphan*/ ) ; 
 int ifmedia_ioctl (int /*<<< orphan*/ ,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
bge_ioctl(if_t ifp, u_long command, caddr_t data)
{
	struct bge_softc *sc = if_getsoftc(ifp);
	struct ifreq *ifr = (struct ifreq *) data;
	struct mii_data *mii;
	int flags, mask, error = 0;

	switch (command) {
	case SIOCSIFMTU:
		if (BGE_IS_JUMBO_CAPABLE(sc) ||
		    (sc->bge_flags & BGE_FLAG_JUMBO_STD)) {
			if (ifr->ifr_mtu < ETHERMIN ||
			    ifr->ifr_mtu > BGE_JUMBO_MTU) {
				error = EINVAL;
				break;
			}
		} else if (ifr->ifr_mtu < ETHERMIN || ifr->ifr_mtu > ETHERMTU) {
			error = EINVAL;
			break;
		}
		BGE_LOCK(sc);
		if (if_getmtu(ifp) != ifr->ifr_mtu) {
			if_setmtu(ifp, ifr->ifr_mtu);
			if (if_getdrvflags(ifp) & IFF_DRV_RUNNING) {
				if_setdrvflagbits(ifp, 0, IFF_DRV_RUNNING);
				bge_init_locked(sc);
			}
		}
		BGE_UNLOCK(sc);
		break;
	case SIOCSIFFLAGS:
		BGE_LOCK(sc);
		if (if_getflags(ifp) & IFF_UP) {
			/*
			 * If only the state of the PROMISC flag changed,
			 * then just use the 'set promisc mode' command
			 * instead of reinitializing the entire NIC. Doing
			 * a full re-init means reloading the firmware and
			 * waiting for it to start up, which may take a
			 * second or two.  Similarly for ALLMULTI.
			 */
			if (if_getdrvflags(ifp) & IFF_DRV_RUNNING) {
				flags = if_getflags(ifp) ^ sc->bge_if_flags;
				if (flags & IFF_PROMISC)
					bge_setpromisc(sc);
				if (flags & IFF_ALLMULTI)
					bge_setmulti(sc);
			} else
				bge_init_locked(sc);
		} else {
			if (if_getdrvflags(ifp) & IFF_DRV_RUNNING) {
				bge_stop(sc);
			}
		}
		sc->bge_if_flags = if_getflags(ifp);
		BGE_UNLOCK(sc);
		error = 0;
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		if (if_getdrvflags(ifp) & IFF_DRV_RUNNING) {
			BGE_LOCK(sc);
			bge_setmulti(sc);
			BGE_UNLOCK(sc);
			error = 0;
		}
		break;
	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		if (sc->bge_flags & BGE_FLAG_TBI) {
			error = ifmedia_ioctl(ifp, ifr,
			    &sc->bge_ifmedia, command);
		} else {
			mii = device_get_softc(sc->bge_miibus);
			error = ifmedia_ioctl(ifp, ifr,
			    &mii->mii_media, command);
		}
		break;
	case SIOCSIFCAP:
		mask = ifr->ifr_reqcap ^ if_getcapenable(ifp);
#ifdef DEVICE_POLLING
		if (mask & IFCAP_POLLING) {
			if (ifr->ifr_reqcap & IFCAP_POLLING) {
				error = ether_poll_register(bge_poll, ifp);
				if (error)
					return (error);
				BGE_LOCK(sc);
				BGE_SETBIT(sc, BGE_PCI_MISC_CTL,
				    BGE_PCIMISCCTL_MASK_PCI_INTR);
				bge_writembx(sc, BGE_MBX_IRQ0_LO, 1);
				if_setcapenablebit(ifp, IFCAP_POLLING, 0);
				BGE_UNLOCK(sc);
			} else {
				error = ether_poll_deregister(ifp);
				/* Enable interrupt even in error case */
				BGE_LOCK(sc);
				BGE_CLRBIT(sc, BGE_PCI_MISC_CTL,
				    BGE_PCIMISCCTL_MASK_PCI_INTR);
				bge_writembx(sc, BGE_MBX_IRQ0_LO, 0);
				if_setcapenablebit(ifp, 0, IFCAP_POLLING);
				BGE_UNLOCK(sc);
			}
		}
#endif
		if ((mask & IFCAP_TXCSUM) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_TXCSUM) != 0) {
			if_togglecapenable(ifp, IFCAP_TXCSUM);
			if ((if_getcapenable(ifp) & IFCAP_TXCSUM) != 0)
				if_sethwassistbits(ifp,
				    sc->bge_csum_features, 0);
			else
				if_sethwassistbits(ifp, 0,
				    sc->bge_csum_features);
		}

		if ((mask & IFCAP_RXCSUM) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_RXCSUM) != 0)
			if_togglecapenable(ifp, IFCAP_RXCSUM);

		if ((mask & IFCAP_TSO4) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_TSO4) != 0) {
			if_togglecapenable(ifp, IFCAP_TSO4);
			if ((if_getcapenable(ifp) & IFCAP_TSO4) != 0)
				if_sethwassistbits(ifp, CSUM_TSO, 0);
			else
				if_sethwassistbits(ifp, 0, CSUM_TSO);
		}

		if (mask & IFCAP_VLAN_MTU) {
			if_togglecapenable(ifp, IFCAP_VLAN_MTU);
			if_setdrvflagbits(ifp, 0, IFF_DRV_RUNNING);
			bge_init(sc);
		}

		if ((mask & IFCAP_VLAN_HWTSO) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_VLAN_HWTSO) != 0)
			if_togglecapenable(ifp, IFCAP_VLAN_HWTSO);
		if ((mask & IFCAP_VLAN_HWTAGGING) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_VLAN_HWTAGGING) != 0) {
			if_togglecapenable(ifp, IFCAP_VLAN_HWTAGGING);
			if ((if_getcapenable(ifp) & IFCAP_VLAN_HWTAGGING) == 0)
				if_setcapenablebit(ifp, 0, IFCAP_VLAN_HWTSO);
			BGE_LOCK(sc);
			bge_setvlan(sc);
			BGE_UNLOCK(sc);
		}
#ifdef VLAN_CAPABILITIES
		if_vlancap(ifp);
#endif
		break;
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}