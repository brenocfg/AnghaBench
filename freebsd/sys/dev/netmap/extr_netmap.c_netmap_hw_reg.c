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
struct netmap_hw_adapter {int (* nm_hw_register ) (struct netmap_adapter*,int) ;} ;
struct netmap_adapter {int /*<<< orphan*/  na_flags; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  NAF_NETMAP_ON ; 
 scalar_t__ nm_iszombie (struct netmap_adapter*) ; 
 int /*<<< orphan*/  nm_os_ifnet_lock () ; 
 int /*<<< orphan*/  nm_os_ifnet_unlock () ; 
 int stub1 (struct netmap_adapter*,int) ; 

__attribute__((used)) static int
netmap_hw_reg(struct netmap_adapter *na, int onoff)
{
	struct netmap_hw_adapter *hwna =
		(struct netmap_hw_adapter*)na;
	int error = 0;

	nm_os_ifnet_lock();

	if (nm_iszombie(na)) {
		if (onoff) {
			error = ENXIO;
		} else if (na != NULL) {
			na->na_flags &= ~NAF_NETMAP_ON;
		}
		goto out;
	}

	error = hwna->nm_hw_register(na, onoff);

out:
	nm_os_ifnet_unlock();

	return error;
}