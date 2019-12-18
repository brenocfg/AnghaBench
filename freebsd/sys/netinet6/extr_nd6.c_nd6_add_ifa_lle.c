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
struct sockaddr {int dummy; } ;
struct llentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifa_rtrequest; struct ifnet* ifa_ifp; } ;
struct in6_ifaddr {int /*<<< orphan*/  ia_addr; TYPE_1__ ia_ifa; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,struct llentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_AFDATA_WLOCK (struct ifnet*) ; 
 int /*<<< orphan*/  IF_AFDATA_WUNLOCK (struct ifnet*) ; 
 int /*<<< orphan*/  LLENTRY_EXPIRED ; 
 int /*<<< orphan*/  LLENTRY_RESOLVED ; 
 int /*<<< orphan*/  LLE_EXCLUSIVE ; 
 int /*<<< orphan*/  LLE_IFADDR ; 
 int /*<<< orphan*/  LLE_WLOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLE_WUNLOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLTABLE6 (struct ifnet*) ; 
 struct llentry* lla_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  lle_event ; 
 int /*<<< orphan*/  llentry_free (struct llentry*) ; 
 struct llentry* lltable_alloc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  lltable_link_entry (int /*<<< orphan*/ ,struct llentry*) ; 
 int /*<<< orphan*/  lltable_unlink_entry (int /*<<< orphan*/ ,struct llentry*) ; 
 scalar_t__ nd6_need_cache (struct ifnet*) ; 
 int /*<<< orphan*/  nd6_rtrequest ; 

int
nd6_add_ifa_lle(struct in6_ifaddr *ia)
{
	struct ifnet *ifp;
	struct llentry *ln, *ln_tmp;
	struct sockaddr *dst;

	ifp = ia->ia_ifa.ifa_ifp;
	if (nd6_need_cache(ifp) == 0)
		return (0);

	ia->ia_ifa.ifa_rtrequest = nd6_rtrequest;
	dst = (struct sockaddr *)&ia->ia_addr;
	ln = lltable_alloc_entry(LLTABLE6(ifp), LLE_IFADDR, dst);
	if (ln == NULL)
		return (ENOBUFS);

	IF_AFDATA_WLOCK(ifp);
	LLE_WLOCK(ln);
	/* Unlink any entry if exists */
	ln_tmp = lla_lookup(LLTABLE6(ifp), LLE_EXCLUSIVE, dst);
	if (ln_tmp != NULL)
		lltable_unlink_entry(LLTABLE6(ifp), ln_tmp);
	lltable_link_entry(LLTABLE6(ifp), ln);
	IF_AFDATA_WUNLOCK(ifp);

	if (ln_tmp != NULL)
		EVENTHANDLER_INVOKE(lle_event, ln_tmp, LLENTRY_EXPIRED);
	EVENTHANDLER_INVOKE(lle_event, ln, LLENTRY_RESOLVED);

	LLE_WUNLOCK(ln);
	if (ln_tmp != NULL)
		llentry_free(ln_tmp);

	return (0);
}