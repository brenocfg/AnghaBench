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
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; int if_capabilities; int /*<<< orphan*/  if_hwassist; int /*<<< orphan*/  if_mtu; struct et_softc* if_softc; } ;
struct et_softc {int sc_if_flags; int sc_flags; int /*<<< orphan*/  sc_miibus; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ET_CSUM_FEATURES ; 
 int ET_FLAG_JUMBO ; 
 int ET_FRAMELEN (int /*<<< orphan*/ ) ; 
 int ET_JUMBO_FRAMELEN ; 
 int /*<<< orphan*/  ET_LOCK (struct et_softc*) ; 
 int /*<<< orphan*/  ET_UNLOCK (struct et_softc*) ; 
 int IFCAP_TXCSUM ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  MCLBYTES ; 
#define  SIOCADDMULTI 134 
#define  SIOCDELMULTI 133 
#define  SIOCGIFMEDIA 132 
#define  SIOCSIFCAP 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et_init_locked (struct et_softc*) ; 
 int /*<<< orphan*/  et_setmulti (struct et_softc*) ; 
 int /*<<< orphan*/  et_stop (struct et_softc*) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
et_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct et_softc *sc;
	struct mii_data *mii;
	struct ifreq *ifr;
	int error, mask, max_framelen;

	sc = ifp->if_softc;
	ifr = (struct ifreq *)data;
	error = 0;

/* XXX LOCKSUSED */
	switch (cmd) {
	case SIOCSIFFLAGS:
		ET_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				if ((ifp->if_flags ^ sc->sc_if_flags) &
				(IFF_ALLMULTI | IFF_PROMISC | IFF_BROADCAST))
					et_setmulti(sc);
			} else {
				et_init_locked(sc);
			}
		} else {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				et_stop(sc);
		}
		sc->sc_if_flags = ifp->if_flags;
		ET_UNLOCK(sc);
		break;

	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		mii = device_get_softc(sc->sc_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, cmd);
		break;

	case SIOCADDMULTI:
	case SIOCDELMULTI:
		if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
			ET_LOCK(sc);
			et_setmulti(sc);
			ET_UNLOCK(sc);
		}
		break;

	case SIOCSIFMTU:
		ET_LOCK(sc);
#if 0
		if (sc->sc_flags & ET_FLAG_JUMBO)
			max_framelen = ET_JUMBO_FRAMELEN;
		else
#endif
			max_framelen = MCLBYTES - 1;

		if (ET_FRAMELEN(ifr->ifr_mtu) > max_framelen) {
			error = EOPNOTSUPP;
			ET_UNLOCK(sc);
			break;
		}

		if (ifp->if_mtu != ifr->ifr_mtu) {
			ifp->if_mtu = ifr->ifr_mtu;
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
				et_init_locked(sc);
			}
		}
		ET_UNLOCK(sc);
		break;

	case SIOCSIFCAP:
		ET_LOCK(sc);
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
		if ((mask & IFCAP_TXCSUM) != 0 &&
		    (IFCAP_TXCSUM & ifp->if_capabilities) != 0) {
			ifp->if_capenable ^= IFCAP_TXCSUM;
			if ((IFCAP_TXCSUM & ifp->if_capenable) != 0)
				ifp->if_hwassist |= ET_CSUM_FEATURES;
			else
				ifp->if_hwassist &= ~ET_CSUM_FEATURES;
		}
		ET_UNLOCK(sc);
		break;

	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}
	return (error);
}