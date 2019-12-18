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

/* Variables and functions */
 struct rtnl_neigh* rtnl_neigh_alloc () ; 
 int /*<<< orphan*/  rtnl_neigh_set_dst (struct rtnl_neigh*,struct nl_addr*) ; 
 int /*<<< orphan*/  rtnl_neigh_set_ifindex (struct rtnl_neigh*,int) ; 

__attribute__((used)) static struct rtnl_neigh *create_filter_neigh_for_dst(struct nl_addr *dst_addr,
						      int oif)
{
	struct rtnl_neigh *filter_neigh;

	filter_neigh = rtnl_neigh_alloc();
	if (filter_neigh == NULL)
		return NULL;

	rtnl_neigh_set_ifindex(filter_neigh, oif);
	rtnl_neigh_set_dst(filter_neigh, dst_addr);

	return filter_neigh;
}