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
 int /*<<< orphan*/  SCU_DOWN ; 
 int /*<<< orphan*/  intel_scu_notifier_post (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ipc_devs ; 
 int ipc_next_dev ; 
 int /*<<< orphan*/  platform_device_del (int /*<<< orphan*/ ) ; 

void intel_scu_devices_destroy(void)
{
	int i;

	intel_scu_notifier_post(SCU_DOWN, NULL);

	for (i = 0; i < ipc_next_dev; i++)
		platform_device_del(ipc_devs[i]);
}