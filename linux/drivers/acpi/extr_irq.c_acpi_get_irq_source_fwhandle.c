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
struct fwnode_handle {int dummy; } ;
struct acpi_resource_source {int /*<<< orphan*/  string_ptr; int /*<<< orphan*/  string_length; } ;
struct acpi_device {struct fwnode_handle fwnode; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct acpi_device* acpi_bus_get_acpi_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_bus_put_acpi_device (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fwnode_handle* acpi_gsi_domain_id ; 

__attribute__((used)) static struct fwnode_handle *
acpi_get_irq_source_fwhandle(const struct acpi_resource_source *source)
{
	struct fwnode_handle *result;
	struct acpi_device *device;
	acpi_handle handle;
	acpi_status status;

	if (!source->string_length)
		return acpi_gsi_domain_id;

	status = acpi_get_handle(NULL, source->string_ptr, &handle);
	if (WARN_ON(ACPI_FAILURE(status)))
		return NULL;

	device = acpi_bus_get_acpi_device(handle);
	if (WARN_ON(!device))
		return NULL;

	result = &device->fwnode;
	acpi_bus_put_acpi_device(device);
	return result;
}