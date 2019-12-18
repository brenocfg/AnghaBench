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
struct ps3_os_area_flash_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_area_flash_mutex ; 
 struct ps3_os_area_flash_ops const* os_area_flash_ops ; 

void ps3_os_area_flash_register(const struct ps3_os_area_flash_ops *ops)
{
	mutex_lock(&os_area_flash_mutex);
	os_area_flash_ops = ops;
	mutex_unlock(&os_area_flash_mutex);
}