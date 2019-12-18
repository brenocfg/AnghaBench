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
 int /*<<< orphan*/  acpi_bus_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_video_bus ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ register_count ; 
 int /*<<< orphan*/  register_count_mutex ; 

void acpi_video_unregister(void)
{
	mutex_lock(&register_count_mutex);
	if (register_count) {
		acpi_bus_unregister_driver(&acpi_video_bus);
		register_count = 0;
	}
	mutex_unlock(&register_count_mutex);
}