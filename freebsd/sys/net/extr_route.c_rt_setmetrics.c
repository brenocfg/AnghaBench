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
struct rtentry {scalar_t__ rt_mtu; scalar_t__ rt_expire; int /*<<< orphan*/  rt_weight; int /*<<< orphan*/  rt_flags; } ;
struct rt_addrinfo {int rti_mflags; TYPE_1__* rti_rmx; } ;
struct TYPE_2__ {scalar_t__ rmx_mtu; scalar_t__ rmx_expire; int /*<<< orphan*/  rmx_weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTF_FIXEDMTU ; 
 int RTV_EXPIRE ; 
 int RTV_MTU ; 
 int RTV_WEIGHT ; 
 scalar_t__ time_second ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static void
rt_setmetrics(const struct rt_addrinfo *info, struct rtentry *rt)
{

	if (info->rti_mflags & RTV_MTU) {
		if (info->rti_rmx->rmx_mtu != 0) {

			/*
			 * MTU was explicitly provided by user.
			 * Keep it.
			 */
			rt->rt_flags |= RTF_FIXEDMTU;
		} else {

			/*
			 * User explicitly sets MTU to 0.
			 * Assume rollback to default.
			 */
			rt->rt_flags &= ~RTF_FIXEDMTU;
		}
		rt->rt_mtu = info->rti_rmx->rmx_mtu;
	}
	if (info->rti_mflags & RTV_WEIGHT)
		rt->rt_weight = info->rti_rmx->rmx_weight;
	/* Kernel -> userland timebase conversion. */
	if (info->rti_mflags & RTV_EXPIRE)
		rt->rt_expire = info->rti_rmx->rmx_expire ?
		    info->rti_rmx->rmx_expire - time_second + time_uptime : 0;
}