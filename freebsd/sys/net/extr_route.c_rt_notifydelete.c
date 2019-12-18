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
struct rtentry {struct ifaddr* rt_ifa; } ;
struct rt_addrinfo {int dummy; } ;
struct ifaddr {int /*<<< orphan*/  (* ifa_rtrequest ) (int /*<<< orphan*/ ,struct rtentry*,struct rt_addrinfo*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RTM_DELETE ; 
 int /*<<< orphan*/  V_rttrash ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct rtentry*,struct rt_addrinfo*) ; 

__attribute__((used)) static void
rt_notifydelete(struct rtentry *rt, struct rt_addrinfo *info)
{
	struct ifaddr *ifa;

	/*
	 * give the protocol a chance to keep things in sync.
	 */
	ifa = rt->rt_ifa;
	if (ifa != NULL && ifa->ifa_rtrequest != NULL)
		ifa->ifa_rtrequest(RTM_DELETE, rt, info);

	/*
	 * One more rtentry floating around that is not
	 * linked to the routing table. rttrash will be decremented
	 * when RTFREE(rt) is eventually called.
	 */
	V_rttrash++;
}