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
struct netmap_generic_adapter {struct netmap_adapter* prev; } ;
struct netmap_adapter {int /*<<< orphan*/  name; int /*<<< orphan*/ * ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NM_RESTORE_NA (struct ifnet*,struct netmap_adapter*) ; 
 int /*<<< orphan*/  netmap_adapter_put (struct netmap_adapter*) ; 
 struct ifnet* netmap_generic_getifp (struct netmap_generic_adapter*) ; 
 scalar_t__ nm_iszombie (struct netmap_adapter*) ; 
 int /*<<< orphan*/  nm_prinf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
generic_netmap_dtor(struct netmap_adapter *na)
{
	struct netmap_generic_adapter *gna = (struct netmap_generic_adapter*)na;
	struct ifnet *ifp = netmap_generic_getifp(gna);
	struct netmap_adapter *prev_na = gna->prev;

	if (prev_na != NULL) {
		netmap_adapter_put(prev_na);
		if (nm_iszombie(na)) {
		        /*
		         * The driver has been removed without releasing
		         * the reference so we need to do it here.
		         */
		        netmap_adapter_put(prev_na);
		}
		nm_prinf("Native netmap adapter for %s restored", prev_na->name);
	}
	NM_RESTORE_NA(ifp, prev_na);
	/*
	 * netmap_detach_common(), that it's called after this function,
	 * overrides WNA(ifp) if na->ifp is not NULL.
	 */
	na->ifp = NULL;
	nm_prinf("Emulated netmap adapter for %s destroyed", na->name);
}