#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_char ;
struct lp_data {TYPE_2__* sc_ifp; int /*<<< orphan*/ * sc_ifbuf; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  sa_family; } ;
struct ifreq {TYPE_3__ ifr_addr; scalar_t__ ifr_mtu; } ;
struct ifnet {int if_flags; int if_drv_flags; struct lp_data* if_softc; } ;
struct ifaddr {TYPE_1__* ifa_addr; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_5__ {scalar_t__ if_mtu; } ;
struct TYPE_4__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 136 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 scalar_t__ MLPIPHDRLEN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
#define  SIOCADDMULTI 135 
#define  SIOCAIFADDR 134 
#define  SIOCDELMULTI 133 
#define  SIOCGIFMEDIA 132 
#define  SIOCGIFMTU 131 
#define  SIOCSIFADDR 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lpinit_locked (struct ifnet*) ; 
 int /*<<< orphan*/  lprintf (char*,int) ; 
 int /*<<< orphan*/  lpstop (struct lp_data*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct lp_data *sc = ifp->if_softc;
	device_t dev = sc->sc_dev;
	device_t ppbus = device_get_parent(dev);
	struct ifaddr *ifa = (struct ifaddr *)data;
	struct ifreq *ifr = (struct ifreq *)data;
	u_char *ptr;
	int error;

	switch (cmd) {
	case SIOCAIFADDR:
	case SIOCSIFADDR:
		if (ifa->ifa_addr->sa_family != AF_INET)
			return (EAFNOSUPPORT);

		ifp->if_flags |= IFF_UP;
		/* FALLTHROUGH */
	case SIOCSIFFLAGS:
		error = 0;
		ppb_lock(ppbus);
		if ((!(ifp->if_flags & IFF_UP)) &&
		    (ifp->if_drv_flags & IFF_DRV_RUNNING))
			lpstop(sc);
		else if (((ifp->if_flags & IFF_UP)) &&
		    (!(ifp->if_drv_flags & IFF_DRV_RUNNING)))
			error = lpinit_locked(ifp);
		ppb_unlock(ppbus);
		return (error);

	case SIOCSIFMTU:
		ppb_lock(ppbus);
		if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
			ptr = malloc(ifr->ifr_mtu + MLPIPHDRLEN, M_DEVBUF,
			    M_NOWAIT);
			if (ptr == NULL) {
				ppb_unlock(ppbus);
				return (ENOBUFS);
			}
			if (sc->sc_ifbuf)
				free(sc->sc_ifbuf, M_DEVBUF);
			sc->sc_ifbuf = ptr;
		}
		sc->sc_ifp->if_mtu = ifr->ifr_mtu;
		ppb_unlock(ppbus);
		break;

	case SIOCGIFMTU:
		ifr->ifr_mtu = sc->sc_ifp->if_mtu;
		break;

	case SIOCADDMULTI:
	case SIOCDELMULTI:
		if (ifr == NULL) {
			return (EAFNOSUPPORT);		/* XXX */
		}
		switch (ifr->ifr_addr.sa_family) {
		case AF_INET:
			break;
		default:
			return (EAFNOSUPPORT);
		}
		break;

	case SIOCGIFMEDIA:
		/*
		 * No ifmedia support at this stage; maybe use it
		 * in future for eg. protocol selection.
		 */
		return (EINVAL);

	default:
		lprintf("LP:ioctl(0x%lx)\n", cmd);
		return (EINVAL);
	}
	return (0);
}