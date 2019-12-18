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
typedef  int u_int32_t ;
struct scope6_id {int* s6id_list; } ;
struct in6_addr {int /*<<< orphan*/ * s6_addr16; } ;
struct ifnet {int if_flags; int if_index; } ;
struct epoch_tracker {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFF_LOOPBACK ; 
 scalar_t__ IN6_IS_ADDR_LOOPBACK (struct in6_addr*) ; 
 int IPV6_ADDR_SCOPE_GLOBAL ; 
 int IPV6_ADDR_SCOPE_INTFACELOCAL ; 
 int IPV6_ADDR_SCOPE_LINKLOCAL ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 struct scope6_id* SID (struct ifnet*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int in6_addrscope (struct in6_addr*) ; 

int
in6_setscope(struct in6_addr *in6, struct ifnet *ifp, u_int32_t *ret_id)
{
	int scope;
	u_int32_t zoneid = 0;
	struct scope6_id *sid;

	/*
	 * special case: the loopback address can only belong to a loopback
	 * interface.
	 */
	if (IN6_IS_ADDR_LOOPBACK(in6)) {
		if (!(ifp->if_flags & IFF_LOOPBACK))
			return (EINVAL);
	} else {
		scope = in6_addrscope(in6);
		if (scope == IPV6_ADDR_SCOPE_INTFACELOCAL ||
		    scope == IPV6_ADDR_SCOPE_LINKLOCAL) {
			/*
			 * Currently we use interface indices as the
			 * zone IDs for interface-local and link-local
			 * scopes.
			 */
			zoneid = ifp->if_index;
			in6->s6_addr16[1] = htons(zoneid & 0xffff); /* XXX */
		} else if (scope != IPV6_ADDR_SCOPE_GLOBAL) {
			struct epoch_tracker et;

			NET_EPOCH_ENTER(et);
			sid = SID(ifp);
			zoneid = sid->s6id_list[scope];
			NET_EPOCH_EXIT(et);
		}
	}

	if (ret_id != NULL)
		*ret_id = zoneid;

	return (0);
}