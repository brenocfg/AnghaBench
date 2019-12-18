#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct ifreq {int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int if_flags; int if_drv_flags; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_softc; } ;
typedef  TYPE_1__* priv_p ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  media; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NG_EIFACE_MTU_MAX ; 
 int /*<<< orphan*/  NG_EIFACE_MTU_MIN ; 
#define  SIOCADDMULTI 136 
#define  SIOCDELMULTI 135 
#define  SIOCGIFADDR 134 
#define  SIOCGIFMEDIA 133 
#define  SIOCSIFADDR 132 
#define  SIOCSIFFLAGS 131 
#define  SIOCSIFMEDIA 130 
#define  SIOCSIFMTU 129 
#define  SIOCSIFPHYS 128 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq* const,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ng_eiface_print_ioctl (struct ifnet*,int,scalar_t__) ; 

__attribute__((used)) static int
ng_eiface_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	const priv_p priv = (priv_p)ifp->if_softc;
	struct ifreq *const ifr = (struct ifreq *)data;
	int error = 0;

#ifdef DEBUG
	ng_eiface_print_ioctl(ifp, command, data);
#endif
	switch (command) {

	/* These two are mostly handled at a higher layer */
	case SIOCSIFADDR:
		error = ether_ioctl(ifp, command, data);
		break;
	case SIOCGIFADDR:
		break;

	/* Set flags */
	case SIOCSIFFLAGS:
		/*
		 * If the interface is marked up and stopped, then start it.
		 * If it is marked down and running, then stop it.
		 */
		if (ifp->if_flags & IFF_UP) {
			if (!(ifp->if_drv_flags & IFF_DRV_RUNNING)) {
				ifp->if_drv_flags &= ~(IFF_DRV_OACTIVE);
				ifp->if_drv_flags |= IFF_DRV_RUNNING;
			}
		} else {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				ifp->if_drv_flags &= ~(IFF_DRV_RUNNING |
				    IFF_DRV_OACTIVE);
		}
		break;

	/* Set the interface MTU */
	case SIOCSIFMTU:
		if (ifr->ifr_mtu > NG_EIFACE_MTU_MAX ||
		    ifr->ifr_mtu < NG_EIFACE_MTU_MIN)
			error = EINVAL;
		else
			ifp->if_mtu = ifr->ifr_mtu;
		break;

	/* (Fake) media type manipulation */
	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &priv->media, command);
		break;

	/* Stuff that's not supported */
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		error = 0;
		break;
	case SIOCSIFPHYS:
		error = EOPNOTSUPP;
		break;

	default:
		error = EINVAL;
		break;
	}
	return (error);
}