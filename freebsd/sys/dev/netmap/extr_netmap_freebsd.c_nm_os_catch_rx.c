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
struct netmap_adapter {int /*<<< orphan*/  name; struct ifnet* ifp; } ;
struct TYPE_2__ {struct netmap_adapter up; } ;
struct netmap_generic_adapter {int /*<<< orphan*/ * save_if_input; TYPE_1__ up; } ;
struct ifnet {int /*<<< orphan*/ * if_input; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/ * freebsd_generic_rx_handler ; 
 int /*<<< orphan*/  nm_os_ifnet_lock () ; 
 int /*<<< orphan*/  nm_os_ifnet_unlock () ; 
 int /*<<< orphan*/  nm_prerr (char*,int /*<<< orphan*/ ) ; 

int
nm_os_catch_rx(struct netmap_generic_adapter *gna, int intercept)
{
	struct netmap_adapter *na = &gna->up.up;
	struct ifnet *ifp = na->ifp;
	int ret = 0;

	nm_os_ifnet_lock();
	if (intercept) {
		if (gna->save_if_input) {
			nm_prerr("RX on %s already intercepted", na->name);
			ret = EBUSY; /* already set */
			goto out;
		}
		gna->save_if_input = ifp->if_input;
		ifp->if_input = freebsd_generic_rx_handler;
	} else {
		if (!gna->save_if_input) {
			nm_prerr("Failed to undo RX intercept on %s",
				na->name);
			ret = EINVAL;  /* not saved */
			goto out;
		}
		ifp->if_input = gna->save_if_input;
		gna->save_if_input = NULL;
	}
out:
	nm_os_ifnet_unlock();

	return ret;
}