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
struct sockaddr_in6 {void* sin6_family; int sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {int dummy; } ;
struct ip6_hdr {int /*<<< orphan*/  ip6_dst; int /*<<< orphan*/  ip6_src; int /*<<< orphan*/  ip6_vfc; } ;
struct in6_ifreq {int /*<<< orphan*/  ifr_addr; } ;
struct in6_aliasreq {struct sockaddr_in6 ifra_dstaddr; struct sockaddr_in6 ifra_addr; } ;
struct gif_softc {void* gif_family; struct ip6_hdr* gif_ip6hdr; int /*<<< orphan*/  gif_hdr; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 void* AF_INET6 ; 
 int /*<<< orphan*/  CK_LIST_REMOVE (struct gif_softc*,int /*<<< orphan*/ ) ; 
 int EADDRNOTAVAIL ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  GIF_WAIT () ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPV6_VERSION ; 
 int /*<<< orphan*/  M_GIF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
#define  SIOCGIFPDSTADDR_IN6 130 
#define  SIOCGIFPSRCADDR_IN6 129 
#define  SIOCSIFPHYADDR_IN6 128 
 int /*<<< orphan*/ * V_ipv6_hashtbl ; 
 void* V_ipv6_srchashtbl ; 
 int /*<<< orphan*/  chain ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* gif_hashinit () ; 
 int /*<<< orphan*/  in6_gif_attach (struct gif_softc*) ; 
 int in6_gif_checkdup (struct gif_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in6_gif_set_running (struct gif_softc*) ; 
 struct ip6_hdr* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int prison_if (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int sa6_embedscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 int sa6_recoverscope (struct sockaddr_in6*) ; 
 int /*<<< orphan*/  srchash ; 

int
in6_gif_ioctl(struct gif_softc *sc, u_long cmd, caddr_t data)
{
	struct in6_ifreq *ifr = (struct in6_ifreq *)data;
	struct sockaddr_in6 *dst, *src;
	struct ip6_hdr *ip6;
	int error;

	/* NOTE: we are protected with gif_ioctl_sx lock */
	error = EINVAL;
	switch (cmd) {
	case SIOCSIFPHYADDR_IN6:
		src = &((struct in6_aliasreq *)data)->ifra_addr;
		dst = &((struct in6_aliasreq *)data)->ifra_dstaddr;

		/* sanity checks */
		if (src->sin6_family != dst->sin6_family ||
		    src->sin6_family != AF_INET6 ||
		    src->sin6_len != dst->sin6_len ||
		    src->sin6_len != sizeof(*src))
			break;
		if (IN6_IS_ADDR_UNSPECIFIED(&src->sin6_addr) ||
		    IN6_IS_ADDR_UNSPECIFIED(&dst->sin6_addr)) {
			error = EADDRNOTAVAIL;
			break;
		}
		/*
		 * Check validity of the scope zone ID of the
		 * addresses, and convert it into the kernel
		 * internal form if necessary.
		 */
		if ((error = sa6_embedscope(src, 0)) != 0 ||
		    (error = sa6_embedscope(dst, 0)) != 0)
			break;

		if (V_ipv6_hashtbl == NULL) {
			V_ipv6_hashtbl = gif_hashinit();
			V_ipv6_srchashtbl = gif_hashinit();
		}
		error = in6_gif_checkdup(sc, &src->sin6_addr,
		    &dst->sin6_addr);
		if (error == EADDRNOTAVAIL)
			break;
		if (error == EEXIST) {
			/* Addresses are the same. Just return. */
			error = 0;
			break;
		}
		ip6 = malloc(sizeof(*ip6), M_GIF, M_WAITOK | M_ZERO);
		ip6->ip6_src = src->sin6_addr;
		ip6->ip6_dst = dst->sin6_addr;
		ip6->ip6_vfc = IPV6_VERSION;
		if (sc->gif_family != 0) {
			/* Detach existing tunnel first */
			CK_LIST_REMOVE(sc, srchash);
			CK_LIST_REMOVE(sc, chain);
			GIF_WAIT();
			free(sc->gif_hdr, M_GIF);
			/* XXX: should we notify about link state change? */
		}
		sc->gif_family = AF_INET6;
		sc->gif_ip6hdr = ip6;
		in6_gif_attach(sc);
		in6_gif_set_running(sc);
		break;
	case SIOCGIFPSRCADDR_IN6:
	case SIOCGIFPDSTADDR_IN6:
		if (sc->gif_family != AF_INET6) {
			error = EADDRNOTAVAIL;
			break;
		}
		src = (struct sockaddr_in6 *)&ifr->ifr_addr;
		memset(src, 0, sizeof(*src));
		src->sin6_family = AF_INET6;
		src->sin6_len = sizeof(*src);
		src->sin6_addr = (cmd == SIOCGIFPSRCADDR_IN6) ?
		    sc->gif_ip6hdr->ip6_src: sc->gif_ip6hdr->ip6_dst;
		error = prison_if(curthread->td_ucred, (struct sockaddr *)src);
		if (error == 0)
			error = sa6_recoverscope(src);
		if (error != 0)
			memset(src, 0, sizeof(*src));
		break;
	}
	return (error);
}