#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct rtentry {int rt_flags; int rt_mtu; int /*<<< orphan*/  rt_nodes; int /*<<< orphan*/ * rt_ifp; TYPE_6__* rt_ifa; } ;
struct rt_addrinfo {int rti_flags; TYPE_6__* rti_ifa; TYPE_1__** rti_info; int /*<<< orphan*/ * rti_ifp; } ;
struct rib_head {int /*<<< orphan*/  rnh_gen; int /*<<< orphan*/  head; scalar_t__ (* rnh_lookup ) (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct if_mtuinfo {int mtu; int /*<<< orphan*/ * ifp; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* ifa_rtrequest ) (int /*<<< orphan*/ ,struct rtentry*,struct rt_addrinfo*) ;int /*<<< orphan*/  ifa_addr; } ;
struct TYPE_8__ {int sa_family; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  RIB_WLOCK_ASSERT (struct rib_head*) ; 
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 size_t RTAX_IFA ; 
 size_t RTAX_IFP ; 
 size_t RTAX_NETMASK ; 
 int RTF_FMASK ; 
 int RTF_GATEWAY ; 
 int RTF_RNH_LOCKED ; 
 int /*<<< orphan*/  RTM_ADD ; 
 int /*<<< orphan*/  RTM_DELETE ; 
 int /*<<< orphan*/  RT_ADDREF (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int if_getmtu_family (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_updatemtu_cb (int /*<<< orphan*/ ,struct if_mtuinfo*) ; 
 int /*<<< orphan*/  ifa_free (TYPE_6__*) ; 
 int /*<<< orphan*/  ifa_ref (TYPE_6__*) ; 
 int rt_getifa_fib (struct rt_addrinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 scalar_t__ rt_mpath_capable (struct rib_head*) ; 
 struct rtentry* rt_mpath_matchgate (struct rtentry*,TYPE_1__*) ; 
 int rt_setgate (struct rtentry*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rt_setmetrics (struct rt_addrinfo*,struct rtentry*) ; 
 int /*<<< orphan*/  sa_equal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct rtentry*,struct rt_addrinfo*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct rtentry*,struct rt_addrinfo*) ; 

__attribute__((used)) static int
rtrequest1_fib_change(struct rib_head *rnh, struct rt_addrinfo *info,
    struct rtentry **ret_nrt, u_int fibnum)
{
	struct rtentry *rt = NULL;
	int error = 0;
	int free_ifa = 0;
	int family, mtu;
	struct if_mtuinfo ifmtu;

	RIB_WLOCK_ASSERT(rnh);

	rt = (struct rtentry *)rnh->rnh_lookup(info->rti_info[RTAX_DST],
	    info->rti_info[RTAX_NETMASK], &rnh->head);

	if (rt == NULL)
		return (ESRCH);

#ifdef RADIX_MPATH
	/*
	 * If we got multipath routes,
	 * we require users to specify a matching RTAX_GATEWAY.
	 */
	if (rt_mpath_capable(rnh)) {
		rt = rt_mpath_matchgate(rt, info->rti_info[RTAX_GATEWAY]);
		if (rt == NULL)
			return (ESRCH);
	}
#endif

	RT_LOCK(rt);

	rt_setmetrics(info, rt);

	/*
	 * New gateway could require new ifaddr, ifp;
	 * flags may also be different; ifp may be specified
	 * by ll sockaddr when protocol address is ambiguous
	 */
	if (((rt->rt_flags & RTF_GATEWAY) &&
	    info->rti_info[RTAX_GATEWAY] != NULL) ||
	    info->rti_info[RTAX_IFP] != NULL ||
	    (info->rti_info[RTAX_IFA] != NULL &&
	     !sa_equal(info->rti_info[RTAX_IFA], rt->rt_ifa->ifa_addr))) {
		/*
		 * XXX: Temporarily set RTF_RNH_LOCKED flag in the rti_flags
		 *	to avoid rlock in the ifa_ifwithroute().
		 */
		info->rti_flags |= RTF_RNH_LOCKED;
		error = rt_getifa_fib(info, fibnum);
		info->rti_flags &= ~RTF_RNH_LOCKED;
		if (info->rti_ifa != NULL)
			free_ifa = 1;

		if (error != 0)
			goto bad;
	}

	/* Check if outgoing interface has changed */
	if (info->rti_ifa != NULL && info->rti_ifa != rt->rt_ifa &&
	    rt->rt_ifa != NULL) {
		if (rt->rt_ifa->ifa_rtrequest != NULL)
			rt->rt_ifa->ifa_rtrequest(RTM_DELETE, rt, info);
		ifa_free(rt->rt_ifa);
		rt->rt_ifa = NULL;
	}
	/* Update gateway address */
	if (info->rti_info[RTAX_GATEWAY] != NULL) {
		error = rt_setgate(rt, rt_key(rt), info->rti_info[RTAX_GATEWAY]);
		if (error != 0)
			goto bad;

		rt->rt_flags &= ~RTF_GATEWAY;
		rt->rt_flags |= (RTF_GATEWAY & info->rti_flags);
	}

	if (info->rti_ifa != NULL && info->rti_ifa != rt->rt_ifa) {
		ifa_ref(info->rti_ifa);
		rt->rt_ifa = info->rti_ifa;
		rt->rt_ifp = info->rti_ifp;
	}
	/* Allow some flags to be toggled on change. */
	rt->rt_flags &= ~RTF_FMASK;
	rt->rt_flags |= info->rti_flags & RTF_FMASK;

	if (rt->rt_ifa && rt->rt_ifa->ifa_rtrequest != NULL)
	       rt->rt_ifa->ifa_rtrequest(RTM_ADD, rt, info);

	/* Alter route MTU if necessary */
	if (rt->rt_ifp != NULL) {
		family = info->rti_info[RTAX_DST]->sa_family;
		mtu = if_getmtu_family(rt->rt_ifp, family);
		/* Set default MTU */
		if (rt->rt_mtu == 0)
			rt->rt_mtu = mtu;
		if (rt->rt_mtu != mtu) {
			/* Check if we really need to update */
			ifmtu.ifp = rt->rt_ifp;
			ifmtu.mtu = mtu;
			if_updatemtu_cb(rt->rt_nodes, &ifmtu);
		}
	}

	/*
	 * This route change may have modified the route's gateway.  In that
	 * case, any inpcbs that have cached this route need to invalidate their
	 * llentry cache.
	 */
	rnh->rnh_gen++;

	if (ret_nrt) {
		*ret_nrt = rt;
		RT_ADDREF(rt);
	}
bad:
	RT_UNLOCK(rt);
	if (free_ifa != 0) {
		ifa_free(info->rti_ifa);
		info->rti_ifa = NULL;
	}
	return (error);
}