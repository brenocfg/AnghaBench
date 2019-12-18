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
struct nfe_softc {int nfe_flags; int nfe_if_flags; int /*<<< orphan*/  nfe_miibus; int /*<<< orphan*/  nfe_jumbo_disable; } ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int ifr_reqcap; int /*<<< orphan*/  ifr_mtu; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
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
 int IFCAP_WOL_MAGIC ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NFE_CSUM_FEATURES ; 
 int /*<<< orphan*/  NFE_JUMBO_MTU ; 
 int NFE_JUMBO_SUP ; 
 int /*<<< orphan*/  NFE_LOCK (struct nfe_softc*) ; 
 int /*<<< orphan*/  NFE_UNLOCK (struct nfe_softc*) ; 
#define  SIOCADDMULTI 134 
#define  SIOCDELMULTI 133 
#define  SIOCGIFMEDIA 132 
#define  SIOCSIFCAP 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int ether_poll_deregister (int /*<<< orphan*/ ) ; 
 int ether_poll_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int if_getcapabilities (int /*<<< orphan*/ ) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_getmtu (int /*<<< orphan*/ ) ; 
 struct nfe_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenablebit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_sethwassistbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setmtu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_togglecapenable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_vlancap (int /*<<< orphan*/ ) ; 
 int ifmedia_ioctl (int /*<<< orphan*/ ,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfe_disable_intr (struct nfe_softc*) ; 
 int /*<<< orphan*/  nfe_enable_intr (struct nfe_softc*) ; 
 int /*<<< orphan*/  nfe_init (struct nfe_softc*) ; 
 int /*<<< orphan*/  nfe_init_locked (struct nfe_softc*) ; 
 int /*<<< orphan*/  nfe_poll ; 
 int /*<<< orphan*/  nfe_setmulti (struct nfe_softc*) ; 
 int /*<<< orphan*/  nfe_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfe_ioctl(if_t ifp, u_long cmd, caddr_t data)
{
	struct nfe_softc *sc;
	struct ifreq *ifr;
	struct mii_data *mii;
	int error, init, mask;

	sc = if_getsoftc(ifp);
	ifr = (struct ifreq *) data;
	error = 0;
	init = 0;
	switch (cmd) {
	case SIOCSIFMTU:
		if (ifr->ifr_mtu < ETHERMIN || ifr->ifr_mtu > NFE_JUMBO_MTU)
			error = EINVAL;
		else if (if_getmtu(ifp) != ifr->ifr_mtu) {
			if ((((sc->nfe_flags & NFE_JUMBO_SUP) == 0) ||
			    (sc->nfe_jumbo_disable != 0)) &&
			    ifr->ifr_mtu > ETHERMTU)
				error = EINVAL;
			else {
				NFE_LOCK(sc);
				if_setmtu(ifp, ifr->ifr_mtu);
				if (if_getdrvflags(ifp) & IFF_DRV_RUNNING) {
					if_setdrvflagbits(ifp, 0, IFF_DRV_RUNNING);
					nfe_init_locked(sc);
				}
				NFE_UNLOCK(sc);
			}
		}
		break;
	case SIOCSIFFLAGS:
		NFE_LOCK(sc);
		if (if_getflags(ifp) & IFF_UP) {
			/*
			 * If only the PROMISC or ALLMULTI flag changes, then
			 * don't do a full re-init of the chip, just update
			 * the Rx filter.
			 */
			if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) &&
			    ((if_getflags(ifp) ^ sc->nfe_if_flags) &
			     (IFF_ALLMULTI | IFF_PROMISC)) != 0)
				nfe_setmulti(sc);
			else
				nfe_init_locked(sc);
		} else {
			if (if_getdrvflags(ifp) & IFF_DRV_RUNNING)
				nfe_stop(ifp);
		}
		sc->nfe_if_flags = if_getflags(ifp);
		NFE_UNLOCK(sc);
		error = 0;
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0) {
			NFE_LOCK(sc);
			nfe_setmulti(sc);
			NFE_UNLOCK(sc);
			error = 0;
		}
		break;
	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		mii = device_get_softc(sc->nfe_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, cmd);
		break;
	case SIOCSIFCAP:
		mask = ifr->ifr_reqcap ^ if_getcapenable(ifp);
#ifdef DEVICE_POLLING
		if ((mask & IFCAP_POLLING) != 0) {
			if ((ifr->ifr_reqcap & IFCAP_POLLING) != 0) {
				error = ether_poll_register(nfe_poll, ifp);
				if (error)
					break;
				NFE_LOCK(sc);
				nfe_disable_intr(sc);
				if_setcapenablebit(ifp, IFCAP_POLLING, 0);
				NFE_UNLOCK(sc);
			} else {
				error = ether_poll_deregister(ifp);
				/* Enable interrupt even in error case */
				NFE_LOCK(sc);
				nfe_enable_intr(sc);
				if_setcapenablebit(ifp, 0, IFCAP_POLLING);
				NFE_UNLOCK(sc);
			}
		}
#endif /* DEVICE_POLLING */
		if ((mask & IFCAP_WOL_MAGIC) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_WOL_MAGIC) != 0)
			if_togglecapenable(ifp, IFCAP_WOL_MAGIC);
		if ((mask & IFCAP_TXCSUM) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_TXCSUM) != 0) {
			if_togglecapenable(ifp, IFCAP_TXCSUM);
			if ((if_getcapenable(ifp) & IFCAP_TXCSUM) != 0)
				if_sethwassistbits(ifp, NFE_CSUM_FEATURES, 0);
			else
				if_sethwassistbits(ifp, 0, NFE_CSUM_FEATURES);
		}
		if ((mask & IFCAP_RXCSUM) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_RXCSUM) != 0) {
			if_togglecapenable(ifp, IFCAP_RXCSUM);
			init++;
		}
		if ((mask & IFCAP_TSO4) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_TSO4) != 0) {
			if_togglecapenable(ifp, IFCAP_TSO4);
			if ((IFCAP_TSO4 & if_getcapenable(ifp)) != 0)
				if_sethwassistbits(ifp, CSUM_TSO, 0);
			else
				if_sethwassistbits(ifp, 0, CSUM_TSO);
		}
		if ((mask & IFCAP_VLAN_HWTSO) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_VLAN_HWTSO) != 0)
			if_togglecapenable(ifp, IFCAP_VLAN_HWTSO);
		if ((mask & IFCAP_VLAN_HWTAGGING) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_VLAN_HWTAGGING) != 0) {
			if_togglecapenable(ifp, IFCAP_VLAN_HWTAGGING);
			if ((if_getcapenable(ifp) & IFCAP_VLAN_HWTAGGING) == 0)
				if_setcapenablebit(ifp, 0, IFCAP_VLAN_HWTSO);
			init++;
		}
		/*
		 * XXX
		 * It seems that VLAN stripping requires Rx checksum offload.
		 * Unfortunately FreeBSD has no way to disable only Rx side
		 * VLAN stripping. So when we know Rx checksum offload is
		 * disabled turn entire hardware VLAN assist off.
		 */
		if ((if_getcapenable(ifp) & IFCAP_RXCSUM) == 0) {
			if ((if_getcapenable(ifp) & IFCAP_VLAN_HWTAGGING) != 0)
				init++;
			if_setcapenablebit(ifp, 0,
			    (IFCAP_VLAN_HWTAGGING | IFCAP_VLAN_HWTSO));
		}
		if (init > 0 && (if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0) {
			if_setdrvflagbits(ifp, 0, IFF_DRV_RUNNING);
			nfe_init(sc);
		}
		if_vlancap(ifp);
		break;
	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (error);
}