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
struct ifreq {int ifr_flags; int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int if_flags; int if_drv_flags; int /*<<< orphan*/  if_mtu; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NG_IFACE_MTU_MAX ; 
 int /*<<< orphan*/  NG_IFACE_MTU_MIN ; 
#define  SIOCADDMULTI 134 
#define  SIOCDELMULTI 133 
#define  SIOCGIFADDR 132 
#define  SIOCSIFADDR 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMTU 129 
#define  SIOCSIFPHYS 128 
 int /*<<< orphan*/  ng_iface_print_ioctl (struct ifnet*,int,scalar_t__) ; 

__attribute__((used)) static int
ng_iface_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct ifreq *const ifr = (struct ifreq *) data;
	int error = 0;

#ifdef DEBUG
	ng_iface_print_ioctl(ifp, command, data);
#endif
	switch (command) {

	/* These two are mostly handled at a higher layer */
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
		ifp->if_drv_flags |= IFF_DRV_RUNNING;
		ifp->if_drv_flags &= ~(IFF_DRV_OACTIVE);
		break;
	case SIOCGIFADDR:
		break;

	/* Set flags */
	case SIOCSIFFLAGS:
		/*
		 * If the interface is marked up and stopped, then start it.
		 * If it is marked down and running, then stop it.
		 */
		if (ifr->ifr_flags & IFF_UP) {
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
		if (ifr->ifr_mtu > NG_IFACE_MTU_MAX
		    || ifr->ifr_mtu < NG_IFACE_MTU_MIN)
			error = EINVAL;
		else
			ifp->if_mtu = ifr->ifr_mtu;
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