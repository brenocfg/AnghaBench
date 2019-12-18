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
struct ifreq {int ifr_reqcap; } ;
struct fxp_softc {int if_flags; int flags; int /*<<< orphan*/  revision; int /*<<< orphan*/  sc_media; int /*<<< orphan*/ * miibus; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_1 (struct fxp_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSUM_TSO ; 
 int /*<<< orphan*/  FXP_CSR_SCB_INTRCNTL ; 
 int /*<<< orphan*/  FXP_CSUM_FEATURES ; 
 int FXP_FLAG_82559_RXCSUM ; 
 int FXP_FLAG_LONG_PKT_EN ; 
 int FXP_FLAG_SAVE_BAD ; 
 int /*<<< orphan*/  FXP_LOCK (struct fxp_softc*) ; 
 int /*<<< orphan*/  FXP_REV_82557 ; 
 int /*<<< orphan*/  FXP_SCB_INTR_DISABLE ; 
 int /*<<< orphan*/  FXP_UNLOCK (struct fxp_softc*) ; 
 int IFCAP_POLLING ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFCAP_VLAN_MTU ; 
 int IFCAP_WOL_MAGIC ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_LINK0 ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
#define  SIOCADDMULTI 133 
#define  SIOCDELMULTI 132 
#define  SIOCGIFMEDIA 131 
#define  SIOCSIFCAP 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 struct mii_data* device_get_softc (int /*<<< orphan*/ *) ; 
 int ether_ioctl (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int ether_poll_deregister (int /*<<< orphan*/ ) ; 
 int ether_poll_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fxp_init_body (struct fxp_softc*,int) ; 
 int /*<<< orphan*/  fxp_poll ; 
 int /*<<< orphan*/  fxp_stop (struct fxp_softc*) ; 
 int if_getcapabilities (int /*<<< orphan*/ ) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 
 struct fxp_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenablebit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_sethwassistbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_togglecapenable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_vlancap (int /*<<< orphan*/ ) ; 
 int ifmedia_ioctl (int /*<<< orphan*/ ,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
fxp_ioctl(if_t ifp, u_long command, caddr_t data)
{
	struct fxp_softc *sc = if_getsoftc(ifp);
	struct ifreq *ifr = (struct ifreq *)data;
	struct mii_data *mii;
	int flag, mask, error = 0, reinit;

	switch (command) {
	case SIOCSIFFLAGS:
		FXP_LOCK(sc);
		/*
		 * If interface is marked up and not running, then start it.
		 * If it is marked down and running, stop it.
		 * XXX If it's up then re-initialize it. This is so flags
		 * such as IFF_PROMISC are handled.
		 */
		if (if_getflags(ifp) & IFF_UP) {
			if (((if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0) &&
			    ((if_getflags(ifp) ^ sc->if_flags) &
			    (IFF_PROMISC | IFF_ALLMULTI | IFF_LINK0)) != 0) {
				if_setdrvflagbits(ifp, 0, IFF_DRV_RUNNING);
				fxp_init_body(sc, 0);
			} else if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) == 0)
				fxp_init_body(sc, 1);
		} else {
			if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0)
				fxp_stop(sc);
		}
		sc->if_flags = if_getflags(ifp);
		FXP_UNLOCK(sc);
		break;

	case SIOCADDMULTI:
	case SIOCDELMULTI:
		FXP_LOCK(sc);
		if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0) {
			if_setdrvflagbits(ifp, 0, IFF_DRV_RUNNING);
			fxp_init_body(sc, 0);
		}
		FXP_UNLOCK(sc);
		break;

	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		if (sc->miibus != NULL) {
			mii = device_get_softc(sc->miibus);
                        error = ifmedia_ioctl(ifp, ifr,
                            &mii->mii_media, command);
		} else {
                        error = ifmedia_ioctl(ifp, ifr, &sc->sc_media, command);
		}
		break;

	case SIOCSIFCAP:
		reinit = 0;
		mask = if_getcapenable(ifp) ^ ifr->ifr_reqcap;
#ifdef DEVICE_POLLING
		if (mask & IFCAP_POLLING) {
			if (ifr->ifr_reqcap & IFCAP_POLLING) {
				error = ether_poll_register(fxp_poll, ifp);
				if (error)
					return(error);
				FXP_LOCK(sc);
				CSR_WRITE_1(sc, FXP_CSR_SCB_INTRCNTL,
				    FXP_SCB_INTR_DISABLE);
				if_setcapenablebit(ifp, IFCAP_POLLING, 0);
				FXP_UNLOCK(sc);
			} else {
				error = ether_poll_deregister(ifp);
				/* Enable interrupts in any case */
				FXP_LOCK(sc);
				CSR_WRITE_1(sc, FXP_CSR_SCB_INTRCNTL, 0);
				if_setcapenablebit(ifp, 0, IFCAP_POLLING);
				FXP_UNLOCK(sc);
			}
		}
#endif
		FXP_LOCK(sc);
		if ((mask & IFCAP_TXCSUM) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_TXCSUM) != 0) {
			if_togglecapenable(ifp, IFCAP_TXCSUM);
			if ((if_getcapenable(ifp) & IFCAP_TXCSUM) != 0)
				if_sethwassistbits(ifp, FXP_CSUM_FEATURES, 0);
			else
				if_sethwassistbits(ifp, 0, FXP_CSUM_FEATURES);
		}
		if ((mask & IFCAP_RXCSUM) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_RXCSUM) != 0) {
			if_togglecapenable(ifp, IFCAP_RXCSUM);
			if ((sc->flags & FXP_FLAG_82559_RXCSUM) != 0)
				reinit++;
		}
		if ((mask & IFCAP_TSO4) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_TSO4) != 0) {
			if_togglecapenable(ifp, IFCAP_TSO4);
			if ((if_getcapenable(ifp) & IFCAP_TSO4) != 0)
				if_sethwassistbits(ifp, CSUM_TSO, 0);
			else
				if_sethwassistbits(ifp, 0, CSUM_TSO);
		}
		if ((mask & IFCAP_WOL_MAGIC) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_WOL_MAGIC) != 0)
			if_togglecapenable(ifp, IFCAP_WOL_MAGIC);
		if ((mask & IFCAP_VLAN_MTU) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_VLAN_MTU) != 0) {
			if_togglecapenable(ifp, IFCAP_VLAN_MTU);
			if (sc->revision != FXP_REV_82557)
				flag = FXP_FLAG_LONG_PKT_EN;
			else /* a hack to get long frames on the old chip */
				flag = FXP_FLAG_SAVE_BAD;
			sc->flags ^= flag;
			if (if_getflags(ifp) & IFF_UP)
				reinit++;
		}
		if ((mask & IFCAP_VLAN_HWCSUM) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_VLAN_HWCSUM) != 0)
			if_togglecapenable(ifp, IFCAP_VLAN_HWCSUM);
		if ((mask & IFCAP_VLAN_HWTSO) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_VLAN_HWTSO) != 0)
			if_togglecapenable(ifp, IFCAP_VLAN_HWTSO);
		if ((mask & IFCAP_VLAN_HWTAGGING) != 0 &&
		    (if_getcapabilities(ifp) & IFCAP_VLAN_HWTAGGING) != 0) {
			if_togglecapenable(ifp, IFCAP_VLAN_HWTAGGING);
			if ((if_getcapenable(ifp) & IFCAP_VLAN_HWTAGGING) == 0)
				if_setcapenablebit(ifp, 0, IFCAP_VLAN_HWTSO |
				    IFCAP_VLAN_HWCSUM);
			reinit++;
		}
		if (reinit > 0 &&
		    (if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0) {
			if_setdrvflagbits(ifp, 0, IFF_DRV_RUNNING);
			fxp_init_body(sc, 0);
		}
		FXP_UNLOCK(sc);
		if_vlancap(ifp);
		break;

	default:
		error = ether_ioctl(ifp, command, data);
	}
	return (error);
}