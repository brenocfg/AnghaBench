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
struct netmap_adapter {scalar_t__ active_fds; int /*<<< orphan*/  na_flags; struct ifnet* ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAF_NETMAP_ON ; 
 int /*<<< orphan*/  nm_os_onexit (struct ifnet*) ; 
 int /*<<< orphan*/  nm_update_hostrings_mode (struct netmap_adapter*) ; 

void
nm_clear_native_flags(struct netmap_adapter *na)
{
	struct ifnet *ifp = na->ifp;

	/* We undo the setup for intercepting packets only if we are the
	 * last user of this adapter. */
	if (na->active_fds > 0) {
		return;
	}

	nm_update_hostrings_mode(na);
	nm_os_onexit(ifp);

	na->na_flags &= ~NAF_NETMAP_ON;
}