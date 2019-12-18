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
typedef  int uint16_t ;
struct rtnl_link {int dummy; } ;
struct get_neigh_handler {int /*<<< orphan*/  oif; int /*<<< orphan*/  link_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 struct rtnl_link* rtnl_link_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtnl_link_is_vlan (struct rtnl_link*) ; 
 int /*<<< orphan*/  rtnl_link_put (struct rtnl_link*) ; 
 int rtnl_link_vlan_get_id (struct rtnl_link*) ; 

uint16_t neigh_get_vlan_id_from_dev(struct get_neigh_handler *neigh_handler)
{
	struct rtnl_link *link;
	int vid = 0xffff;

	link = rtnl_link_get(neigh_handler->link_cache, neigh_handler->oif);
	if (link == NULL) {
		errno = EINVAL;
		return vid;
	}

	if (rtnl_link_is_vlan(link))
		vid = rtnl_link_vlan_get_id(link);
	rtnl_link_put(link);
	return vid >= 0 && vid <= 0xfff ? vid : 0xffff;
}