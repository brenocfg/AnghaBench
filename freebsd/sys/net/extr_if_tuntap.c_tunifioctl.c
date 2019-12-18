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
struct tuntap_softc {int tun_flags; int tun_pid; } ;
struct ifstat {char* ascii; } ;
struct ifreq {int /*<<< orphan*/  ifr_reqcap; int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int /*<<< orphan*/  if_capenable; int /*<<< orphan*/  if_mtu; struct tuntap_softc* if_softc; } ;
struct ifmediareq {int ifm_count; int /*<<< orphan*/  ifm_ulist; void* ifm_active; void* ifm_current; int /*<<< orphan*/  ifm_status; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 void* IFM_ETHER ; 
#define  SIOCADDMULTI 135 
#define  SIOCDELMULTI 134 
#define  SIOCGIFMEDIA 133 
#define  SIOCGIFSTATUS 132 
#define  SIOCSIFADDR 131 
#define  SIOCSIFCAP 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  TUNDEBUG (struct ifnet*,char*) ; 
 int TUN_L2 ; 
 int /*<<< orphan*/  TUN_LOCK (struct tuntap_softc*) ; 
 int TUN_OPEN ; 
 int /*<<< orphan*/  TUN_UNLOCK (struct tuntap_softc*) ; 
 int /*<<< orphan*/  VLAN_CAPABILITIES (struct ifnet*) ; 
 int copyout (int*,int /*<<< orphan*/ ,int) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tun_caps_changed (struct ifnet*) ; 
 int /*<<< orphan*/  tun_ioctl_sx ; 
 int /*<<< orphan*/  tuninit (struct ifnet*) ; 

__attribute__((used)) static int
tunifioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct ifreq *ifr = (struct ifreq *)data;
	struct tuntap_softc *tp;
	struct ifstat *ifs;
	struct ifmediareq	*ifmr;
	int		dummy, error = 0;
	bool		l2tun;

	ifmr = NULL;
	sx_xlock(&tun_ioctl_sx);
	tp = ifp->if_softc;
	if (tp == NULL) {
		error = ENXIO;
		goto bad;
	}
	l2tun = (tp->tun_flags & TUN_L2) != 0;
	switch(cmd) {
	case SIOCGIFSTATUS:
		ifs = (struct ifstat *)data;
		TUN_LOCK(tp);
		if (tp->tun_pid)
			snprintf(ifs->ascii, sizeof(ifs->ascii),
			    "\tOpened by PID %d\n", tp->tun_pid);
		else
			ifs->ascii[0] = '\0';
		TUN_UNLOCK(tp);
		break;
	case SIOCSIFADDR:
		if (l2tun)
			error = ether_ioctl(ifp, cmd, data);
		else
			tuninit(ifp);
		if (error == 0)
		    TUNDEBUG(ifp, "address set\n");
		break;
	case SIOCSIFMTU:
		ifp->if_mtu = ifr->ifr_mtu;
		TUNDEBUG(ifp, "mtu set\n");
		break;
	case SIOCSIFFLAGS:
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		break;
	case SIOCGIFMEDIA:
		if (!l2tun) {
			error = EINVAL;
			break;
		}

		ifmr = (struct ifmediareq *)data;
		dummy = ifmr->ifm_count;
		ifmr->ifm_count = 1;
		ifmr->ifm_status = IFM_AVALID;
		ifmr->ifm_active = IFM_ETHER;
		if (tp->tun_flags & TUN_OPEN)
			ifmr->ifm_status |= IFM_ACTIVE;
		ifmr->ifm_current = ifmr->ifm_active;
		if (dummy >= 1) {
			int media = IFM_ETHER;
			error = copyout(&media, ifmr->ifm_ulist, sizeof(int));
		}
		break;
	case SIOCSIFCAP:
		TUN_LOCK(tp);
		ifp->if_capenable = ifr->ifr_reqcap;
		tun_caps_changed(ifp);
		TUN_UNLOCK(tp);
		VLAN_CAPABILITIES(ifp);
		break;
	default:
		if (l2tun) {
			error = ether_ioctl(ifp, cmd, data);
		} else {
			error = EINVAL;
		}
	}
bad:
	sx_xunlock(&tun_ioctl_sx);
	return (error);
}