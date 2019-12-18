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
typedef  int u_int ;
struct ifreq {int /*<<< orphan*/  ifr_fib; int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {struct gif_softc* if_softc; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_flags; } ;
struct gif_softc {scalar_t__ gif_family; int gif_options; int /*<<< orphan*/  gif_fibnum; } ;
typedef  int /*<<< orphan*/  options ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  AF_INET 146 
#define  AF_INET6 145 
 int EINVAL ; 
 int ENXIO ; 
#define  GIFGOPTS 144 
#define  GIFSOPTS 143 
 int /*<<< orphan*/  GIF_MTU_MAX ; 
 int /*<<< orphan*/  GIF_MTU_MIN ; 
 int GIF_OPTMASK ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  PRIV_NET_GIF ; 
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
 int copyin (int /*<<< orphan*/ ,int*,int) ; 
 int copyout (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  gif_delete_tunnel (struct gif_softc*) ; 
 int /*<<< orphan*/  gif_ioctl_sx ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifr_data_get_ptr (struct ifreq*) ; 
 int in6_gif_ioctl (struct gif_softc*,int,scalar_t__) ; 
 int in6_gif_setopts (struct gif_softc*,int) ; 
 int in_gif_ioctl (struct gif_softc*,int,scalar_t__) ; 
 int in_gif_setopts (struct gif_softc*,int) ; 
 int priv_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_numfibs ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gif_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct ifreq *ifr = (struct ifreq*)data;
	struct gif_softc *sc;
	u_int options;
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
		if (ifr->ifr_mtu < GIF_MTU_MIN ||
		    ifr->ifr_mtu > GIF_MTU_MAX)
			return (EINVAL);
		else
			ifp->if_mtu = ifr->ifr_mtu;
		return (0);
	}
	sx_xlock(&gif_ioctl_sx);
	sc = ifp->if_softc;
	if (sc == NULL) {
		error = ENXIO;
		goto bad;
	}
	error = 0;
	switch (cmd) {
	case SIOCDIFPHYADDR:
		if (sc->gif_family == 0)
			break;
		gif_delete_tunnel(sc);
		break;
#ifdef INET
	case SIOCSIFPHYADDR:
	case SIOCGIFPSRCADDR:
	case SIOCGIFPDSTADDR:
		error = in_gif_ioctl(sc, cmd, data);
		break;
#endif
#ifdef INET6
	case SIOCSIFPHYADDR_IN6:
	case SIOCGIFPSRCADDR_IN6:
	case SIOCGIFPDSTADDR_IN6:
		error = in6_gif_ioctl(sc, cmd, data);
		break;
#endif
	case SIOCGTUNFIB:
		ifr->ifr_fib = sc->gif_fibnum;
		break;
	case SIOCSTUNFIB:
		if ((error = priv_check(curthread, PRIV_NET_GIF)) != 0)
			break;
		if (ifr->ifr_fib >= rt_numfibs)
			error = EINVAL;
		else
			sc->gif_fibnum = ifr->ifr_fib;
		break;
	case GIFGOPTS:
		options = sc->gif_options;
		error = copyout(&options, ifr_data_get_ptr(ifr),
		    sizeof(options));
		break;
	case GIFSOPTS:
		if ((error = priv_check(curthread, PRIV_NET_GIF)) != 0)
			break;
		error = copyin(ifr_data_get_ptr(ifr), &options,
		    sizeof(options));
		if (error)
			break;
		if (options & ~GIF_OPTMASK) {
			error = EINVAL;
			break;
		}
		if (sc->gif_options != options) {
			switch (sc->gif_family) {
#ifdef INET
			case AF_INET:
				error = in_gif_setopts(sc, options);
				break;
#endif
#ifdef INET6
			case AF_INET6:
				error = in6_gif_setopts(sc, options);
				break;
#endif
			default:
				/* No need to invoke AF-handler */
				sc->gif_options = options;
			}
		}
		break;
	default:
		error = EINVAL;
		break;
	}
	if (error == 0 && sc->gif_family != 0) {
		if (
#ifdef INET
		    cmd == SIOCSIFPHYADDR ||
#endif
#ifdef INET6
		    cmd == SIOCSIFPHYADDR_IN6 ||
#endif
		    0) {
			if_link_state_change(ifp, LINK_STATE_UP);
		}
	}
bad:
	sx_xunlock(&gif_ioctl_sx);
	return (error);
}