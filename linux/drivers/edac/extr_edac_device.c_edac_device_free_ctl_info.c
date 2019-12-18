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
struct edac_device_ctl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_device_unregister_sysfs_main_kobj (struct edac_device_ctl_info*) ; 

void edac_device_free_ctl_info(struct edac_device_ctl_info *ctl_info)
{
	edac_device_unregister_sysfs_main_kobj(ctl_info);
}