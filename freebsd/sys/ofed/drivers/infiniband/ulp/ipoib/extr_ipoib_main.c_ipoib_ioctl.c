#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct ipoib_dev_priv {scalar_t__ gone; int /*<<< orphan*/  restart_task; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sa_data; } ;
struct ifreq {int /*<<< orphan*/  ifr_mtu; TYPE_2__ ifr_addr; } ;
struct ifnet {int if_flags; int if_drv_flags; struct ipoib_dev_priv* if_softc; int /*<<< orphan*/  (* if_init ) (struct ipoib_dev_priv*) ;} ;
struct ifaddr {TYPE_1__* ifa_addr; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
#define  AF_INET 134 
 int EINVAL ; 
 int ENXIO ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  INFINIBAND_ALEN ; 
#define  SIOCADDMULTI 133 
#define  SIOCDELMULTI 132 
#define  SIOCGIFADDR 131 
#define  SIOCSIFADDR 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  arp_ifinit (struct ifnet*,struct ifaddr*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ipoib_change_mtu (struct ipoib_dev_priv*,int /*<<< orphan*/ ,int) ; 
 int ipoib_open (struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  ipoib_stop (struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  stub2 (struct ipoib_dev_priv*) ; 

__attribute__((used)) static int
ipoib_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct ipoib_dev_priv *priv = ifp->if_softc;
	struct ifaddr *ifa = (struct ifaddr *) data;
	struct ifreq *ifr = (struct ifreq *) data;
	int error = 0;

	/* check if detaching */
	if (priv == NULL || priv->gone != 0)
		return (ENXIO);

	switch (command) {
	case SIOCSIFFLAGS:
		if (ifp->if_flags & IFF_UP) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
				error = -ipoib_open(priv);
		} else
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				ipoib_stop(priv);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		if (ifp->if_drv_flags & IFF_DRV_RUNNING)
			queue_work(ipoib_workqueue, &priv->restart_task);
		break;
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;

		switch (ifa->ifa_addr->sa_family) {
#ifdef INET
		case AF_INET:
			ifp->if_init(ifp->if_softc);	/* before arpwhohas */
			arp_ifinit(ifp, ifa);
			break;
#endif
		default:
			ifp->if_init(ifp->if_softc);
			break;
		}
		break;

	case SIOCGIFADDR:
			bcopy(IF_LLADDR(ifp), &ifr->ifr_addr.sa_data[0],
                            INFINIBAND_ALEN);
		break;

	case SIOCSIFMTU:
		/*
		 * Set the interface MTU.
		 */
		error = -ipoib_change_mtu(priv, ifr->ifr_mtu, false);
		break;
	default:
		error = EINVAL;
		break;
	}
	return (error);
}