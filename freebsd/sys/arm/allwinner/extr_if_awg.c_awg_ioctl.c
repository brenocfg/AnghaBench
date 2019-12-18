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
struct awg_softc {int if_flags; int /*<<< orphan*/  miibus; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWG_LOCK (struct awg_softc*) ; 
 int /*<<< orphan*/  AWG_UNLOCK (struct awg_softc*) ; 
 int CSUM_IP ; 
 int CSUM_TCP ; 
 int CSUM_UDP ; 
 int IFCAP_POLLING ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
#define  SIOCADDMULTI 133 
#define  SIOCDELMULTI 132 
#define  SIOCGIFMEDIA 131 
#define  SIOCSIFCAP 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 int /*<<< orphan*/  awg_disable_intr (struct awg_softc*) ; 
 int /*<<< orphan*/  awg_enable_intr (struct awg_softc*) ; 
 int /*<<< orphan*/  awg_init_locked (struct awg_softc*) ; 
 int /*<<< orphan*/  awg_poll ; 
 int /*<<< orphan*/  awg_setup_rxfilter (struct awg_softc*) ; 
 int /*<<< orphan*/  awg_stop (struct awg_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int ether_poll_deregister (int /*<<< orphan*/ ) ; 
 int ether_poll_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 
 struct awg_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenablebit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  if_sethwassistbits (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  if_togglecapenable (int /*<<< orphan*/ ,int) ; 
 int ifmedia_ioctl (int /*<<< orphan*/ ,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
awg_ioctl(if_t ifp, u_long cmd, caddr_t data)
{
	struct awg_softc *sc;
	struct mii_data *mii;
	struct ifreq *ifr;
	int flags, mask, error;

	sc = if_getsoftc(ifp);
	mii = device_get_softc(sc->miibus);
	ifr = (struct ifreq *)data;
	error = 0;

	switch (cmd) {
	case SIOCSIFFLAGS:
		AWG_LOCK(sc);
		if (if_getflags(ifp) & IFF_UP) {
			if (if_getdrvflags(ifp) & IFF_DRV_RUNNING) {
				flags = if_getflags(ifp) ^ sc->if_flags;
				if ((flags & (IFF_PROMISC|IFF_ALLMULTI)) != 0)
					awg_setup_rxfilter(sc);
			} else
				awg_init_locked(sc);
		} else {
			if (if_getdrvflags(ifp) & IFF_DRV_RUNNING)
				awg_stop(sc);
		}
		sc->if_flags = if_getflags(ifp);
		AWG_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		if (if_getdrvflags(ifp) & IFF_DRV_RUNNING) {
			AWG_LOCK(sc);
			awg_setup_rxfilter(sc);
			AWG_UNLOCK(sc);
		}
		break;
	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, cmd);
		break;
	case SIOCSIFCAP:
		mask = ifr->ifr_reqcap ^ if_getcapenable(ifp);
#ifdef DEVICE_POLLING
		if (mask & IFCAP_POLLING) {
			if ((ifr->ifr_reqcap & IFCAP_POLLING) != 0) {
				error = ether_poll_register(awg_poll, ifp);
				if (error != 0)
					break;
				AWG_LOCK(sc);
				awg_disable_intr(sc);
				if_setcapenablebit(ifp, IFCAP_POLLING, 0);
				AWG_UNLOCK(sc);
			} else {
				error = ether_poll_deregister(ifp);
				AWG_LOCK(sc);
				awg_enable_intr(sc);
				if_setcapenablebit(ifp, 0, IFCAP_POLLING);
				AWG_UNLOCK(sc);
			}
		}
#endif
		if (mask & IFCAP_VLAN_MTU)
			if_togglecapenable(ifp, IFCAP_VLAN_MTU);
		if (mask & IFCAP_RXCSUM)
			if_togglecapenable(ifp, IFCAP_RXCSUM);
		if (mask & IFCAP_TXCSUM)
			if_togglecapenable(ifp, IFCAP_TXCSUM);
		if ((if_getcapenable(ifp) & IFCAP_TXCSUM) != 0)
			if_sethwassistbits(ifp, CSUM_IP | CSUM_UDP | CSUM_TCP, 0);
		else
			if_sethwassistbits(ifp, 0, CSUM_IP | CSUM_UDP | CSUM_TCP);
		break;
	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (error);
}