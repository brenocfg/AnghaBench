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
struct ifnet {int if_flags; int if_drv_flags; int (* if_ioctl ) (struct ifnet*,int,scalar_t__) ;struct ieee80211vap* if_softc; int /*<<< orphan*/  (* if_init ) (struct ieee80211vap*) ;int /*<<< orphan*/  if_mtu; int /*<<< orphan*/ * if_bridge; } ;
struct ifaddr {TYPE_1__* ifa_addr; } ;
struct ieee80211vap {int iv_ifflags; int iv_caps; int /*<<< orphan*/  iv_stats; int /*<<< orphan*/  iv_media; int /*<<< orphan*/  iv_myaddr; int /*<<< orphan*/  iv_state; int /*<<< orphan*/  iv_opmode; struct ieee80211com* iv_ic; } ;
struct ieee80211req {int dummy; } ;
struct ieee80211com {int ic_nrunning; int (* ic_ioctl ) (struct ieee80211com*,int,scalar_t__) ;int /*<<< orphan*/  ic_mcast_task; } ;
struct epoch_tracker {int dummy; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
#define  AF_INET 138 
 int EINVAL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_ADDR_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_C_TDMA ; 
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_MTU_MAX ; 
 int /*<<< orphan*/  IEEE80211_MTU_MIN ; 
 int /*<<< orphan*/  IEEE80211_M_AHDEMO ; 
 int /*<<< orphan*/  IEEE80211_M_MONITOR ; 
 int /*<<< orphan*/  IEEE80211_S_INIT ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PPROMISC ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  PRIV_NET80211_MANAGE ; 
#define  SIOCADDMULTI 137 
#define  SIOCDELMULTI 136 
#define  SIOCG80211 135 
#define  SIOCG80211STATS 134 
#define  SIOCGIFMEDIA 133 
#define  SIOCS80211 132 
#define  SIOCSIFADDR 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  arp_ifinit (struct ifnet*,struct ifaddr*) ; 
 int /*<<< orphan*/  copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  curthread ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_allmulti (struct ieee80211vap*,int) ; 
 int /*<<< orphan*/  ieee80211_com_vdecref (struct ieee80211vap*) ; 
 int ieee80211_com_vincref (struct ieee80211vap*) ; 
 int ieee80211_ioctl_get80211 (struct ieee80211vap*,int,struct ieee80211req*) ; 
 int ieee80211_ioctl_set80211 (struct ieee80211vap*,int,struct ieee80211req*) ; 
 int /*<<< orphan*/  ieee80211_promisc (struct ieee80211vap*,int) ; 
 int /*<<< orphan*/  ieee80211_runtask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_start_locked (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_stop_locked (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_waitfor_parent (struct ieee80211com*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ifr_data_get_ptr (struct ifreq*) ; 
 int priv_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211vap*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211vap*) ; 
 int stub3 (struct ieee80211com*,int,scalar_t__) ; 

int
ieee80211_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct ieee80211vap *vap = ifp->if_softc;
	struct ieee80211com *ic = vap->iv_ic;
	int error = 0, wait = 0, ic_used;
	struct ifreq *ifr;
	struct ifaddr *ifa;			/* XXX */

	ic_used = (cmd != SIOCSIFMTU && cmd != SIOCG80211STATS);
	if (ic_used && (error = ieee80211_com_vincref(vap)) != 0)
		return (error);

	switch (cmd) {
	case SIOCSIFFLAGS:
		IEEE80211_LOCK(ic);
		if ((ifp->if_flags ^ vap->iv_ifflags) & IFF_PROMISC) {
			/*
			 * Enable promiscuous mode when:
			 * 1. Interface is not a member of bridge, or
			 * 2. Requested by user, or
			 * 3. In monitor (or adhoc-demo) mode.
			 */
			if (ifp->if_bridge == NULL ||
			    (ifp->if_flags & IFF_PPROMISC) != 0 ||
			    vap->iv_opmode == IEEE80211_M_MONITOR ||
			    (vap->iv_opmode == IEEE80211_M_AHDEMO &&
			    (vap->iv_caps & IEEE80211_C_TDMA) == 0)) {
				ieee80211_promisc(vap,
				    ifp->if_flags & IFF_PROMISC);
				vap->iv_ifflags ^= IFF_PROMISC;
			}
		}
		if ((ifp->if_flags ^ vap->iv_ifflags) & IFF_ALLMULTI) {
			ieee80211_allmulti(vap, ifp->if_flags & IFF_ALLMULTI);
			vap->iv_ifflags ^= IFF_ALLMULTI;
		}
		if (ifp->if_flags & IFF_UP) {
			/*
			 * Bring ourself up unless we're already operational.
			 * If we're the first vap and the parent is not up
			 * then it will automatically be brought up as a
			 * side-effect of bringing ourself up.
			 */
			if (vap->iv_state == IEEE80211_S_INIT) {
				if (ic->ic_nrunning == 0)
					wait = 1;
				ieee80211_start_locked(vap);
			}
		} else if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
			/*
			 * Stop ourself.  If we are the last vap to be
			 * marked down the parent will also be taken down.
			 */
			if (ic->ic_nrunning == 1)
				wait = 1;
			ieee80211_stop_locked(vap);
		}
		IEEE80211_UNLOCK(ic);
		/* Wait for parent ioctl handler if it was queued */
		if (wait) {
			struct epoch_tracker et;

			ieee80211_waitfor_parent(ic);

			/*
			 * Check if the MAC address was changed
			 * via SIOCSIFLLADDR ioctl.
			 *
			 * NB: device may be detached during initialization;
			 * use if_ioctl for existence check.
			 */
			NET_EPOCH_ENTER(et);
			if (ifp->if_ioctl == ieee80211_ioctl &&
			    (ifp->if_flags & IFF_UP) == 0 &&
			    !IEEE80211_ADDR_EQ(vap->iv_myaddr, IF_LLADDR(ifp)))
				IEEE80211_ADDR_COPY(vap->iv_myaddr,
				    IF_LLADDR(ifp));
			NET_EPOCH_EXIT(et);
		}
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		ieee80211_runtask(ic, &ic->ic_mcast_task);
		break;
	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		ifr = (struct ifreq *)data;
		error = ifmedia_ioctl(ifp, ifr, &vap->iv_media, cmd);
		break;
	case SIOCG80211:
		error = ieee80211_ioctl_get80211(vap, cmd,
				(struct ieee80211req *) data);
		break;
	case SIOCS80211:
		error = priv_check(curthread, PRIV_NET80211_MANAGE);
		if (error == 0)
			error = ieee80211_ioctl_set80211(vap, cmd,
					(struct ieee80211req *) data);
		break;
	case SIOCG80211STATS:
		ifr = (struct ifreq *)data;
		copyout(&vap->iv_stats, ifr_data_get_ptr(ifr),
		    sizeof (vap->iv_stats));
		break;
	case SIOCSIFMTU:
		ifr = (struct ifreq *)data;
		if (!(IEEE80211_MTU_MIN <= ifr->ifr_mtu &&
		    ifr->ifr_mtu <= IEEE80211_MTU_MAX))
			error = EINVAL;
		else
			ifp->if_mtu = ifr->ifr_mtu;
		break;
	case SIOCSIFADDR:
		/*
		 * XXX Handle this directly so we can suppress if_init calls.
		 * XXX This should be done in ether_ioctl but for the moment
		 * XXX there are too many other parts of the system that
		 * XXX set IFF_UP and so suppress if_init being called when
		 * XXX it should be.
		 */
		ifa = (struct ifaddr *) data;
		switch (ifa->ifa_addr->sa_family) {
#ifdef INET
		case AF_INET:
			if ((ifp->if_flags & IFF_UP) == 0) {
				ifp->if_flags |= IFF_UP;
				ifp->if_init(ifp->if_softc);
			}
			arp_ifinit(ifp, ifa);
			break;
#endif
		default:
			if ((ifp->if_flags & IFF_UP) == 0) {
				ifp->if_flags |= IFF_UP;
				ifp->if_init(ifp->if_softc);
			}
			break;
		}
		break;
	default:
		/*
		 * Pass unknown ioctls first to the driver, and if it
		 * returns ENOTTY, then to the generic Ethernet handler.
		 */
		if (ic->ic_ioctl != NULL &&
		    (error = ic->ic_ioctl(ic, cmd, data)) != ENOTTY)
			break;
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	if (ic_used)
		ieee80211_com_vdecref(vap);

	return (error);
}