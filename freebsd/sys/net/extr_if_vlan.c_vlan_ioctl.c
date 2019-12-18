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
typedef  int /*<<< orphan*/  vlr ;
typedef  int u_long ;
struct vlanreq {char* vlr_parent; int /*<<< orphan*/  vlr_tag; } ;
struct ifvlantrunk {int dummy; } ;
struct ifvlan {int ifv_pcp; int /*<<< orphan*/  ifv_capenable; int /*<<< orphan*/  ifv_vid; scalar_t__ ifv_mtufudge; scalar_t__ ifv_mintu; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sa_data; } ;
struct ifreq {int ifr_vlan_pcp; int /*<<< orphan*/  ifr_reqcap; scalar_t__ ifr_mtu; TYPE_2__ ifr_addr; } ;
struct ifnet {int (* if_ioctl ) (struct ifnet*,int const,scalar_t__) ;int if_pcp; int /*<<< orphan*/  if_home_vnet; int /*<<< orphan*/  if_vnet; int /*<<< orphan*/  if_xname; scalar_t__ if_mtu; int /*<<< orphan*/  if_addrlen; int /*<<< orphan*/  if_flags; struct ifvlan* if_softc; } ;
struct ifmediareq {int ifm_count; int /*<<< orphan*/  ifm_ulist; struct vlanreq ifm_current; } ;
struct ifaddr {TYPE_1__* ifa_addr; } ;
struct epoch_tracker {int dummy; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EINVAL ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  IFNET_EVENT_PCP ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 struct ifnet* PARENT (struct ifvlan*) ; 
 int /*<<< orphan*/  PRIV_NET_SETVLANPCP ; 
#define  SIOCADDMULTI 140 
#define  SIOCDELMULTI 139 
#define  SIOCGETVLAN 138 
#define  SIOCGIFADDR 137 
#define  SIOCGIFMEDIA 136 
#define  SIOCGVLANPCP 135 
#define  SIOCSETVLAN 134 
#define  SIOCSIFADDR 133 
#define  SIOCSIFCAP 132 
#define  SIOCSIFFLAGS 131 
#define  SIOCSIFMEDIA 130 
#define  SIOCSIFMTU 129 
#define  SIOCSVLANPCP 128 
 struct ifvlantrunk* TRUNK (struct ifvlan*) ; 
 int /*<<< orphan*/  TRUNK_WLOCK (struct ifvlantrunk*) ; 
 int /*<<< orphan*/  TRUNK_WUNLOCK (struct ifvlantrunk*) ; 
 int /*<<< orphan*/  VLAN_SLOCK () ; 
 int /*<<< orphan*/  VLAN_SUNLOCK () ; 
 int /*<<< orphan*/  VLAN_XLOCK () ; 
 int /*<<< orphan*/  VLAN_XUNLOCK () ; 
 int /*<<< orphan*/  arp_ifinit (struct ifnet*,struct ifaddr*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct vlanreq*,int) ; 
 int copyin (int /*<<< orphan*/ ,struct vlanreq*,int) ; 
 int copyout (struct vlanreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  if_ref (struct ifnet*) ; 
 int /*<<< orphan*/  if_rele (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_event ; 
 int /*<<< orphan*/  ifr_data_get_ptr (struct ifreq*) ; 
 struct ifnet* ifunit_ref (char*) ; 
 int priv_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ifnet*,int const,scalar_t__) ; 
 int /*<<< orphan*/  vlan_capabilities (struct ifvlan*) ; 
 int vlan_config (struct ifvlan*,struct ifnet*,int /*<<< orphan*/ ) ; 
 int vlan_setflags (struct ifnet*,int) ; 
 int vlan_setmulti (struct ifnet*) ; 
 int /*<<< orphan*/  vlan_tag_recalculate (struct ifvlan*) ; 
 int /*<<< orphan*/  vlan_unconfig (struct ifnet*) ; 

__attribute__((used)) static int
vlan_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct ifnet *p;
	struct ifreq *ifr;
	struct ifaddr *ifa;
	struct ifvlan *ifv;
	struct ifvlantrunk *trunk;
	struct vlanreq vlr;
	int error = 0;

	ifr = (struct ifreq *)data;
	ifa = (struct ifaddr *) data;
	ifv = ifp->if_softc;

	switch (cmd) {
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
#ifdef INET
		if (ifa->ifa_addr->sa_family == AF_INET)
			arp_ifinit(ifp, ifa);
#endif
		break;
	case SIOCGIFADDR:
		bcopy(IF_LLADDR(ifp), &ifr->ifr_addr.sa_data[0],
		    ifp->if_addrlen);
		break;
	case SIOCGIFMEDIA:
		VLAN_SLOCK();
		if (TRUNK(ifv) != NULL) {
			p = PARENT(ifv);
			if_ref(p);
			error = (*p->if_ioctl)(p, SIOCGIFMEDIA, data);
			if_rele(p);
			/* Limit the result to the parent's current config. */
			if (error == 0) {
				struct ifmediareq *ifmr;

				ifmr = (struct ifmediareq *)data;
				if (ifmr->ifm_count >= 1 && ifmr->ifm_ulist) {
					ifmr->ifm_count = 1;
					error = copyout(&ifmr->ifm_current,
						ifmr->ifm_ulist,
						sizeof(int));
				}
			}
		} else {
			error = EINVAL;
		}
		VLAN_SUNLOCK();
		break;

	case SIOCSIFMEDIA:
		error = EINVAL;
		break;

	case SIOCSIFMTU:
		/*
		 * Set the interface MTU.
		 */
		VLAN_SLOCK();
		trunk = TRUNK(ifv);
		if (trunk != NULL) {
			TRUNK_WLOCK(trunk);
			if (ifr->ifr_mtu >
			     (PARENT(ifv)->if_mtu - ifv->ifv_mtufudge) ||
			    ifr->ifr_mtu <
			     (ifv->ifv_mintu - ifv->ifv_mtufudge))
				error = EINVAL;
			else
				ifp->if_mtu = ifr->ifr_mtu;
			TRUNK_WUNLOCK(trunk);
		} else
			error = EINVAL;
		VLAN_SUNLOCK();
		break;

	case SIOCSETVLAN:
#ifdef VIMAGE
		/*
		 * XXXRW/XXXBZ: The goal in these checks is to allow a VLAN
		 * interface to be delegated to a jail without allowing the
		 * jail to change what underlying interface/VID it is
		 * associated with.  We are not entirely convinced that this
		 * is the right way to accomplish that policy goal.
		 */
		if (ifp->if_vnet != ifp->if_home_vnet) {
			error = EPERM;
			break;
		}
#endif
		error = copyin(ifr_data_get_ptr(ifr), &vlr, sizeof(vlr));
		if (error)
			break;
		if (vlr.vlr_parent[0] == '\0') {
			vlan_unconfig(ifp);
			break;
		}
		p = ifunit_ref(vlr.vlr_parent);
		if (p == NULL) {
			error = ENOENT;
			break;
		}
		error = vlan_config(ifv, p, vlr.vlr_tag);
		if_rele(p);
		break;

	case SIOCGETVLAN:
#ifdef VIMAGE
		if (ifp->if_vnet != ifp->if_home_vnet) {
			error = EPERM;
			break;
		}
#endif
		bzero(&vlr, sizeof(vlr));
		VLAN_SLOCK();
		if (TRUNK(ifv) != NULL) {
			strlcpy(vlr.vlr_parent, PARENT(ifv)->if_xname,
			    sizeof(vlr.vlr_parent));
			vlr.vlr_tag = ifv->ifv_vid;
		}
		VLAN_SUNLOCK();
		error = copyout(&vlr, ifr_data_get_ptr(ifr), sizeof(vlr));
		break;
		
	case SIOCSIFFLAGS:
		/*
		 * We should propagate selected flags to the parent,
		 * e.g., promiscuous mode.
		 */
		VLAN_XLOCK();
		if (TRUNK(ifv) != NULL)
			error = vlan_setflags(ifp, 1);
		VLAN_XUNLOCK();
		break;

	case SIOCADDMULTI:
	case SIOCDELMULTI:
		/*
		 * If we don't have a parent, just remember the membership for
		 * when we do.
		 *
		 * XXX We need the rmlock here to avoid sleeping while
		 * holding in6_multi_mtx.
		 */
		VLAN_XLOCK();
		trunk = TRUNK(ifv);
		if (trunk != NULL)
			error = vlan_setmulti(ifp);
		VLAN_XUNLOCK();

		break;
	case SIOCGVLANPCP:
#ifdef VIMAGE
		if (ifp->if_vnet != ifp->if_home_vnet) {
			error = EPERM;
			break;
		}
#endif
		ifr->ifr_vlan_pcp = ifv->ifv_pcp;
		break;

	case SIOCSVLANPCP:
#ifdef VIMAGE
		if (ifp->if_vnet != ifp->if_home_vnet) {
			error = EPERM;
			break;
		}
#endif
		error = priv_check(curthread, PRIV_NET_SETVLANPCP);
		if (error)
			break;
		if (ifr->ifr_vlan_pcp > 7) {
			error = EINVAL;
			break;
		}
		ifv->ifv_pcp = ifr->ifr_vlan_pcp;
		ifp->if_pcp = ifv->ifv_pcp;
		vlan_tag_recalculate(ifv);
		/* broadcast event about PCP change */
		EVENTHANDLER_INVOKE(ifnet_event, ifp, IFNET_EVENT_PCP);
		break;

	case SIOCSIFCAP:
		VLAN_SLOCK();
		ifv->ifv_capenable = ifr->ifr_reqcap;
		trunk = TRUNK(ifv);
		if (trunk != NULL) {
			struct epoch_tracker et;

			NET_EPOCH_ENTER(et);
			vlan_capabilities(ifv);
			NET_EPOCH_EXIT(et);
		}
		VLAN_SUNLOCK();
		break;

	default:
		error = EINVAL;
		break;
	}

	return (error);
}