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
struct rtnl_route {int dummy; } ;
struct rtnl_nexthop {int dummy; } ;
struct rtnl_link {int dummy; } ;
struct nl_object {int dummy; } ;
struct nl_addr {int dummy; } ;
struct get_neigh_handler {int oif; int /*<<< orphan*/ * src; void* found_ll_addr; int /*<<< orphan*/ * dst; int /*<<< orphan*/  link_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETUNREACH ; 
 int RTN_BLACKHOLE ; 
 int RTN_LOCAL ; 
 int RTN_PROHIBIT ; 
 int RTN_THROW ; 
 int RTN_UNREACHABLE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  handle_encoded_mac (int /*<<< orphan*/ *,void**) ; 
 void* nl_addr_clone (struct nl_addr*) ; 
 int /*<<< orphan*/  nl_addr_put (int /*<<< orphan*/ *) ; 
 struct rtnl_link* rtnl_link_get (int /*<<< orphan*/ ,int) ; 
 struct nl_addr* rtnl_link_get_addr (struct rtnl_link*) ; 
 int /*<<< orphan*/  rtnl_link_put (struct rtnl_link*) ; 
 struct nl_addr* rtnl_route_get_pref_src (struct rtnl_route*) ; 
 int rtnl_route_get_type (struct rtnl_route*) ; 
 struct rtnl_nexthop* rtnl_route_nexthop_n (struct rtnl_route*,int /*<<< orphan*/ ) ; 
 struct nl_addr* rtnl_route_nh_get_gateway (struct rtnl_nexthop*) ; 
 int rtnl_route_nh_get_ifindex (struct rtnl_nexthop*) ; 

__attribute__((used)) static void get_route_cb_parser(struct nl_object *obj, void *arg)
{
	struct get_neigh_handler *neigh_handler =
		(struct get_neigh_handler *)arg;

	struct rtnl_route *route = (struct rtnl_route *)obj;
	struct nl_addr *gateway = NULL;
	struct nl_addr *src = rtnl_route_get_pref_src(route);
	int oif;
	int type = rtnl_route_get_type(route);
	struct rtnl_link *link;

	struct rtnl_nexthop *nh = rtnl_route_nexthop_n(route, 0);

	if (nh != NULL)
		gateway = rtnl_route_nh_get_gateway(nh);
	oif = rtnl_route_nh_get_ifindex(nh);

	if (gateway) {
		nl_addr_put(neigh_handler->dst);
		neigh_handler->dst = nl_addr_clone(gateway);
	}

	if (RTN_BLACKHOLE == type ||
	    RTN_UNREACHABLE == type ||
	    RTN_PROHIBIT == type ||
	    RTN_THROW == type) {
		errno = ENETUNREACH;
		goto err;
	}

	if (!neigh_handler->src && src)
		neigh_handler->src = nl_addr_clone(src);

	if (neigh_handler->oif < 0 && oif > 0)
		neigh_handler->oif = oif;

	/* Link Local */
	if (RTN_LOCAL == type) {
		struct nl_addr *lladdr;

		link = rtnl_link_get(neigh_handler->link_cache,
				     neigh_handler->oif);

		if (link == NULL)
			goto err;

		lladdr = rtnl_link_get_addr(link);

		if (lladdr == NULL)
			goto err_link;

		neigh_handler->found_ll_addr = nl_addr_clone(lladdr);
		rtnl_link_put(link);
	} else {
		handle_encoded_mac(
			neigh_handler->dst,
			&neigh_handler->found_ll_addr);
	}

	return;

err_link:
	rtnl_link_put(link);
err:
	if (neigh_handler->src) {
		nl_addr_put(neigh_handler->src);
		neigh_handler->src = NULL;
	}
}