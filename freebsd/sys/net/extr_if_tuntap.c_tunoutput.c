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
typedef  int u_short ;
typedef  scalar_t__ u_int32_t ;
struct tuntap_softc {int tun_flags; } ;
struct sockaddr {scalar_t__ sa_family; int sa_len; struct sockaddr const* sa_data; } ;
struct route {int dummy; } ;
struct mbuf {scalar_t__* m_data; } ;
struct ifnet {int if_flags; int (* if_transmit ) (struct ifnet*,struct mbuf*) ;int /*<<< orphan*/  if_bpf; struct tuntap_softc* if_softc; } ;
typedef  int /*<<< orphan*/  af ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_UNSPEC ; 
 int EAFNOSUPPORT ; 
 int EHOSTDOWN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int IFF_UP ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PREPEND (struct mbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TUNDEBUG (struct ifnet*,char*,...) ; 
 int TUN_IFHEAD ; 
 int TUN_LMODE ; 
 int /*<<< orphan*/  TUN_LOCK (struct tuntap_softc*) ; 
 int TUN_READY ; 
 int /*<<< orphan*/  TUN_UNLOCK (struct tuntap_softc*) ; 
 int /*<<< orphan*/  bcopy (struct sockaddr const*,scalar_t__*,int) ; 
 int /*<<< orphan*/  bpf_mtap2 (int /*<<< orphan*/ ,scalar_t__*,int,struct mbuf*) ; 
 scalar_t__ bpf_peers_present (int /*<<< orphan*/ ) ; 
 scalar_t__ htonl (scalar_t__) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int mac_ifnet_check_transmit (struct ifnet*,struct mbuf*) ; 
 int stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static int
tunoutput(struct ifnet *ifp, struct mbuf *m0, const struct sockaddr *dst,
    struct route *ro)
{
	struct tuntap_softc *tp = ifp->if_softc;
	u_short cached_tun_flags;
	int error;
	u_int32_t af;

	TUNDEBUG (ifp, "tunoutput\n");

#ifdef MAC
	error = mac_ifnet_check_transmit(ifp, m0);
	if (error) {
		m_freem(m0);
		return (error);
	}
#endif

	/* Could be unlocked read? */
	TUN_LOCK(tp);
	cached_tun_flags = tp->tun_flags;
	TUN_UNLOCK(tp);
	if ((cached_tun_flags & TUN_READY) != TUN_READY) {
		TUNDEBUG (ifp, "not ready 0%o\n", tp->tun_flags);
		m_freem (m0);
		return (EHOSTDOWN);
	}

	if ((ifp->if_flags & IFF_UP) != IFF_UP) {
		m_freem (m0);
		return (EHOSTDOWN);
	}

	/* BPF writes need to be handled specially. */
	if (dst->sa_family == AF_UNSPEC)
		bcopy(dst->sa_data, &af, sizeof(af));
	else
		af = dst->sa_family;

	if (bpf_peers_present(ifp->if_bpf))
		bpf_mtap2(ifp->if_bpf, &af, sizeof(af), m0);

	/* prepend sockaddr? this may abort if the mbuf allocation fails */
	if (cached_tun_flags & TUN_LMODE) {
		/* allocate space for sockaddr */
		M_PREPEND(m0, dst->sa_len, M_NOWAIT);

		/* if allocation failed drop packet */
		if (m0 == NULL) {
			if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
			return (ENOBUFS);
		} else {
			bcopy(dst, m0->m_data, dst->sa_len);
		}
	}

	if (cached_tun_flags & TUN_IFHEAD) {
		/* Prepend the address family */
		M_PREPEND(m0, 4, M_NOWAIT);

		/* if allocation failed drop packet */
		if (m0 == NULL) {
			if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
			return (ENOBUFS);
		} else
			*(u_int32_t *)m0->m_data = htonl(af);
	} else {
#ifdef INET
		if (af != AF_INET)
#endif
		{
			m_freem(m0);
			return (EAFNOSUPPORT);
		}
	}

	error = (ifp->if_transmit)(ifp, m0);
	if (error)
		return (ENOBUFS);
	if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
	return (0);
}