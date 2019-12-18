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
typedef  int u_long ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {void* sin_family; int sin_len; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct ip {TYPE_1__ ip_dst; TYPE_1__ ip_src; } ;
struct in_aliasreq {struct sockaddr_in ifra_dstaddr; struct sockaddr_in ifra_addr; } ;
struct ifreq {int /*<<< orphan*/  ifr_addr; } ;
struct gif_softc {void* gif_family; struct ip* gif_iphdr; int /*<<< orphan*/  gif_hdr; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  CK_LIST_REMOVE (struct gif_softc*,int /*<<< orphan*/ ) ; 
 int EADDRNOTAVAIL ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  GIF_WAIT () ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  M_GIF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
#define  SIOCGIFPDSTADDR 130 
#define  SIOCGIFPSRCADDR 129 
#define  SIOCSIFPHYADDR 128 
 int /*<<< orphan*/ * V_ipv4_hashtbl ; 
 void* V_ipv4_srchashtbl ; 
 int /*<<< orphan*/  chain ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* gif_hashinit () ; 
 int /*<<< orphan*/  in_gif_attach (struct gif_softc*) ; 
 int in_gif_checkdup (struct gif_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_gif_set_running (struct gif_softc*) ; 
 struct ip* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int prison_if (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  srchash ; 

int
in_gif_ioctl(struct gif_softc *sc, u_long cmd, caddr_t data)
{
	struct ifreq *ifr = (struct ifreq *)data;
	struct sockaddr_in *dst, *src;
	struct ip *ip;
	int error;

	/* NOTE: we are protected with gif_ioctl_sx lock */
	error = EINVAL;
	switch (cmd) {
	case SIOCSIFPHYADDR:
		src = &((struct in_aliasreq *)data)->ifra_addr;
		dst = &((struct in_aliasreq *)data)->ifra_dstaddr;

		/* sanity checks */
		if (src->sin_family != dst->sin_family ||
		    src->sin_family != AF_INET ||
		    src->sin_len != dst->sin_len ||
		    src->sin_len != sizeof(*src))
			break;
		if (src->sin_addr.s_addr == INADDR_ANY ||
		    dst->sin_addr.s_addr == INADDR_ANY) {
			error = EADDRNOTAVAIL;
			break;
		}
		if (V_ipv4_hashtbl == NULL) {
			V_ipv4_hashtbl = gif_hashinit();
			V_ipv4_srchashtbl = gif_hashinit();
		}
		error = in_gif_checkdup(sc, src->sin_addr.s_addr,
		    dst->sin_addr.s_addr);
		if (error == EADDRNOTAVAIL)
			break;
		if (error == EEXIST) {
			/* Addresses are the same. Just return. */
			error = 0;
			break;
		}
		ip = malloc(sizeof(*ip), M_GIF, M_WAITOK | M_ZERO);
		ip->ip_src.s_addr = src->sin_addr.s_addr;
		ip->ip_dst.s_addr = dst->sin_addr.s_addr;
		if (sc->gif_family != 0) {
			/* Detach existing tunnel first */
			CK_LIST_REMOVE(sc, srchash);
			CK_LIST_REMOVE(sc, chain);
			GIF_WAIT();
			free(sc->gif_hdr, M_GIF);
			/* XXX: should we notify about link state change? */
		}
		sc->gif_family = AF_INET;
		sc->gif_iphdr = ip;
		in_gif_attach(sc);
		in_gif_set_running(sc);
		break;
	case SIOCGIFPSRCADDR:
	case SIOCGIFPDSTADDR:
		if (sc->gif_family != AF_INET) {
			error = EADDRNOTAVAIL;
			break;
		}
		src = (struct sockaddr_in *)&ifr->ifr_addr;
		memset(src, 0, sizeof(*src));
		src->sin_family = AF_INET;
		src->sin_len = sizeof(*src);
		src->sin_addr = (cmd == SIOCGIFPSRCADDR) ?
		    sc->gif_iphdr->ip_src: sc->gif_iphdr->ip_dst;
		error = prison_if(curthread->td_ucred, (struct sockaddr *)src);
		if (error != 0)
			memset(src, 0, sizeof(*src));
		break;
	}
	return (error);
}