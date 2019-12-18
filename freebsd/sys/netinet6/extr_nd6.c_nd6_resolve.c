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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {int dummy; } ;
struct mbuf {int m_flags; } ;
struct llentry {int r_flags; scalar_t__ r_skip_req; int /*<<< orphan*/  lle_hittime; int /*<<< orphan*/  r_hdrlen; int /*<<< orphan*/  r_linkdata; } ;
struct ifnet {int if_type; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  ETHER_MAP_IPV6_MULTICAST (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  IFT_BRIDGE 130 
#define  IFT_ETHER 129 
#define  IFT_L2VLAN 128 
 int /*<<< orphan*/  LLE_ADDREF (struct llentry*) ; 
 int /*<<< orphan*/  LLE_EXCLUSIVE ; 
 int /*<<< orphan*/  LLE_REQ_LOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLE_REQ_UNLOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLE_UNLOCKED ; 
 int LLE_VALID ; 
 int /*<<< orphan*/  LLE_WUNLOCK (struct llentry*) ; 
 int M_MCAST ; 
 int ND6_IFF_IFDISABLED ; 
 TYPE_1__* ND_IFINFO (struct ifnet*) ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 int RLLE_IFADDR ; 
 int RLLE_VALID ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct llentry* nd6_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ifnet*) ; 
 int nd6_resolve_slow (struct ifnet*,int /*<<< orphan*/ ,struct mbuf*,struct sockaddr_in6 const*,int /*<<< orphan*/ *,int*,struct llentry**) ; 
 int /*<<< orphan*/  time_uptime ; 

int
nd6_resolve(struct ifnet *ifp, int is_gw, struct mbuf *m,
    const struct sockaddr *sa_dst, u_char *desten, uint32_t *pflags,
    struct llentry **plle)
{
	struct llentry *ln = NULL;
	const struct sockaddr_in6 *dst6;

	NET_EPOCH_ASSERT();

	if (pflags != NULL)
		*pflags = 0;

	dst6 = (const struct sockaddr_in6 *)sa_dst;

	/* discard the packet if IPv6 operation is disabled on the interface */
	if ((ND_IFINFO(ifp)->flags & ND6_IFF_IFDISABLED)) {
		m_freem(m);
		return (ENETDOWN); /* better error? */
	}

	if (m != NULL && m->m_flags & M_MCAST) {
		switch (ifp->if_type) {
		case IFT_ETHER:
		case IFT_L2VLAN:
		case IFT_BRIDGE:
			ETHER_MAP_IPV6_MULTICAST(&dst6->sin6_addr,
						 desten);
			return (0);
		default:
			m_freem(m);
			return (EAFNOSUPPORT);
		}
	}

	ln = nd6_lookup(&dst6->sin6_addr, plle ? LLE_EXCLUSIVE : LLE_UNLOCKED,
	    ifp);
	if (ln != NULL && (ln->r_flags & RLLE_VALID) != 0) {
		/* Entry found, let's copy lle info */
		bcopy(ln->r_linkdata, desten, ln->r_hdrlen);
		if (pflags != NULL)
			*pflags = LLE_VALID | (ln->r_flags & RLLE_IFADDR);
		/* Check if we have feedback request from nd6 timer */
		if (ln->r_skip_req != 0) {
			LLE_REQ_LOCK(ln);
			ln->r_skip_req = 0; /* Notify that entry was used */
			ln->lle_hittime = time_uptime;
			LLE_REQ_UNLOCK(ln);
		}
		if (plle) {
			LLE_ADDREF(ln);
			*plle = ln;
			LLE_WUNLOCK(ln);
		}
		return (0);
	} else if (plle && ln)
		LLE_WUNLOCK(ln);

	return (nd6_resolve_slow(ifp, 0, m, dst6, desten, pflags, plle));
}