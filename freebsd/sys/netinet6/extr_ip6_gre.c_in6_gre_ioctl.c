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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_long ;
struct sockaddr_in6 {void* sin6_family; int sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {int dummy; } ;
struct ip6_hdr {int /*<<< orphan*/  ip6_dst; int /*<<< orphan*/  ip6_src; } ;
struct in6_ifreq {int /*<<< orphan*/  ifr_addr; } ;
struct in6_aliasreq {struct sockaddr_in6 ifra_dstaddr; struct sockaddr_in6 ifra_addr; } ;
struct greudp6 {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ip6_dst; int /*<<< orphan*/  ip6_src; } ;
struct gre_softc {void* gre_family; TYPE_1__ gre_oip6; struct ip6_hdr* gre_hdr; int /*<<< orphan*/  gre_iseq; int /*<<< orphan*/  gre_oseq; int /*<<< orphan*/  gre_options; } ;
struct gre_sockets {int dummy; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 void* AF_INET6 ; 
 int /*<<< orphan*/  CK_LIST_REMOVE (struct gre_softc*,int /*<<< orphan*/ ) ; 
 int EADDRNOTAVAIL ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  GRE_WAIT () ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_GRE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
#define  SIOCGIFPDSTADDR_IN6 130 
#define  SIOCGIFPSRCADDR_IN6 129 
#define  SIOCSIFPHYADDR_IN6 128 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/ * V_ipv6_hashtbl ; 
 struct gre_sockets* V_ipv6_sockets ; 
 void* V_ipv6_srchashtbl ; 
 int /*<<< orphan*/  chain ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  free (struct ip6_hdr*,int /*<<< orphan*/ ) ; 
 void* gre_hashinit () ; 
 int in6_gre_attach (struct gre_softc*) ; 
 int in6_gre_checkdup (struct gre_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ip6_hdr* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int prison_if (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int sa6_embedscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 int sa6_recoverscope (struct sockaddr_in6*) ; 
 int /*<<< orphan*/  srchash ; 

int
in6_gre_ioctl(struct gre_softc *sc, u_long cmd, caddr_t data)
{
	struct in6_ifreq *ifr = (struct in6_ifreq *)data;
	struct sockaddr_in6 *dst, *src;
	struct ip6_hdr *ip6;
	int error;

	/* NOTE: we are protected with gre_ioctl_sx lock */
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
			V_ipv6_hashtbl = gre_hashinit();
			V_ipv6_srchashtbl = gre_hashinit();
			V_ipv6_sockets = (struct gre_sockets *)gre_hashinit();
		}
		error = in6_gre_checkdup(sc, &src->sin6_addr,
		    &dst->sin6_addr, sc->gre_options);
		if (error == EADDRNOTAVAIL)
			break;
		if (error == EEXIST) {
			/* Addresses are the same. Just return. */
			error = 0;
			break;
		}
		ip6 = malloc(sizeof(struct greudp6) + 3 * sizeof(uint32_t),
		    M_GRE, M_WAITOK | M_ZERO);
		ip6->ip6_src = src->sin6_addr;
		ip6->ip6_dst = dst->sin6_addr;
		if (sc->gre_family != 0) {
			/* Detach existing tunnel first */
			CK_LIST_REMOVE(sc, chain);
			CK_LIST_REMOVE(sc, srchash);
			GRE_WAIT();
			free(sc->gre_hdr, M_GRE);
			/* XXX: should we notify about link state change? */
		}
		sc->gre_family = AF_INET6;
		sc->gre_hdr = ip6;
		sc->gre_oseq = 0;
		sc->gre_iseq = UINT32_MAX;
		error = in6_gre_attach(sc);
		if (error != 0) {
			sc->gre_family = 0;
			free(sc->gre_hdr, M_GRE);
		}
		break;
	case SIOCGIFPSRCADDR_IN6:
	case SIOCGIFPDSTADDR_IN6:
		if (sc->gre_family != AF_INET6) {
			error = EADDRNOTAVAIL;
			break;
		}
		src = (struct sockaddr_in6 *)&ifr->ifr_addr;
		memset(src, 0, sizeof(*src));
		src->sin6_family = AF_INET6;
		src->sin6_len = sizeof(*src);
		src->sin6_addr = (cmd == SIOCGIFPSRCADDR_IN6) ?
		    sc->gre_oip6.ip6_src: sc->gre_oip6.ip6_dst;
		error = prison_if(curthread->td_ucred, (struct sockaddr *)src);
		if (error == 0)
			error = sa6_recoverscope(src);
		if (error != 0)
			memset(src, 0, sizeof(*src));
		break;
	}
	return (error);
}