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

/* Variables and functions */
 int /*<<< orphan*/  NMG_LOCK_DESTROY () ; 
 int /*<<< orphan*/  destroy_dev (scalar_t__) ; 
 scalar_t__ netmap_dev ; 
 int /*<<< orphan*/  netmap_mem_fini () ; 
 int /*<<< orphan*/  netmap_uninit_bridges () ; 
 int /*<<< orphan*/  nm_os_ifnet_fini () ; 
 int /*<<< orphan*/  nm_prinf (char*) ; 

void
netmap_fini(void)
{
	if (netmap_dev)
		destroy_dev(netmap_dev);
	/* we assume that there are no longer netmap users */
	nm_os_ifnet_fini();
	netmap_uninit_bridges();
	netmap_mem_fini();
	NMG_LOCK_DESTROY();
	nm_prinf("netmap: unloaded module.");
}