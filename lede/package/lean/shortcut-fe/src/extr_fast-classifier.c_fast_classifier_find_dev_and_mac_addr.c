#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rtable {int dummy; } ;
struct rt6_info {int dummy; } ;
struct net_device {scalar_t__ addr_len; } ;
struct neighbour {int nud_state; int /*<<< orphan*/  ha; struct net_device* dev; } ;
struct in6_addr {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_5__ {scalar_t__ ip6; int /*<<< orphan*/  ip; } ;
typedef  TYPE_1__ sfe_ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TRACE (char*,TYPE_1__*) ; 
 int IS_ERR (struct rtable*) ; 
 int NUD_VALID ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct neighbour* dst_neigh_lookup (struct dst_entry*,TYPE_1__*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  init_net ; 
 struct rtable* ip_route_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct rt6_info* rt6_lookup (int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool fast_classifier_find_dev_and_mac_addr(sfe_ip_addr_t *addr, struct net_device **dev, u8 *mac_addr, bool is_v4)
{
	struct neighbour *neigh;
	struct rtable *rt;
	struct rt6_info *rt6;
	struct dst_entry *dst;
	struct net_device *mac_dev;

	/*
	 * Look up the rtable entry for the IP address then get the hardware
	 * address from its neighbour structure.  This means this works when the
	 * neighbours are routers too.
	 */
	if (is_v4) {
		rt = ip_route_output(&init_net, addr->ip, 0, 0, 0);
		if (unlikely(IS_ERR(rt))) {
			goto ret_fail;
		}

		dst = (struct dst_entry *)rt;
	} else {
		rt6 = rt6_lookup(&init_net, (struct in6_addr *)addr->ip6, 0, 0, 0);
		if (!rt6) {
			goto ret_fail;
		}

		dst = (struct dst_entry *)rt6;
	}

	rcu_read_lock();
	neigh = dst_neigh_lookup(dst, addr);
	if (unlikely(!neigh)) {
		rcu_read_unlock();
		dst_release(dst);
		goto ret_fail;
	}

	if (unlikely(!(neigh->nud_state & NUD_VALID))) {
		rcu_read_unlock();
		neigh_release(neigh);
		dst_release(dst);
		goto ret_fail;
	}

	mac_dev = neigh->dev;
	if (!mac_dev) {
		rcu_read_unlock();
		neigh_release(neigh);
		dst_release(dst);
		goto ret_fail;
	}

	memcpy(mac_addr, neigh->ha, (size_t)mac_dev->addr_len);

	dev_hold(mac_dev);
	*dev = mac_dev;
	rcu_read_unlock();
	neigh_release(neigh);
	dst_release(dst);

	return true;

ret_fail:
	DEBUG_TRACE("failed to find MAC address for IP: %pIS\n", addr);

	return false;
}