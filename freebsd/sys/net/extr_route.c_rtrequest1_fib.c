#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int sa_family; int sa_len; } ;
struct rtentry {int rt_flags; int rt_weight; struct ifaddr* rt_ifa; int /*<<< orphan*/  rt_nodes; int /*<<< orphan*/  rt_ifp; scalar_t__ rt_fibnum; } ;
struct rt_addrinfo {int rti_flags; struct sockaddr** rti_info; struct ifaddr* rti_ifa; } ;
struct rib_head {int /*<<< orphan*/  rnh_gen; int /*<<< orphan*/  head; struct radix_node* (* rnh_addaddr ) (struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct radix_node {int dummy; } ;
struct ifaddr {int /*<<< orphan*/  (* ifa_rtrequest ) (int,struct rtentry*,struct rt_addrinfo*) ;int /*<<< orphan*/  ifa_ifp; } ;
typedef  int /*<<< orphan*/  mdst ;
struct TYPE_3__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 133 
#define  AF_INET6 132 
 int AF_LINK ; 
 int AF_UNSPEC ; 
 int EAFNOSUPPORT ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  RIB_WLOCK (struct rib_head*) ; 
 int /*<<< orphan*/  RIB_WUNLOCK (struct rib_head*) ; 
 size_t RTAX_DST ; 
 int /*<<< orphan*/  RTFREE (struct rtentry*) ; 
 int /*<<< orphan*/  RTFREE_LOCKED (struct rtentry*) ; 
 int RTF_GATEWAY ; 
 int RTF_HOST ; 
 int RTF_PINNED ; 
 int RTF_RNH_LOCKED ; 
 int RTF_UP ; 
#define  RTM_ADD 131 
#define  RTM_CHANGE 130 
#define  RTM_DELETE 129 
#define  RTM_RESOLVE 128 
 int /*<<< orphan*/  RT_ADDREF (struct rtentry*) ; 
 scalar_t__ RT_DEFAULT_FIB ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  R_Free (scalar_t__) ; 
 int /*<<< orphan*/  V_rtzone ; 
 int /*<<< orphan*/  bcopy (struct sockaddr*,struct sockaddr*,int) ; 
 struct sockaddr* dst ; 
 int flags ; 
 TYPE_1__* gateway ; 
 int /*<<< orphan*/  ifa_free (struct ifaddr*) ; 
 int /*<<< orphan*/  ifa_ref (struct ifaddr*) ; 
 int /*<<< orphan*/ * netmask ; 
 int rt_getifa_fib (struct rt_addrinfo*,scalar_t__) ; 
 scalar_t__ rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rt_maskedcopy (struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_mpath_capable (struct rib_head*) ; 
 int /*<<< orphan*/  rt_mpath_conflict (struct rib_head*,struct rtentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_notifydelete (struct rtentry*,struct rt_addrinfo*) ; 
 scalar_t__ rt_numfibs ; 
 int rt_setgate (struct rtentry*,struct sockaddr*,TYPE_1__*) ; 
 int /*<<< orphan*/  rt_setmetrics (struct rt_addrinfo*,struct rtentry*) ; 
 struct rib_head* rt_tables_get_rnh (scalar_t__,int) ; 
 struct rtentry* rt_unlinkrte (struct rib_head*,struct rt_addrinfo*,int*) ; 
 int rtrequest1_fib_change (struct rib_head*,struct rt_addrinfo*,struct rtentry**,scalar_t__) ; 
 struct radix_node* stub1 (struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct radix_node* stub2 (struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,struct rtentry*,struct rt_addrinfo*) ; 
 struct rtentry* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct rtentry*) ; 

int
rtrequest1_fib(int req, struct rt_addrinfo *info, struct rtentry **ret_nrt,
				u_int fibnum)
{
	int error = 0;
	struct rtentry *rt, *rt_old;
	struct radix_node *rn;
	struct rib_head *rnh;
	struct ifaddr *ifa;
	struct sockaddr *ndst;
	struct sockaddr_storage mdst;

	KASSERT((fibnum < rt_numfibs), ("rtrequest1_fib: bad fibnum"));
	KASSERT((flags & RTF_RNH_LOCKED) == 0, ("rtrequest1_fib: locked"));
	switch (dst->sa_family) {
	case AF_INET6:
	case AF_INET:
		/* We support multiple FIBs. */
		break;
	default:
		fibnum = RT_DEFAULT_FIB;
		break;
	}

	/*
	 * Find the correct routing tree to use for this Address Family
	 */
	rnh = rt_tables_get_rnh(fibnum, dst->sa_family);
	if (rnh == NULL)
		return (EAFNOSUPPORT);

	/*
	 * If we are adding a host route then we don't want to put
	 * a netmask in the tree, nor do we want to clone it.
	 */
	if (flags & RTF_HOST)
		netmask = NULL;

	switch (req) {
	case RTM_DELETE:
		if (netmask) {
			if (dst->sa_len > sizeof(mdst))
				return (EINVAL);
			rt_maskedcopy(dst, (struct sockaddr *)&mdst, netmask);
			dst = (struct sockaddr *)&mdst;
		}

		RIB_WLOCK(rnh);
		rt = rt_unlinkrte(rnh, info, &error);
		RIB_WUNLOCK(rnh);
		if (error != 0)
			return (error);

		rt_notifydelete(rt, info);

		/*
		 * If the caller wants it, then it can have it,
		 * but it's up to it to free the rtentry as we won't be
		 * doing it.
		 */
		if (ret_nrt) {
			*ret_nrt = rt;
			RT_UNLOCK(rt);
		} else
			RTFREE_LOCKED(rt);
		break;
	case RTM_RESOLVE:
		/*
		 * resolve was only used for route cloning
		 * here for compat
		 */
		break;
	case RTM_ADD:
		if ((flags & RTF_GATEWAY) && !gateway)
			return (EINVAL);
		if (dst && gateway && (dst->sa_family != gateway->sa_family) && 
		    (gateway->sa_family != AF_UNSPEC) && (gateway->sa_family != AF_LINK))
			return (EINVAL);

		if (info->rti_ifa == NULL) {
			error = rt_getifa_fib(info, fibnum);
			if (error)
				return (error);
		}
		rt = uma_zalloc(V_rtzone, M_NOWAIT);
		if (rt == NULL) {
			return (ENOBUFS);
		}
		rt->rt_flags = RTF_UP | flags;
		rt->rt_fibnum = fibnum;
		/*
		 * Add the gateway. Possibly re-malloc-ing the storage for it.
		 */
		if ((error = rt_setgate(rt, dst, gateway)) != 0) {
			uma_zfree(V_rtzone, rt);
			return (error);
		}

		/*
		 * point to the (possibly newly malloc'd) dest address.
		 */
		ndst = (struct sockaddr *)rt_key(rt);

		/*
		 * make sure it contains the value we want (masked if needed).
		 */
		if (netmask) {
			rt_maskedcopy(dst, ndst, netmask);
		} else
			bcopy(dst, ndst, dst->sa_len);

		/*
		 * We use the ifa reference returned by rt_getifa_fib().
		 * This moved from below so that rnh->rnh_addaddr() can
		 * examine the ifa and  ifa->ifa_ifp if it so desires.
		 */
		ifa = info->rti_ifa;
		ifa_ref(ifa);
		rt->rt_ifa = ifa;
		rt->rt_ifp = ifa->ifa_ifp;
		rt->rt_weight = 1;

		rt_setmetrics(info, rt);

		RIB_WLOCK(rnh);
		RT_LOCK(rt);
#ifdef RADIX_MPATH
		/* do not permit exactly the same dst/mask/gw pair */
		if (rt_mpath_capable(rnh) &&
			rt_mpath_conflict(rnh, rt, netmask)) {
			RIB_WUNLOCK(rnh);

			ifa_free(rt->rt_ifa);
			R_Free(rt_key(rt));
			uma_zfree(V_rtzone, rt);
			return (EEXIST);
		}
#endif

		/* XXX mtu manipulation will be done in rnh_addaddr -- itojun */
		rn = rnh->rnh_addaddr(ndst, netmask, &rnh->head, rt->rt_nodes);

		rt_old = NULL;
		if (rn == NULL && (info->rti_flags & RTF_PINNED) != 0) {

			/*
			 * Force removal and re-try addition
			 * TODO: better multipath&pinned support
			 */
			struct sockaddr *info_dst = info->rti_info[RTAX_DST];
			info->rti_info[RTAX_DST] = ndst;
			/* Do not delete existing PINNED(interface) routes */
			info->rti_flags &= ~RTF_PINNED;
			rt_old = rt_unlinkrte(rnh, info, &error);
			info->rti_flags |= RTF_PINNED;
			info->rti_info[RTAX_DST] = info_dst;
			if (rt_old != NULL)
				rn = rnh->rnh_addaddr(ndst, netmask, &rnh->head,
				    rt->rt_nodes);
		}
		RIB_WUNLOCK(rnh);

		if (rt_old != NULL)
			RT_UNLOCK(rt_old);

		/*
		 * If it still failed to go into the tree,
		 * then un-make it (this should be a function)
		 */
		if (rn == NULL) {
			ifa_free(rt->rt_ifa);
			R_Free(rt_key(rt));
			uma_zfree(V_rtzone, rt);
			return (EEXIST);
		} 

		if (rt_old != NULL) {
			rt_notifydelete(rt_old, info);
			RTFREE(rt_old);
		}

		/*
		 * If this protocol has something to add to this then
		 * allow it to do that as well.
		 */
		if (ifa->ifa_rtrequest)
			ifa->ifa_rtrequest(req, rt, info);

		/*
		 * actually return a resultant rtentry and
		 * give the caller a single reference.
		 */
		if (ret_nrt) {
			*ret_nrt = rt;
			RT_ADDREF(rt);
		}
		rnh->rnh_gen++;		/* Routing table updated */
		RT_UNLOCK(rt);
		break;
	case RTM_CHANGE:
		RIB_WLOCK(rnh);
		error = rtrequest1_fib_change(rnh, info, ret_nrt, fibnum);
		RIB_WUNLOCK(rnh);
		break;
	default:
		error = EOPNOTSUPP;
	}

	return (error);
}