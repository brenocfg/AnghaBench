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
typedef  int /*<<< orphan*/  uint64_t ;
struct in6_ifstat {int dummy; } ;
struct in6_ifextra {struct in6_ifextra* icmp6_ifstat; struct in6_ifextra* in6_ifstat; int /*<<< orphan*/  lltable; int /*<<< orphan*/  nd_ifinfo; int /*<<< orphan*/  scope6_id; } ;
struct ifnet {int dummy; } ;
struct icmp6_ifstat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_ARRAY_FREE (struct in6_ifextra*,int) ; 
 int /*<<< orphan*/  M_IFADDR ; 
 int /*<<< orphan*/  free (struct in6_ifextra*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lltable_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mld_domifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  nd6_ifdetach (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scope6_ifdetach (int /*<<< orphan*/ ) ; 

void
in6_domifdetach(struct ifnet *ifp, void *aux)
{
	struct in6_ifextra *ext = (struct in6_ifextra *)aux;

	mld_domifdetach(ifp);
	scope6_ifdetach(ext->scope6_id);
	nd6_ifdetach(ifp, ext->nd_ifinfo);
	lltable_free(ext->lltable);
	COUNTER_ARRAY_FREE(ext->in6_ifstat,
	    sizeof(struct in6_ifstat) / sizeof(uint64_t));
	free(ext->in6_ifstat, M_IFADDR);
	COUNTER_ARRAY_FREE(ext->icmp6_ifstat,
	    sizeof(struct icmp6_ifstat) / sizeof(uint64_t));
	free(ext->icmp6_ifstat, M_IFADDR);
	free(ext, M_IFADDR);
}