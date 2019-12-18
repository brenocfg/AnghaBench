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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct in_addr {int dummy; } ;
struct sockaddr_in {struct in_addr sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct route {int ro_flags; } ;
struct mbuf {int m_flags; } ;
struct llentry {int dummy; } ;
struct ifnet {int /*<<< orphan*/ * if_broadcastaddr; } ;
struct ether_header {int /*<<< orphan*/ * ether_shost; int /*<<< orphan*/  ether_type; int /*<<< orphan*/ * ether_dhost; } ;
typedef  int /*<<< orphan*/  etype ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EAFNOSUPPORT ; 
 int EHOSTDOWN ; 
 int EHOSTUNREACH ; 
 int /*<<< orphan*/  ETHERTYPE_IP ; 
 int /*<<< orphan*/  ETHERTYPE_IPV6 ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  ETHER_MAP_IPV6_MULTICAST (struct in6_addr const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ETHER_MAP_IP_MULTICAST (struct in_addr const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IF_LLADDR (struct ifnet*) ; 
 int LLE_IFADDR ; 
 int M_BCAST ; 
 int M_MCAST ; 
 int RT_HAS_GW ; 
 int RT_L2_ME ; 
 int RT_MAY_LOOP ; 
 int arpresolve (struct ifnet*,int /*<<< orphan*/ ,struct mbuf*,struct sockaddr const*,int /*<<< orphan*/ *,int*,struct llentry**) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int nd6_resolve (struct ifnet*,int /*<<< orphan*/ ,struct mbuf*,struct sockaddr const*,int /*<<< orphan*/ *,int*,struct llentry**) ; 

__attribute__((used)) static int
ether_resolve_addr(struct ifnet *ifp, struct mbuf *m,
	const struct sockaddr *dst, struct route *ro, u_char *phdr,
	uint32_t *pflags, struct llentry **plle)
{
	struct ether_header *eh;
	uint32_t lleflags = 0;
	int error = 0;
#if defined(INET) || defined(INET6)
	uint16_t etype;
#endif

	if (plle)
		*plle = NULL;
	eh = (struct ether_header *)phdr;

	switch (dst->sa_family) {
#ifdef INET
	case AF_INET:
		if ((m->m_flags & (M_BCAST | M_MCAST)) == 0)
			error = arpresolve(ifp, 0, m, dst, phdr, &lleflags,
			    plle);
		else {
			if (m->m_flags & M_BCAST)
				memcpy(eh->ether_dhost, ifp->if_broadcastaddr,
				    ETHER_ADDR_LEN);
			else {
				const struct in_addr *a;
				a = &(((const struct sockaddr_in *)dst)->sin_addr);
				ETHER_MAP_IP_MULTICAST(a, eh->ether_dhost);
			}
			etype = htons(ETHERTYPE_IP);
			memcpy(&eh->ether_type, &etype, sizeof(etype));
			memcpy(eh->ether_shost, IF_LLADDR(ifp), ETHER_ADDR_LEN);
		}
		break;
#endif
#ifdef INET6
	case AF_INET6:
		if ((m->m_flags & M_MCAST) == 0)
			error = nd6_resolve(ifp, 0, m, dst, phdr, &lleflags,
			    plle);
		else {
			const struct in6_addr *a6;
			a6 = &(((const struct sockaddr_in6 *)dst)->sin6_addr);
			ETHER_MAP_IPV6_MULTICAST(a6, eh->ether_dhost);
			etype = htons(ETHERTYPE_IPV6);
			memcpy(&eh->ether_type, &etype, sizeof(etype));
			memcpy(eh->ether_shost, IF_LLADDR(ifp), ETHER_ADDR_LEN);
		}
		break;
#endif
	default:
		if_printf(ifp, "can't handle af%d\n", dst->sa_family);
		if (m != NULL)
			m_freem(m);
		return (EAFNOSUPPORT);
	}

	if (error == EHOSTDOWN) {
		if (ro != NULL && (ro->ro_flags & RT_HAS_GW) != 0)
			error = EHOSTUNREACH;
	}

	if (error != 0)
		return (error);

	*pflags = RT_MAY_LOOP;
	if (lleflags & LLE_IFADDR)
		*pflags |= RT_L2_ME;

	return (0);
}