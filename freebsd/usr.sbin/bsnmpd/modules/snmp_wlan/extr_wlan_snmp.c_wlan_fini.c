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
 int /*<<< orphan*/  mib_unregister_newif (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  or_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_wlan ; 
 int /*<<< orphan*/  wlan_free_iflist () ; 
 int /*<<< orphan*/  wlan_module ; 

__attribute__((used)) static int
wlan_fini(void)
{
	mib_unregister_newif(wlan_module);
	or_unregister(reg_wlan);

	/* XXX: Cleanup! */
	wlan_free_iflist();

	return (0);
}