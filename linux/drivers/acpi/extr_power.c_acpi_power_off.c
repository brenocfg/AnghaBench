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
struct acpi_power_resource {int /*<<< orphan*/  resource_lock; } ;

/* Variables and functions */
 int acpi_power_off_unlocked (struct acpi_power_resource*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_power_off(struct acpi_power_resource *resource)
{
	int result;

	mutex_lock(&resource->resource_lock);
	result = acpi_power_off_unlocked(resource);
	mutex_unlock(&resource->resource_lock);
	return result;
}