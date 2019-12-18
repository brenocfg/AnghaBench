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
struct netmap_adapter {int /*<<< orphan*/  na_flags; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 struct netmap_adapter* NA (struct ifnet*) ; 
 int /*<<< orphan*/  NAF_ZOMBIE ; 
 int /*<<< orphan*/  NM_KR_LOCKED ; 
 scalar_t__ NM_NA_VALID (struct ifnet*) ; 
 int /*<<< orphan*/  netmap_set_all_rings (struct netmap_adapter*,int /*<<< orphan*/ ) ; 

void
netmap_make_zombie(struct ifnet *ifp)
{
	if (NM_NA_VALID(ifp)) {
		struct netmap_adapter *na = NA(ifp);
		netmap_set_all_rings(na, NM_KR_LOCKED);
		na->na_flags |= NAF_ZOMBIE;
		netmap_set_all_rings(na, 0);
	}
}