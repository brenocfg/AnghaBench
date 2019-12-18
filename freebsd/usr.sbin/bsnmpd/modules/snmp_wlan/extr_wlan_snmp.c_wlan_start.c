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
struct mibif {int dummy; } ;

/* Variables and functions */
 struct mibif* mib_first_if () ; 
 struct mibif* mib_next_if (struct mibif*) ; 
 int /*<<< orphan*/  oid_wlan ; 
 int /*<<< orphan*/  or_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_wlan ; 
 int /*<<< orphan*/  timer_start_repeat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_attach_newif (struct mibif*) ; 
 int /*<<< orphan*/  wlan_data_timer ; 
 int /*<<< orphan*/  wlan_module ; 
 int /*<<< orphan*/  wlan_poll_ticks ; 
 int /*<<< orphan*/  wlan_update_data ; 

__attribute__((used)) static void
wlan_start(void)
{
	struct mibif *ifp;

	reg_wlan = or_register(&oid_wlan,
	    "The MIB module for managing wireless networking.", wlan_module);

	 /* Add the existing wlan interfaces. */
	 for (ifp = mib_first_if(); ifp != NULL; ifp = mib_next_if(ifp))
		wlan_attach_newif(ifp);

	wlan_data_timer = timer_start_repeat(wlan_poll_ticks,
	    wlan_poll_ticks, wlan_update_data, NULL, wlan_module);
}