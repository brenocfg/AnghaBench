#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u_long ;
typedef  int time_t ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct socket {int dummy; } ;
struct sockaddr_in6 {scalar_t__ sin6_family; scalar_t__ sin6_scope_id; int sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct nd_prefixctl {int ndpr_plen; int ndpr_raf_onlink; int ndpr_raf_auto; int /*<<< orphan*/  ndpr_pltime; int /*<<< orphan*/  ndpr_vltime; struct sockaddr_in6 ndpr_prefix; struct ifnet* ndpr_ifp; } ;
struct nd_prefix {int ndpr_addrcnt; } ;
struct TYPE_18__ {int flags; } ;
struct in6_ndireq {TYPE_4__ ndi; } ;
struct in6_ndifreq32 {int /*<<< orphan*/  ifindex; } ;
struct in6_ndifreq {int /*<<< orphan*/  ifindex; } ;
struct in6_ifstat {int dummy; } ;
struct in6_addrlifetime {int ia6t_vltime; int ia6t_expire; int ia6t_pltime; int ia6t_preferred; } ;
struct TYPE_15__ {int ifru_flags6; struct in6_addrlifetime ifru_lifetime; int /*<<< orphan*/  ifru_icmp6stat; int /*<<< orphan*/  ifru_stat; } ;
struct in6_ifreq {TYPE_1__ ifr_ifru; struct sockaddr_in6 ifr_addr; struct sockaddr_in6 ifr_dstaddr; } ;
struct in6_ifextra {int /*<<< orphan*/  icmp6_ifstat; int /*<<< orphan*/  in6_ifstat; } ;
struct TYPE_19__ {int /*<<< orphan*/  ifa_carp; } ;
struct in6_ifaddr {int ia6_flags; int ia6_updatetime; TYPE_5__ ia_ifa; struct nd_prefix* ia6_ndpr; struct in6_addrlifetime ia6_lifetime; struct sockaddr_in6 ia_prefixmask; struct sockaddr_in6 ia_dstaddr; struct sockaddr_in6 ia_addr; } ;
struct TYPE_17__ {int /*<<< orphan*/  ia6t_pltime; int /*<<< orphan*/  ia6t_vltime; } ;
struct TYPE_16__ {int /*<<< orphan*/  sin6_addr; } ;
struct in6_aliasreq {int ifra_flags; TYPE_3__ ifra_lifetime; TYPE_2__ ifra_prefixmask; struct sockaddr_in6 ifra_addr; int /*<<< orphan*/  ifra_vhid; } ;
struct ifnet {int if_flags; int (* if_ioctl ) (struct ifnet*,int,scalar_t__) ;int /*<<< orphan*/ ** if_afdata; } ;
struct icmp6_ifstat {int dummy; } ;
typedef  int /*<<< orphan*/  pr0 ;
typedef  int /*<<< orphan*/  nd ;
typedef  int /*<<< orphan*/  maxexpire ;
typedef  scalar_t__ caddr_t ;
struct TYPE_14__ {int flags; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  COUNTER_ARRAY_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int EADDRNOTAVAIL ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPFNOSUPPORT ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,struct ifnet*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFADDR_EVENT_DEL ; 
 int IFF_POINTOPOINT ; 
 int IN6_IFF_AUTOCONF ; 
 int /*<<< orphan*/  IN6_MASK_ADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int ND6_IFF_IFDISABLED ; 
 int ND6_INFINITE_LIFETIME ; 
 int /*<<< orphan*/  ND6_WLOCK () ; 
 int /*<<< orphan*/  ND6_WUNLOCK () ; 
 TYPE_12__* ND_IFINFO (struct ifnet*) ; 
 int OSIOCAIFADDR_IN6 ; 
#define  OSIOCGIFINFO_IN6 170 
 int /*<<< orphan*/  PRIV_NETINET_ADDRCTRL6 ; 
 int /*<<< orphan*/  PRIV_NETINET_ND6 ; 
 int /*<<< orphan*/  PRIV_NETINET_SCOPE6 ; 
 int /*<<< orphan*/  PRIV_NET_ADDIFADDR ; 
 int /*<<< orphan*/  PRIV_NET_DELIFADDR ; 
#define  SIOCAADDRCTL_POLICY 169 
#define  SIOCAIFADDR_IN6 168 
#define  SIOCAIFPREFIX_IN6 167 
#define  SIOCCIFPREFIX_IN6 166 
#define  SIOCDADDRCTL_POLICY 165 
#define  SIOCDIFADDR_IN6 164 
#define  SIOCDIFPREFIX_IN6 163 
#define  SIOCGDEFIFACE32_IN6 162 
#define  SIOCGDEFIFACE_IN6 161 
#define  SIOCGETMIFCNT_IN6 160 
#define  SIOCGETSGCNT_IN6 159 
#define  SIOCGIFADDR_IN6 158 
#define  SIOCGIFAFLAG_IN6 157 
#define  SIOCGIFALIFETIME_IN6 156 
#define  SIOCGIFDSTADDR_IN6 155 
#define  SIOCGIFINFO_IN6 154 
#define  SIOCGIFNETMASK_IN6 153 
#define  SIOCGIFPDSTADDR_IN6 152 
#define  SIOCGIFPREFIX_IN6 151 
#define  SIOCGIFPSRCADDR_IN6 150 
#define  SIOCGIFSTAT_ICMP6 149 
#define  SIOCGIFSTAT_IN6 148 
#define  SIOCGNBRINFO_IN6 147 
#define  SIOCGSCOPE6 146 
#define  SIOCGSCOPE6DEF 145 
#define  SIOCSDEFIFACE_IN6 144 
#define  SIOCSGIFPREFIX_IN6 143 
#define  SIOCSIFADDR 142 
#define  SIOCSIFADDR_IN6 141 
#define  SIOCSIFBRDADDR 140 
#define  SIOCSIFDSTADDR 139 
#define  SIOCSIFDSTADDR_IN6 138 
#define  SIOCSIFINFO_FLAGS 137 
#define  SIOCSIFINFO_IN6 136 
#define  SIOCSIFNETMASK 135 
#define  SIOCSIFNETMASK_IN6 134 
#define  SIOCSIFPHYADDR_IN6 133 
#define  SIOCSIFPREFIX_IN6 132 
#define  SIOCSNDFLUSH_IN6 131 
#define  SIOCSPFXFLUSH_IN6 130 
#define  SIOCSRTRFLUSH_IN6 129 
#define  SIOCSSCOPE6 128 
 int /*<<< orphan*/  V_ip6_use_tempaddr ; 
 int /*<<< orphan*/  bzero (struct nd_prefixctl*,int) ; 
 int carp_attach_p (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carp_detach_p (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ifa_free (TYPE_5__*) ; 
 int /*<<< orphan*/  ifaddr_event_ext ; 
 int in6_mask2len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in6_purgeaddr (TYPE_5__*) ; 
 int in6_setscope (int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ *) ; 
 int in6_src_ioctl (int,scalar_t__) ; 
 int in6_tmpifadd (struct in6_ifaddr*,int,int /*<<< orphan*/ ) ; 
 int in6_update_ifa (struct ifnet*,struct in6_aliasreq*,struct in6_ifaddr*,int /*<<< orphan*/ ) ; 
 struct in6_ifaddr* in6ifa_ifpwithaddr (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct in6_ndireq*,int /*<<< orphan*/ ,int) ; 
 int mrt6_ioctl (int,scalar_t__) ; 
 int nd6_ioctl (int const,scalar_t__,struct ifnet*) ; 
 int /*<<< orphan*/  nd6_prefix_del (struct nd_prefix*) ; 
 struct nd_prefix* nd6_prefix_lookup (struct nd_prefixctl*) ; 
 int /*<<< orphan*/  nd6_prefix_rele (struct nd_prefix*) ; 
 int /*<<< orphan*/  nd6_prefix_unlink (struct nd_prefix*,int /*<<< orphan*/ *) ; 
 int nd6_prelist_add (struct nd_prefixctl*,int /*<<< orphan*/ *,struct nd_prefix**) ; 
 int /*<<< orphan*/  pfxlist_onlink_check () ; 
 int prison_check_ip6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int sa6_embedscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 int sa6_recoverscope (struct sockaddr_in6*) ; 
 int scope6_ioctl (int,scalar_t__,struct ifnet*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int) ; 
 int stub2 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,int) ; 
 int stub4 (struct ifnet*,int,scalar_t__) ; 

int
in6_control(struct socket *so, u_long cmd, caddr_t data,
    struct ifnet *ifp, struct thread *td)
{
	struct	in6_ifreq *ifr = (struct in6_ifreq *)data;
	struct	in6_ifaddr *ia = NULL;
	struct	in6_aliasreq *ifra = (struct in6_aliasreq *)data;
	struct sockaddr_in6 *sa6;
	int carp_attached = 0;
	int error;
	u_long ocmd = cmd;

	/*
	 * Compat to make pre-10.x ifconfig(8) operable.
	 */
	if (cmd == OSIOCAIFADDR_IN6)
		cmd = SIOCAIFADDR_IN6;

	switch (cmd) {
	case SIOCGETSGCNT_IN6:
	case SIOCGETMIFCNT_IN6:
		/*
		 * XXX mrt_ioctl has a 3rd, unused, FIB argument in route.c.
		 * We cannot see how that would be needed, so do not adjust the
		 * KPI blindly; more likely should clean up the IPv4 variant.
		 */
		return (mrt6_ioctl ? mrt6_ioctl(cmd, data) : EOPNOTSUPP);
	}

	switch (cmd) {
	case SIOCAADDRCTL_POLICY:
	case SIOCDADDRCTL_POLICY:
		if (td != NULL) {
			error = priv_check(td, PRIV_NETINET_ADDRCTRL6);
			if (error)
				return (error);
		}
		return (in6_src_ioctl(cmd, data));
	}

	if (ifp == NULL)
		return (EOPNOTSUPP);

	switch (cmd) {
	case SIOCSNDFLUSH_IN6:
	case SIOCSPFXFLUSH_IN6:
	case SIOCSRTRFLUSH_IN6:
	case SIOCSDEFIFACE_IN6:
	case SIOCSIFINFO_FLAGS:
	case SIOCSIFINFO_IN6:
		if (td != NULL) {
			error = priv_check(td, PRIV_NETINET_ND6);
			if (error)
				return (error);
		}
		/* FALLTHROUGH */
	case OSIOCGIFINFO_IN6:
	case SIOCGIFINFO_IN6:
	case SIOCGNBRINFO_IN6:
	case SIOCGDEFIFACE_IN6:
		return (nd6_ioctl(cmd, data, ifp));

#ifdef COMPAT_FREEBSD32
	case SIOCGDEFIFACE32_IN6:
		{
			struct in6_ndifreq ndif;
			struct in6_ndifreq32 *ndif32;

			error = nd6_ioctl(SIOCGDEFIFACE_IN6, (caddr_t)&ndif,
			    ifp);
			if (error)
				return (error);
			ndif32 = (struct in6_ndifreq32 *)data;
			ndif32->ifindex = ndif.ifindex;
			return (0);
		}
#endif
	}

	switch (cmd) {
	case SIOCSIFPREFIX_IN6:
	case SIOCDIFPREFIX_IN6:
	case SIOCAIFPREFIX_IN6:
	case SIOCCIFPREFIX_IN6:
	case SIOCSGIFPREFIX_IN6:
	case SIOCGIFPREFIX_IN6:
		log(LOG_NOTICE,
		    "prefix ioctls are now invalidated. "
		    "please use ifconfig.\n");
		return (EOPNOTSUPP);
	}

	switch (cmd) {
	case SIOCSSCOPE6:
		if (td != NULL) {
			error = priv_check(td, PRIV_NETINET_SCOPE6);
			if (error)
				return (error);
		}
		/* FALLTHROUGH */
	case SIOCGSCOPE6:
	case SIOCGSCOPE6DEF:
		return (scope6_ioctl(cmd, data, ifp));
	}

	/*
	 * Find address for this interface, if it exists.
	 *
	 * In netinet code, we have checked ifra_addr in SIOCSIF*ADDR operation
	 * only, and used the first interface address as the target of other
	 * operations (without checking ifra_addr).  This was because netinet
	 * code/API assumed at most 1 interface address per interface.
	 * Since IPv6 allows a node to assign multiple addresses
	 * on a single interface, we almost always look and check the
	 * presence of ifra_addr, and reject invalid ones here.
	 * It also decreases duplicated code among SIOC*_IN6 operations.
	 */
	switch (cmd) {
	case SIOCAIFADDR_IN6:
	case SIOCSIFPHYADDR_IN6:
		sa6 = &ifra->ifra_addr;
		break;
	case SIOCSIFADDR_IN6:
	case SIOCGIFADDR_IN6:
	case SIOCSIFDSTADDR_IN6:
	case SIOCSIFNETMASK_IN6:
	case SIOCGIFDSTADDR_IN6:
	case SIOCGIFNETMASK_IN6:
	case SIOCDIFADDR_IN6:
	case SIOCGIFPSRCADDR_IN6:
	case SIOCGIFPDSTADDR_IN6:
	case SIOCGIFAFLAG_IN6:
	case SIOCSNDFLUSH_IN6:
	case SIOCSPFXFLUSH_IN6:
	case SIOCSRTRFLUSH_IN6:
	case SIOCGIFALIFETIME_IN6:
	case SIOCGIFSTAT_IN6:
	case SIOCGIFSTAT_ICMP6:
		sa6 = &ifr->ifr_addr;
		break;
	case SIOCSIFADDR:
	case SIOCSIFBRDADDR:
	case SIOCSIFDSTADDR:
	case SIOCSIFNETMASK:
		/*
		 * Although we should pass any non-INET6 ioctl requests
		 * down to driver, we filter some legacy INET requests.
		 * Drivers trust SIOCSIFADDR et al to come from an already
		 * privileged layer, and do not perform any credentials
		 * checks or input validation.
		 */
		return (EINVAL);
	default:
		sa6 = NULL;
		break;
	}
	if (sa6 && sa6->sin6_family == AF_INET6) {
		if (sa6->sin6_scope_id != 0)
			error = sa6_embedscope(sa6, 0);
		else
			error = in6_setscope(&sa6->sin6_addr, ifp, NULL);
		if (error != 0)
			return (error);
		if (td != NULL && (error = prison_check_ip6(td->td_ucred,
		    &sa6->sin6_addr)) != 0)
			return (error);
		ia = in6ifa_ifpwithaddr(ifp, &sa6->sin6_addr);
	} else
		ia = NULL;

	switch (cmd) {
	case SIOCSIFADDR_IN6:
	case SIOCSIFDSTADDR_IN6:
	case SIOCSIFNETMASK_IN6:
		/*
		 * Since IPv6 allows a node to assign multiple addresses
		 * on a single interface, SIOCSIFxxx ioctls are deprecated.
		 */
		/* we decided to obsolete this command (20000704) */
		error = EINVAL;
		goto out;

	case SIOCDIFADDR_IN6:
		/*
		 * for IPv4, we look for existing in_ifaddr here to allow
		 * "ifconfig if0 delete" to remove the first IPv4 address on
		 * the interface.  For IPv6, as the spec allows multiple
		 * interface address from the day one, we consider "remove the
		 * first one" semantics to be not preferable.
		 */
		if (ia == NULL) {
			error = EADDRNOTAVAIL;
			goto out;
		}
		/* FALLTHROUGH */
	case SIOCAIFADDR_IN6:
		/*
		 * We always require users to specify a valid IPv6 address for
		 * the corresponding operation.
		 */
		if (ifra->ifra_addr.sin6_family != AF_INET6 ||
		    ifra->ifra_addr.sin6_len != sizeof(struct sockaddr_in6)) {
			error = EAFNOSUPPORT;
			goto out;
		}

		if (td != NULL) {
			error = priv_check(td, (cmd == SIOCDIFADDR_IN6) ?
			    PRIV_NET_DELIFADDR : PRIV_NET_ADDIFADDR);
			if (error)
				goto out;
		}
		/* FALLTHROUGH */
	case SIOCGIFSTAT_IN6:
	case SIOCGIFSTAT_ICMP6:
		if (ifp->if_afdata[AF_INET6] == NULL) {
			error = EPFNOSUPPORT;
			goto out;
		}
		break;

	case SIOCGIFADDR_IN6:
		/* This interface is basically deprecated. use SIOCGIFCONF. */
		/* FALLTHROUGH */
	case SIOCGIFAFLAG_IN6:
	case SIOCGIFNETMASK_IN6:
	case SIOCGIFDSTADDR_IN6:
	case SIOCGIFALIFETIME_IN6:
		/* must think again about its semantics */
		if (ia == NULL) {
			error = EADDRNOTAVAIL;
			goto out;
		}
		break;
	}

	switch (cmd) {
	case SIOCGIFADDR_IN6:
		ifr->ifr_addr = ia->ia_addr;
		if ((error = sa6_recoverscope(&ifr->ifr_addr)) != 0)
			goto out;
		break;

	case SIOCGIFDSTADDR_IN6:
		if ((ifp->if_flags & IFF_POINTOPOINT) == 0) {
			error = EINVAL;
			goto out;
		}
		ifr->ifr_dstaddr = ia->ia_dstaddr;
		if ((error = sa6_recoverscope(&ifr->ifr_dstaddr)) != 0)
			goto out;
		break;

	case SIOCGIFNETMASK_IN6:
		ifr->ifr_addr = ia->ia_prefixmask;
		break;

	case SIOCGIFAFLAG_IN6:
		ifr->ifr_ifru.ifru_flags6 = ia->ia6_flags;
		break;

	case SIOCGIFSTAT_IN6:
		COUNTER_ARRAY_COPY(((struct in6_ifextra *)
		    ifp->if_afdata[AF_INET6])->in6_ifstat,
		    &ifr->ifr_ifru.ifru_stat,
		    sizeof(struct in6_ifstat) / sizeof(uint64_t));
		break;

	case SIOCGIFSTAT_ICMP6:
		COUNTER_ARRAY_COPY(((struct in6_ifextra *)
		    ifp->if_afdata[AF_INET6])->icmp6_ifstat,
		    &ifr->ifr_ifru.ifru_icmp6stat,
		    sizeof(struct icmp6_ifstat) / sizeof(uint64_t));
		break;

	case SIOCGIFALIFETIME_IN6:
		ifr->ifr_ifru.ifru_lifetime = ia->ia6_lifetime;
		if (ia->ia6_lifetime.ia6t_vltime != ND6_INFINITE_LIFETIME) {
			time_t maxexpire;
			struct in6_addrlifetime *retlt =
			    &ifr->ifr_ifru.ifru_lifetime;

			/*
			 * XXX: adjust expiration time assuming time_t is
			 * signed.
			 */
			maxexpire = (-1) &
			    ~((time_t)1 << ((sizeof(maxexpire) * 8) - 1));
			if (ia->ia6_lifetime.ia6t_vltime <
			    maxexpire - ia->ia6_updatetime) {
				retlt->ia6t_expire = ia->ia6_updatetime +
				    ia->ia6_lifetime.ia6t_vltime;
			} else
				retlt->ia6t_expire = maxexpire;
		}
		if (ia->ia6_lifetime.ia6t_pltime != ND6_INFINITE_LIFETIME) {
			time_t maxexpire;
			struct in6_addrlifetime *retlt =
			    &ifr->ifr_ifru.ifru_lifetime;

			/*
			 * XXX: adjust expiration time assuming time_t is
			 * signed.
			 */
			maxexpire = (-1) &
			    ~((time_t)1 << ((sizeof(maxexpire) * 8) - 1));
			if (ia->ia6_lifetime.ia6t_pltime <
			    maxexpire - ia->ia6_updatetime) {
				retlt->ia6t_preferred = ia->ia6_updatetime +
				    ia->ia6_lifetime.ia6t_pltime;
			} else
				retlt->ia6t_preferred = maxexpire;
		}
		break;

	case SIOCAIFADDR_IN6:
	{
		struct nd_prefixctl pr0;
		struct nd_prefix *pr;

		/*
		 * first, make or update the interface address structure,
		 * and link it to the list.
		 */
		if ((error = in6_update_ifa(ifp, ifra, ia, 0)) != 0)
			goto out;
		if (ia != NULL) {
			if (ia->ia_ifa.ifa_carp)
				(*carp_detach_p)(&ia->ia_ifa, true);
			ifa_free(&ia->ia_ifa);
		}
		if ((ia = in6ifa_ifpwithaddr(ifp, &ifra->ifra_addr.sin6_addr))
		    == NULL) {
			/*
			 * this can happen when the user specify the 0 valid
			 * lifetime.
			 */
			break;
		}

		if (cmd == ocmd && ifra->ifra_vhid > 0) {
			if (carp_attach_p != NULL)
				error = (*carp_attach_p)(&ia->ia_ifa,
				    ifra->ifra_vhid);
			else
				error = EPROTONOSUPPORT;
			if (error)
				goto out;
			else
				carp_attached = 1;
		}

		/*
		 * then, make the prefix on-link on the interface.
		 * XXX: we'd rather create the prefix before the address, but
		 * we need at least one address to install the corresponding
		 * interface route, so we configure the address first.
		 */

		/*
		 * convert mask to prefix length (prefixmask has already
		 * been validated in in6_update_ifa().
		 */
		bzero(&pr0, sizeof(pr0));
		pr0.ndpr_ifp = ifp;
		pr0.ndpr_plen = in6_mask2len(&ifra->ifra_prefixmask.sin6_addr,
		    NULL);
		if (pr0.ndpr_plen == 128) {
			/* we don't need to install a host route. */
			goto aifaddr_out;
		}
		pr0.ndpr_prefix = ifra->ifra_addr;
		/* apply the mask for safety. */
		IN6_MASK_ADDR(&pr0.ndpr_prefix.sin6_addr,
		    &ifra->ifra_prefixmask.sin6_addr);

		/*
		 * XXX: since we don't have an API to set prefix (not address)
		 * lifetimes, we just use the same lifetimes as addresses.
		 * The (temporarily) installed lifetimes can be overridden by
		 * later advertised RAs (when accept_rtadv is non 0), which is
		 * an intended behavior.
		 */
		pr0.ndpr_raf_onlink = 1; /* should be configurable? */
		pr0.ndpr_raf_auto =
		    ((ifra->ifra_flags & IN6_IFF_AUTOCONF) != 0);
		pr0.ndpr_vltime = ifra->ifra_lifetime.ia6t_vltime;
		pr0.ndpr_pltime = ifra->ifra_lifetime.ia6t_pltime;

		/* add the prefix if not yet. */
		if ((pr = nd6_prefix_lookup(&pr0)) == NULL) {
			/*
			 * nd6_prelist_add will install the corresponding
			 * interface route.
			 */
			if ((error = nd6_prelist_add(&pr0, NULL, &pr)) != 0) {
				if (carp_attached)
					(*carp_detach_p)(&ia->ia_ifa, false);
				goto out;
			}
		}

		/* relate the address to the prefix */
		if (ia->ia6_ndpr == NULL) {
			ia->ia6_ndpr = pr;
			pr->ndpr_addrcnt++;

			/*
			 * If this is the first autoconf address from the
			 * prefix, create a temporary address as well
			 * (when required).
			 */
			if ((ia->ia6_flags & IN6_IFF_AUTOCONF) &&
			    V_ip6_use_tempaddr && pr->ndpr_addrcnt == 1) {
				int e;
				if ((e = in6_tmpifadd(ia, 1, 0)) != 0) {
					log(LOG_NOTICE, "in6_control: failed "
					    "to create a temporary address, "
					    "errno=%d\n", e);
				}
			}
		}
		nd6_prefix_rele(pr);

		/*
		 * this might affect the status of autoconfigured addresses,
		 * that is, this address might make other addresses detached.
		 */
		pfxlist_onlink_check();

aifaddr_out:
		/*
		 * Try to clear the flag when a new IPv6 address is added
		 * onto an IFDISABLED interface and it succeeds.
		 */
		if (ND_IFINFO(ifp)->flags & ND6_IFF_IFDISABLED) {
			struct in6_ndireq nd;

			memset(&nd, 0, sizeof(nd));
			nd.ndi.flags = ND_IFINFO(ifp)->flags;
			nd.ndi.flags &= ~ND6_IFF_IFDISABLED;
			if (nd6_ioctl(SIOCSIFINFO_FLAGS, (caddr_t)&nd, ifp) < 0)
				log(LOG_NOTICE, "SIOCAIFADDR_IN6: "
				    "SIOCSIFINFO_FLAGS for -ifdisabled "
				    "failed.");
			/*
			 * Ignore failure of clearing the flag intentionally.
			 * The failure means address duplication was detected.
			 */
		}
		break;
	}

	case SIOCDIFADDR_IN6:
	{
		struct nd_prefix *pr;

		/*
		 * If the address being deleted is the only one that owns
		 * the corresponding prefix, expire the prefix as well.
		 * XXX: theoretically, we don't have to worry about such
		 * relationship, since we separate the address management
		 * and the prefix management.  We do this, however, to provide
		 * as much backward compatibility as possible in terms of
		 * the ioctl operation.
		 * Note that in6_purgeaddr() will decrement ndpr_addrcnt.
		 */
		pr = ia->ia6_ndpr;
		in6_purgeaddr(&ia->ia_ifa);
		if (pr != NULL && pr->ndpr_addrcnt == 0) {
			ND6_WLOCK();
			nd6_prefix_unlink(pr, NULL);
			ND6_WUNLOCK();
			nd6_prefix_del(pr);
		}
		EVENTHANDLER_INVOKE(ifaddr_event_ext, ifp, &ia->ia_ifa,
		    IFADDR_EVENT_DEL);
		break;
	}

	default:
		if (ifp->if_ioctl == NULL) {
			error = EOPNOTSUPP;
			goto out;
		}
		error = (*ifp->if_ioctl)(ifp, cmd, data);
		goto out;
	}

	error = 0;
out:
	if (ia != NULL)
		ifa_free(&ia->ia_ifa);
	return (error);
}