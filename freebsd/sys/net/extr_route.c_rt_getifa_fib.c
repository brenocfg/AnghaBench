#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct sockaddr_dl {scalar_t__ sdl_index; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct rt_addrinfo {int rti_flags; TYPE_2__* rti_ifa; int /*<<< orphan*/ * rti_ifp; struct sockaddr** rti_info; } ;
struct epoch_tracker {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ifa_ifp; } ;
struct TYPE_4__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 int ENETUNREACH ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 size_t RTAX_IFA ; 
 int RTF_GATEWAY ; 
 struct sockaddr* dst ; 
 int /*<<< orphan*/  flags ; 
 struct sockaddr* gateway ; 
 TYPE_2__* ifa_ifwithaddr (int /*<<< orphan*/ *) ; 
 void* ifa_ifwithroute (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifa_ref (TYPE_2__*) ; 
 int /*<<< orphan*/ * ifaaddr ; 
 void* ifaof_ifpforaddr (struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ifnet_byindex (scalar_t__) ; 
 TYPE_1__* ifpaddr ; 

int
rt_getifa_fib(struct rt_addrinfo *info, u_int fibnum)
{
	struct epoch_tracker et;
	int needref, error;

	/*
	 * ifp may be specified by sockaddr_dl
	 * when protocol address is ambiguous.
	 */
	error = 0;
	needref = (info->rti_ifa == NULL);
	NET_EPOCH_ENTER(et);

	/* If we have interface specified by the ifindex in the address, use it */
	if (info->rti_ifp == NULL && ifpaddr != NULL &&
	    ifpaddr->sa_family == AF_LINK) {
	    const struct sockaddr_dl *sdl = (const struct sockaddr_dl *)ifpaddr;
	    if (sdl->sdl_index != 0)
		    info->rti_ifp = ifnet_byindex(sdl->sdl_index);
	}
	/*
	 * If we have source address specified, try to find it
	 * TODO: avoid enumerating all ifas on all interfaces.
	 */
	if (info->rti_ifa == NULL && ifaaddr != NULL)
		info->rti_ifa = ifa_ifwithaddr(ifaaddr);
	if (info->rti_ifa == NULL) {
		struct sockaddr *sa;

		/*
		 * Most common use case for the userland-supplied routes.
		 *
		 * Choose sockaddr to select ifa.
		 * -- if ifp is set --
		 * Order of preference:
		 * 1) IFA address
		 * 2) gateway address
		 *   Note: for interface routes link-level gateway address 
		 *     is specified to indicate the interface index without
		 *     specifying RTF_GATEWAY. In this case, ignore gateway
		 *   Note: gateway AF may be different from dst AF. In this case,
		 *   ignore gateway
		 * 3) final destination.
		 * 4) if all of these fails, try to get at least link-level ifa.
		 * -- else --
		 * try to lookup gateway or dst in the routing table to get ifa
		 */
		if (info->rti_info[RTAX_IFA] != NULL)
			sa = info->rti_info[RTAX_IFA];
		else if ((info->rti_flags & RTF_GATEWAY) != 0 &&
		    gateway->sa_family == dst->sa_family)
			sa = gateway;
		else
			sa = dst;
		if (info->rti_ifp != NULL) {
			info->rti_ifa = ifaof_ifpforaddr(sa, info->rti_ifp);
			/* Case 4 */
			if (info->rti_ifa == NULL && gateway != NULL)
				info->rti_ifa = ifaof_ifpforaddr(gateway, info->rti_ifp);
		} else if (dst != NULL && gateway != NULL)
			info->rti_ifa = ifa_ifwithroute(flags, dst, gateway,
							fibnum);
		else if (sa != NULL)
			info->rti_ifa = ifa_ifwithroute(flags, sa, sa,
							fibnum);
	}
	if (needref && info->rti_ifa != NULL) {
		if (info->rti_ifp == NULL)
			info->rti_ifp = info->rti_ifa->ifa_ifp;
		ifa_ref(info->rti_ifa);
	} else
		error = ENETUNREACH;
	NET_EPOCH_EXIT(et);
	return (error);
}