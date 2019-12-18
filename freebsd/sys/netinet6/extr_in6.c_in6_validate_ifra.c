#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {scalar_t__ sin6_family; scalar_t__ sin6_scope_id; struct in6_addr sin6_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_7__ {scalar_t__ sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct in6_ifaddr {TYPE_4__ ia_addr; TYPE_3__ ia_prefixmask; } ;
struct TYPE_6__ {int sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_5__ {int sin6_len; scalar_t__ sin6_family; int /*<<< orphan*/  sin6_addr; } ;
struct in6_addrlifetime {scalar_t__ ia6t_pltime; scalar_t__ ia6t_vltime; } ;
struct in6_aliasreq {TYPE_2__ ifra_prefixmask; TYPE_1__ ifra_addr; struct in6_addrlifetime ifra_lifetime; struct sockaddr_in6 ifra_dstaddr; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int IFF_LOOPBACK ; 
 int IFF_POINTOPOINT ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int in6_mask2len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ in6_setscope (struct in6_addr*,struct ifnet*,scalar_t__*) ; 
 int /*<<< orphan*/  ip6_sprintf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 
 scalar_t__ sa6_embedscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
in6_validate_ifra(struct ifnet *ifp, struct in6_aliasreq *ifra,
    struct in6_ifaddr *ia, int flags)
{
	int plen = -1;
	struct sockaddr_in6 dst6;
	struct in6_addrlifetime *lt;
	char ip6buf[INET6_ADDRSTRLEN];

	/* Validate parameters */
	if (ifp == NULL || ifra == NULL) /* this maybe redundant */
		return (EINVAL);

	/*
	 * The destination address for a p2p link must have a family
	 * of AF_UNSPEC or AF_INET6.
	 */
	if ((ifp->if_flags & IFF_POINTOPOINT) != 0 &&
	    ifra->ifra_dstaddr.sin6_family != AF_INET6 &&
	    ifra->ifra_dstaddr.sin6_family != AF_UNSPEC)
		return (EAFNOSUPPORT);

	/*
	 * Validate address
	 */
	if (ifra->ifra_addr.sin6_len != sizeof(struct sockaddr_in6) ||
	    ifra->ifra_addr.sin6_family != AF_INET6)
		return (EINVAL);

	/*
	 * validate ifra_prefixmask.  don't check sin6_family, netmask
	 * does not carry fields other than sin6_len.
	 */
	if (ifra->ifra_prefixmask.sin6_len > sizeof(struct sockaddr_in6))
		return (EINVAL);
	/*
	 * Because the IPv6 address architecture is classless, we require
	 * users to specify a (non 0) prefix length (mask) for a new address.
	 * We also require the prefix (when specified) mask is valid, and thus
	 * reject a non-consecutive mask.
	 */
	if (ia == NULL && ifra->ifra_prefixmask.sin6_len == 0)
		return (EINVAL);
	if (ifra->ifra_prefixmask.sin6_len != 0) {
		plen = in6_mask2len(&ifra->ifra_prefixmask.sin6_addr,
		    (u_char *)&ifra->ifra_prefixmask +
		    ifra->ifra_prefixmask.sin6_len);
		if (plen <= 0)
			return (EINVAL);
	} else {
		/*
		 * In this case, ia must not be NULL.  We just use its prefix
		 * length.
		 */
		plen = in6_mask2len(&ia->ia_prefixmask.sin6_addr, NULL);
	}
	/*
	 * If the destination address on a p2p interface is specified,
	 * and the address is a scoped one, validate/set the scope
	 * zone identifier.
	 */
	dst6 = ifra->ifra_dstaddr;
	if ((ifp->if_flags & (IFF_POINTOPOINT|IFF_LOOPBACK)) != 0 &&
	    (dst6.sin6_family == AF_INET6)) {
		struct in6_addr in6_tmp;
		u_int32_t zoneid;

		in6_tmp = dst6.sin6_addr;
		if (in6_setscope(&in6_tmp, ifp, &zoneid))
			return (EINVAL); /* XXX: should be impossible */

		if (dst6.sin6_scope_id != 0) {
			if (dst6.sin6_scope_id != zoneid)
				return (EINVAL);
		} else		/* user omit to specify the ID. */
			dst6.sin6_scope_id = zoneid;

		/* convert into the internal form */
		if (sa6_embedscope(&dst6, 0))
			return (EINVAL); /* XXX: should be impossible */
	}
	/* Modify original ifra_dstaddr to reflect changes */
	ifra->ifra_dstaddr = dst6;

	/*
	 * The destination address can be specified only for a p2p or a
	 * loopback interface.  If specified, the corresponding prefix length
	 * must be 128.
	 */
	if (ifra->ifra_dstaddr.sin6_family == AF_INET6) {
		if ((ifp->if_flags & (IFF_POINTOPOINT|IFF_LOOPBACK)) == 0) {
			/* XXX: noisy message */
			nd6log((LOG_INFO, "in6_update_ifa: a destination can "
			    "be specified for a p2p or a loopback IF only\n"));
			return (EINVAL);
		}
		if (plen != 128) {
			nd6log((LOG_INFO, "in6_update_ifa: prefixlen should "
			    "be 128 when dstaddr is specified\n"));
			return (EINVAL);
		}
	}
	/* lifetime consistency check */
	lt = &ifra->ifra_lifetime;
	if (lt->ia6t_pltime > lt->ia6t_vltime)
		return (EINVAL);
	if (lt->ia6t_vltime == 0) {
		/*
		 * the following log might be noisy, but this is a typical
		 * configuration mistake or a tool's bug.
		 */
		nd6log((LOG_INFO,
		    "in6_update_ifa: valid lifetime is 0 for %s\n",
		    ip6_sprintf(ip6buf, &ifra->ifra_addr.sin6_addr)));

		if (ia == NULL)
			return (0); /* there's nothing to do */
	}

	/* Check prefix mask */
	if (ia != NULL && ifra->ifra_prefixmask.sin6_len != 0) {
		/*
		 * We prohibit changing the prefix length of an existing
		 * address, because
		 * + such an operation should be rare in IPv6, and
		 * + the operation would confuse prefix management.
		 */
		if (ia->ia_prefixmask.sin6_len != 0 &&
		    in6_mask2len(&ia->ia_prefixmask.sin6_addr, NULL) != plen) {
			nd6log((LOG_INFO, "in6_validate_ifa: the prefix length "
			    "of an existing %s address should not be changed\n",
			    ip6_sprintf(ip6buf, &ia->ia_addr.sin6_addr)));

			return (EINVAL);
		}
	}

	return (0);
}