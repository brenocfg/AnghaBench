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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct rtentry {int rt_flags; scalar_t__ rt_ifp; } ;
struct route {struct rtentry* ro_rt; int /*<<< orphan*/  ro_dst; } ;
struct radix_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTFREE_LOCKED (struct rtentry*) ; 
 int RTF_UP ; 
 int /*<<< orphan*/  RT_ADDREF (struct rtentry*) ; 
 scalar_t__ RT_LINK_IS_UP (scalar_t__) ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/ * rn_mpath_next (struct radix_node*) ; 
 struct rtentry* rt_mpath_selectrte (struct rtentry*,int /*<<< orphan*/ ) ; 
 struct rtentry* rtalloc1_fib (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
rtalloc_mpath_fib(struct route *ro, uint32_t hash, u_int fibnum)
{
	struct rtentry *rt;

	/*
	 * XXX we don't attempt to lookup cached route again; what should
	 * be done for sendto(3) case?
	 */
	if (ro->ro_rt && ro->ro_rt->rt_ifp && (ro->ro_rt->rt_flags & RTF_UP)
	    && RT_LINK_IS_UP(ro->ro_rt->rt_ifp))
		return;				 
	ro->ro_rt = rtalloc1_fib(&ro->ro_dst, 1, 0, fibnum);

	/* if the route does not exist or it is not multipath, don't care */
	if (ro->ro_rt == NULL)
		return;
	if (rn_mpath_next((struct radix_node *)ro->ro_rt) == NULL) {
		RT_UNLOCK(ro->ro_rt);
		return;
	}

	rt = rt_mpath_selectrte(ro->ro_rt, hash);
	/* XXX try filling rt_gwroute and avoid unreachable gw  */

	/* gw selection has failed - there must be only zero weight routes */
	if (!rt) {
		RT_UNLOCK(ro->ro_rt);
		ro->ro_rt = NULL;
		return;
	}
	if (ro->ro_rt != rt) {
		RTFREE_LOCKED(ro->ro_rt);
		ro->ro_rt = rt;
		RT_LOCK(ro->ro_rt);
		RT_ADDREF(ro->ro_rt);

	} 
	RT_UNLOCK(ro->ro_rt);
}