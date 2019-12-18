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
struct in6_multi_head {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN6_MULTI_LIST_LOCK () ; 
 int /*<<< orphan*/  IN6_MULTI_LIST_UNLOCK () ; 
 int /*<<< orphan*/  IN6_MULTI_LOCK () ; 
 int /*<<< orphan*/  IN6_MULTI_UNLOCK () ; 
 int /*<<< orphan*/  SLIST_INIT (struct in6_multi_head*) ; 
 int /*<<< orphan*/  in6m_release_list_deferred (struct in6_multi_head*) ; 
 int /*<<< orphan*/  in6m_release_wait () ; 
 int /*<<< orphan*/  mld_ifdetach (struct ifnet*,struct in6_multi_head*) ; 

__attribute__((used)) static void
in6_purgemaddrs(struct ifnet *ifp)
{
	struct in6_multi_head inmh;

	SLIST_INIT(&inmh);
	IN6_MULTI_LOCK();
	IN6_MULTI_LIST_LOCK();
	mld_ifdetach(ifp, &inmh);
	IN6_MULTI_LIST_UNLOCK();
	IN6_MULTI_UNLOCK();
	in6m_release_list_deferred(&inmh);

	/*
	 * Make sure all multicast deletions invoking if_ioctl() are
	 * completed before returning. Else we risk accessing a freed
	 * ifnet structure pointer.
	 */
	in6m_release_wait();
}