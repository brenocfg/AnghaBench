#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_long ;
struct sockaddr_in6 {int sin_family; int sin_len; int sin6_family; int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr_in {int sin_family; int sin_len; int sin6_family; int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int const sa_family; int sa_len; } ;
struct TYPE_22__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_19__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_23__ {TYPE_7__ sin6; TYPE_4__ sin; } ;
struct TYPE_20__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_18__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_17__ {int const sa_family; } ;
struct TYPE_21__ {TYPE_5__ sin6; TYPE_3__ sin; TYPE_2__ sa; } ;
struct secasindex {TYPE_8__ dst; TYPE_6__ src; } ;
struct ipsec_softc {int /*<<< orphan*/  reqid; int /*<<< orphan*/  fibnum; int /*<<< orphan*/  family; } ;
struct in_aliasreq {int /*<<< orphan*/  ifra_dstaddr; int /*<<< orphan*/  ifra_addr; } ;
struct in6_ifreq {int /*<<< orphan*/  ifr_addr; } ;
struct in6_aliasreq {int /*<<< orphan*/  ifra_dstaddr; int /*<<< orphan*/  ifra_addr; } ;
struct ifreq {int /*<<< orphan*/  ifr_fib; int /*<<< orphan*/  ifr_addr; int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {struct ipsec_softc* if_softc; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_flags; } ;
typedef  int /*<<< orphan*/  reqid ;
typedef  scalar_t__ caddr_t ;
struct TYPE_24__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_16__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_15__ {int /*<<< orphan*/  td_ucred; } ;
struct TYPE_14__ {TYPE_1__ sin_addr; } ;

/* Variables and functions */
#define  AF_INET 146 
#define  AF_INET6 145 
 int EADDRNOTAVAIL ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
#define  IPSECGREQID 144 
#define  IPSECSREQID 143 
 int /*<<< orphan*/  IPSEC_DIR_OUTBOUND ; 
 int /*<<< orphan*/  IPSEC_MTU_MAX ; 
 int /*<<< orphan*/  IPSEC_MTU_MIN ; 
 int /*<<< orphan*/  PRIV_NET_SETIFCAP ; 
 int /*<<< orphan*/  PRIV_NET_SETIFFIB ; 
#define  SIOCADDMULTI 142 
#define  SIOCDELMULTI 141 
#define  SIOCDIFPHYADDR 140 
#define  SIOCGIFMTU 139 
#define  SIOCGIFPDSTADDR 138 
#define  SIOCGIFPDSTADDR_IN6 137 
#define  SIOCGIFPSRCADDR 136 
#define  SIOCGIFPSRCADDR_IN6 135 
#define  SIOCGTUNFIB 134 
#define  SIOCSIFADDR 133 
#define  SIOCSIFFLAGS 132 
#define  SIOCSIFMTU 131 
#define  SIOCSIFPHYADDR 130 
#define  SIOCSIFPHYADDR_IN6 129 
#define  SIOCSTUNFIB 128 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_12__* curthread ; 
 int /*<<< orphan*/  ifr_data_get_ptr (struct ifreq*) ; 
 int /*<<< orphan*/  ipsec_delete_tunnel (struct ipsec_softc*) ; 
 struct secasindex* ipsec_getsaidx (struct ipsec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsec_ioctl_sx ; 
 int ipsec_set_addresses (struct ifnet*,struct sockaddr*,struct sockaddr*) ; 
 int ipsec_set_reqid (struct ipsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int prison_if (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int priv_check (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_numfibs ; 
 int sa6_embedscope (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int sa6_recoverscope (struct sockaddr_in6*) ; 
 TYPE_10__* satosin (struct sockaddr*) ; 
 TYPE_9__* satosin6 (struct sockaddr*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipsec_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct ifreq *ifr = (struct ifreq*)data;
	struct sockaddr *dst, *src;
	struct ipsec_softc *sc;
	struct secasindex *saidx;
#ifdef INET
	struct sockaddr_in *sin = NULL;
#endif
#ifdef INET6
	struct sockaddr_in6 *sin6 = NULL;
#endif
	uint32_t reqid;
	int error;

	switch (cmd) {
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
	case SIOCGIFMTU:
	case SIOCSIFFLAGS:
		return (0);
	case SIOCSIFMTU:
		if (ifr->ifr_mtu < IPSEC_MTU_MIN ||
		    ifr->ifr_mtu > IPSEC_MTU_MAX)
			return (EINVAL);
		else
			ifp->if_mtu = ifr->ifr_mtu;
		return (0);
	}
	sx_xlock(&ipsec_ioctl_sx);
	sc = ifp->if_softc;
	/* Check that softc is still here */
	if (sc == NULL) {
		error = ENXIO;
		goto bad;
	}
	error = 0;
	switch (cmd) {
	case SIOCSIFPHYADDR:
#ifdef INET6
	case SIOCSIFPHYADDR_IN6:
#endif
		error = EINVAL;
		switch (cmd) {
#ifdef INET
		case SIOCSIFPHYADDR:
			src = (struct sockaddr *)
				&(((struct in_aliasreq *)data)->ifra_addr);
			dst = (struct sockaddr *)
				&(((struct in_aliasreq *)data)->ifra_dstaddr);
			break;
#endif
#ifdef INET6
		case SIOCSIFPHYADDR_IN6:
			src = (struct sockaddr *)
				&(((struct in6_aliasreq *)data)->ifra_addr);
			dst = (struct sockaddr *)
				&(((struct in6_aliasreq *)data)->ifra_dstaddr);
			break;
#endif
		default:
			goto bad;
		}
		/* sa_family must be equal */
		if (src->sa_family != dst->sa_family ||
		    src->sa_len != dst->sa_len)
			goto bad;

		/* validate sa_len */
		switch (src->sa_family) {
#ifdef INET
		case AF_INET:
			if (src->sa_len != sizeof(struct sockaddr_in))
				goto bad;
			break;
#endif
#ifdef INET6
		case AF_INET6:
			if (src->sa_len != sizeof(struct sockaddr_in6))
				goto bad;
			break;
#endif
		default:
			error = EAFNOSUPPORT;
			goto bad;
		}
		/* check sa_family looks sane for the cmd */
		error = EAFNOSUPPORT;
		switch (cmd) {
#ifdef INET
		case SIOCSIFPHYADDR:
			if (src->sa_family == AF_INET)
				break;
			goto bad;
#endif
#ifdef INET6
		case SIOCSIFPHYADDR_IN6:
			if (src->sa_family == AF_INET6)
				break;
			goto bad;
#endif
		}
		error = EADDRNOTAVAIL;
		switch (src->sa_family) {
#ifdef INET
		case AF_INET:
			if (satosin(src)->sin_addr.s_addr == INADDR_ANY ||
			    satosin(dst)->sin_addr.s_addr == INADDR_ANY)
				goto bad;
			break;
#endif
#ifdef INET6
		case AF_INET6:
			if (IN6_IS_ADDR_UNSPECIFIED(
			    &satosin6(src)->sin6_addr) ||
			    IN6_IS_ADDR_UNSPECIFIED(
			    &satosin6(dst)->sin6_addr))
				goto bad;
			/*
			 * Check validity of the scope zone ID of the
			 * addresses, and convert it into the kernel
			 * internal form if necessary.
			 */
			error = sa6_embedscope(satosin6(src), 0);
			if (error != 0)
				goto bad;
			error = sa6_embedscope(satosin6(dst), 0);
			if (error != 0)
				goto bad;
#endif
		};
		error = ipsec_set_addresses(ifp, src, dst);
		break;
	case SIOCDIFPHYADDR:
		ipsec_delete_tunnel(sc);
		break;
	case SIOCGIFPSRCADDR:
	case SIOCGIFPDSTADDR:
#ifdef INET6
	case SIOCGIFPSRCADDR_IN6:
	case SIOCGIFPDSTADDR_IN6:
#endif
		if (sc->family == 0) {
			error = EADDRNOTAVAIL;
			break;
		}
		saidx = ipsec_getsaidx(sc, IPSEC_DIR_OUTBOUND, sc->family);
		switch (cmd) {
#ifdef INET
		case SIOCGIFPSRCADDR:
		case SIOCGIFPDSTADDR:
			if (saidx->src.sa.sa_family != AF_INET) {
				error = EADDRNOTAVAIL;
				break;
			}
			sin = (struct sockaddr_in *)&ifr->ifr_addr;
			memset(sin, 0, sizeof(*sin));
			sin->sin_family = AF_INET;
			sin->sin_len = sizeof(*sin);
			break;
#endif
#ifdef INET6
		case SIOCGIFPSRCADDR_IN6:
		case SIOCGIFPDSTADDR_IN6:
			if (saidx->src.sa.sa_family != AF_INET6) {
				error = EADDRNOTAVAIL;
				break;
			}
			sin6 = (struct sockaddr_in6 *)
				&(((struct in6_ifreq *)data)->ifr_addr);
			memset(sin6, 0, sizeof(*sin6));
			sin6->sin6_family = AF_INET6;
			sin6->sin6_len = sizeof(*sin6);
			break;
#endif
		default:
			error = EAFNOSUPPORT;
		}
		if (error == 0) {
			switch (cmd) {
#ifdef INET
			case SIOCGIFPSRCADDR:
				sin->sin_addr = saidx->src.sin.sin_addr;
				break;
			case SIOCGIFPDSTADDR:
				sin->sin_addr = saidx->dst.sin.sin_addr;
				break;
#endif
#ifdef INET6
			case SIOCGIFPSRCADDR_IN6:
				sin6->sin6_addr = saidx->src.sin6.sin6_addr;
				break;
			case SIOCGIFPDSTADDR_IN6:
				sin6->sin6_addr = saidx->dst.sin6.sin6_addr;
				break;
#endif
			}
		}
		if (error != 0)
			break;
		switch (cmd) {
#ifdef INET
		case SIOCGIFPSRCADDR:
		case SIOCGIFPDSTADDR:
			error = prison_if(curthread->td_ucred,
			    (struct sockaddr *)sin);
			if (error != 0)
				memset(sin, 0, sizeof(*sin));
			break;
#endif
#ifdef INET6
		case SIOCGIFPSRCADDR_IN6:
		case SIOCGIFPDSTADDR_IN6:
			error = prison_if(curthread->td_ucred,
			    (struct sockaddr *)sin6);
			if (error == 0)
				error = sa6_recoverscope(sin6);
			if (error != 0)
				memset(sin6, 0, sizeof(*sin6));
#endif
		}
		break;
	case SIOCGTUNFIB:
		ifr->ifr_fib = sc->fibnum;
		break;
	case SIOCSTUNFIB:
		if ((error = priv_check(curthread, PRIV_NET_SETIFFIB)) != 0)
			break;
		if (ifr->ifr_fib >= rt_numfibs)
			error = EINVAL;
		else
			sc->fibnum = ifr->ifr_fib;
		break;
	case IPSECGREQID:
		reqid = sc->reqid;
		error = copyout(&reqid, ifr_data_get_ptr(ifr), sizeof(reqid));
		break;
	case IPSECSREQID:
		if ((error = priv_check(curthread, PRIV_NET_SETIFCAP)) != 0)
			break;
		error = copyin(ifr_data_get_ptr(ifr), &reqid, sizeof(reqid));
		if (error != 0)
			break;
		error = ipsec_set_reqid(sc, reqid);
		break;
	default:
		error = EINVAL;
		break;
	}
bad:
	sx_xunlock(&ipsec_ioctl_sx);
	return (error);
}