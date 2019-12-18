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
struct rtentry {scalar_t__ rt_expire; int /*<<< orphan*/  rt_pksent; int /*<<< orphan*/  rt_weight; int /*<<< orphan*/  rt_mtu; } ;
struct rt_metrics {scalar_t__ rmx_expire; int /*<<< orphan*/  rmx_pksent; int /*<<< orphan*/  rmx_weight; int /*<<< orphan*/  rmx_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct rt_metrics*,int) ; 
 int /*<<< orphan*/  counter_u64_fetch (int /*<<< orphan*/ ) ; 
 scalar_t__ time_second ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static void
rt_getmetrics(const struct rtentry *rt, struct rt_metrics *out)
{

	bzero(out, sizeof(*out));
	out->rmx_mtu = rt->rt_mtu;
	out->rmx_weight = rt->rt_weight;
	out->rmx_pksent = counter_u64_fetch(rt->rt_pksent);
	/* Kernel -> userland timebase conversion. */
	out->rmx_expire = rt->rt_expire ?
	    rt->rt_expire - time_uptime + time_second : 0;
}