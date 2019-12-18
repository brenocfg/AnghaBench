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
struct ifreq {int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int /*<<< orphan*/  if_mtu; struct epair_softc* if_softc; } ;
struct epair_softc {int /*<<< orphan*/  media; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  SIOCADDMULTI 133 
#define  SIOCDELMULTI 132 
#define  SIOCGIFMEDIA 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
epair_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct epair_softc *sc;
	struct ifreq *ifr;
	int error;

	ifr = (struct ifreq *)data;
	switch (cmd) {
	case SIOCSIFFLAGS:
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		error = 0;
		break;

	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		sc = ifp->if_softc;
		error = ifmedia_ioctl(ifp, ifr, &sc->media, cmd);
		break;

	case SIOCSIFMTU:
		/* We basically allow all kinds of MTUs. */
		ifp->if_mtu = ifr->ifr_mtu;
		error = 0;
		break;

	default:
		/* Let the common ethernet handler process this. */
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (error);
}