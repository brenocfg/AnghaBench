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
struct vxlan_softc {int /*<<< orphan*/  vxl_media; } ;
struct ifreq {int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int /*<<< orphan*/  if_mtu; struct vxlan_softc* if_softc; } ;
struct ifdrv {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETHERMIN ; 
#define  SIOCADDMULTI 135 
#define  SIOCDELMULTI 134 
#define  SIOCGDRVSPEC 133 
#define  SIOCGIFMEDIA 132 
#define  SIOCSDRVSPEC 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  VXLAN_MAX_MTU ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int vxlan_ioctl_drvspec (struct vxlan_softc*,struct ifdrv*,int) ; 
 int vxlan_ioctl_ifflags (struct vxlan_softc*) ; 

__attribute__((used)) static int
vxlan_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct vxlan_softc *sc;
	struct ifreq *ifr;
	struct ifdrv *ifd;
	int error;

	sc = ifp->if_softc;
	ifr = (struct ifreq *) data;
	ifd = (struct ifdrv *) data;

	error = 0;

	switch (cmd) {
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		break;

	case SIOCGDRVSPEC:
	case SIOCSDRVSPEC:
		error = vxlan_ioctl_drvspec(sc, ifd, cmd == SIOCGDRVSPEC);
		break;

	case SIOCSIFFLAGS:
		error = vxlan_ioctl_ifflags(sc);
		break;

	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &sc->vxl_media, cmd);
		break;

	case SIOCSIFMTU:
		if (ifr->ifr_mtu < ETHERMIN || ifr->ifr_mtu > VXLAN_MAX_MTU)
			error = EINVAL;
		else
			ifp->if_mtu = ifr->ifr_mtu;
		break;

	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (error);
}