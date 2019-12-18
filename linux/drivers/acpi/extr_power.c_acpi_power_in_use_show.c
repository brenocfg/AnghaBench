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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_power_resource {int /*<<< orphan*/  ref_count; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  to_acpi_device (struct device*) ; 
 struct acpi_power_resource* to_power_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t acpi_power_in_use_show(struct device *dev,
				      struct device_attribute *attr,
				      char *buf) {
	struct acpi_power_resource *resource;

	resource = to_power_resource(to_acpi_device(dev));
	return sprintf(buf, "%u\n", !!resource->ref_count);
}