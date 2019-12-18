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
struct vr_softc {int vr_if_flags; int vr_flags; int /*<<< orphan*/  vr_miibus; } ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; int if_capabilities; int /*<<< orphan*/  if_hwassist; struct vr_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_2 (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_POLLING ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_WOL_MAGIC ; 
 int IFCAP_WOL_UCAST ; 
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
 int /*<<< orphan*/  VR_CSUM_FEATURES ; 
 int VR_F_DETACHED ; 
 int /*<<< orphan*/  VR_IMR ; 
 int VR_INTRS ; 
 int /*<<< orphan*/  VR_LOCK (struct vr_softc*) ; 
 int /*<<< orphan*/  VR_UNLOCK (struct vr_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ether_poll_deregister (struct ifnet*) ; 
 int ether_poll_register (int /*<<< orphan*/ ,struct ifnet*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vr_init_locked (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_poll ; 
 int /*<<< orphan*/  vr_set_filter (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_stop (struct vr_softc*) ; 

__attribute__((used)) static int
vr_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct vr_softc		*sc;
	struct ifreq		*ifr;
	struct mii_data		*mii;
	int			error, mask;

	sc = ifp->if_softc;
	ifr = (struct ifreq *)data;
	error = 0;

	switch (command) {
	case SIOCSIFFLAGS:
		VR_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				if ((ifp->if_flags ^ sc->vr_if_flags) &
				    (IFF_PROMISC | IFF_ALLMULTI))
					vr_set_filter(sc);
			} else {
				if ((sc->vr_flags & VR_F_DETACHED) == 0)
					vr_init_locked(sc);
			}
		} else {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				vr_stop(sc);
		}
		sc->vr_if_flags = ifp->if_flags;
		VR_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		VR_LOCK(sc);
		vr_set_filter(sc);
		VR_UNLOCK(sc);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		mii = device_get_softc(sc->vr_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, command);
		break;
	case SIOCSIFCAP:
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
#ifdef DEVICE_POLLING
		if (mask & IFCAP_POLLING) {
			if (ifr->ifr_reqcap & IFCAP_POLLING) {
				error = ether_poll_register(vr_poll, ifp);
				if (error != 0)
					break;
				VR_LOCK(sc);
				/* Disable interrupts. */
				CSR_WRITE_2(sc, VR_IMR, 0x0000);
				ifp->if_capenable |= IFCAP_POLLING;
				VR_UNLOCK(sc);
			} else {
				error = ether_poll_deregister(ifp);
				/* Enable interrupts. */
				VR_LOCK(sc);
				CSR_WRITE_2(sc, VR_IMR, VR_INTRS);
				ifp->if_capenable &= ~IFCAP_POLLING;
				VR_UNLOCK(sc);
			}
		}
#endif /* DEVICE_POLLING */
		if ((mask & IFCAP_TXCSUM) != 0 &&
		    (IFCAP_TXCSUM & ifp->if_capabilities) != 0) {
			ifp->if_capenable ^= IFCAP_TXCSUM;
			if ((IFCAP_TXCSUM & ifp->if_capenable) != 0)
				ifp->if_hwassist |= VR_CSUM_FEATURES;
			else
				ifp->if_hwassist &= ~VR_CSUM_FEATURES;
		}
		if ((mask & IFCAP_RXCSUM) != 0 &&
		    (IFCAP_RXCSUM & ifp->if_capabilities) != 0)
			ifp->if_capenable ^= IFCAP_RXCSUM;
		if ((mask & IFCAP_WOL_UCAST) != 0 &&
		    (ifp->if_capabilities & IFCAP_WOL_UCAST) != 0)
			ifp->if_capenable ^= IFCAP_WOL_UCAST;
		if ((mask & IFCAP_WOL_MAGIC) != 0 &&
		    (ifp->if_capabilities & IFCAP_WOL_MAGIC) != 0)
			ifp->if_capenable ^= IFCAP_WOL_MAGIC;
		break;
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}