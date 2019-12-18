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
struct rtnl_neigh {int dummy; } ;
struct nl_addr {int dummy; } ;
struct get_neigh_handler {int /*<<< orphan*/  dst; int /*<<< orphan*/  oif; int /*<<< orphan*/  neigh_cache; } ;

/* Variables and functions */
 struct nl_addr* nl_addr_clone (struct nl_addr*) ; 
 struct rtnl_neigh* rtnl_neigh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nl_addr* rtnl_neigh_get_lladdr (struct rtnl_neigh*) ; 
 int /*<<< orphan*/  rtnl_neigh_put (struct rtnl_neigh*) ; 

__attribute__((used)) static struct nl_addr *get_neigh_mac(struct get_neigh_handler *neigh_handler)
{
	struct rtnl_neigh *neigh;
	struct nl_addr *ll_addr = NULL;

	/* future optimization - if link local address - parse address and
	 * return mac now instead of doing so after the routing CB. This
	 * is of course referred to GIDs */
	neigh = rtnl_neigh_get(neigh_handler->neigh_cache,
			       neigh_handler->oif,
			       neigh_handler->dst);
	if (neigh == NULL)
		return NULL;

	ll_addr = rtnl_neigh_get_lladdr(neigh);
	if (NULL != ll_addr)
		ll_addr = nl_addr_clone(ll_addr);

	rtnl_neigh_put(neigh);
	return ll_addr;
}