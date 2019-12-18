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
struct dmi_system_id {int dummy; } ;

/* Variables and functions */
 int disable_backlight_sysfs_if ; 

__attribute__((used)) static int video_disable_backlight_sysfs_if(
	const struct dmi_system_id *d)
{
	if (disable_backlight_sysfs_if == -1)
		disable_backlight_sysfs_if = 1;
	return 0;
}