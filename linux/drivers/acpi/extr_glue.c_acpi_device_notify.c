#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct acpi_device {TYPE_1__* handler; } ;
struct acpi_bus_type {int /*<<< orphan*/  (* setup ) (struct device*) ;struct acpi_device* (* find_companion ) (struct device*) ;} ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* bind ) (struct device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int /*<<< orphan*/  ACPI_FULL_PATHNAME ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,...) ; 
 int ENODEV ; 
 int acpi_bind_one (struct device*,struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_configure_pmsi_domain (struct device*) ; 
 struct acpi_bus_type* acpi_get_bus_type (struct device*) ; 
 int /*<<< orphan*/  acpi_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 scalar_t__ dev_is_platform (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 struct acpi_device* stub1 (struct device*) ; 
 int /*<<< orphan*/  stub2 (struct device*) ; 
 int /*<<< orphan*/  stub3 (struct device*) ; 

__attribute__((used)) static int acpi_device_notify(struct device *dev)
{
	struct acpi_bus_type *type = acpi_get_bus_type(dev);
	struct acpi_device *adev;
	int ret;

	ret = acpi_bind_one(dev, NULL);
	if (ret && type) {
		struct acpi_device *adev;

		adev = type->find_companion(dev);
		if (!adev) {
			DBG("Unable to get handle for %s\n", dev_name(dev));
			ret = -ENODEV;
			goto out;
		}
		ret = acpi_bind_one(dev, adev);
		if (ret)
			goto out;
	}
	adev = ACPI_COMPANION(dev);
	if (!adev)
		goto out;

	if (dev_is_platform(dev))
		acpi_configure_pmsi_domain(dev);

	if (type && type->setup)
		type->setup(dev);
	else if (adev->handler && adev->handler->bind)
		adev->handler->bind(dev);

 out:
#if ACPI_GLUE_DEBUG
	if (!ret) {
		struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };

		acpi_get_name(ACPI_HANDLE(dev), ACPI_FULL_PATHNAME, &buffer);
		DBG("Device %s -> %s\n", dev_name(dev), (char *)buffer.pointer);
		kfree(buffer.pointer);
	} else
		DBG("Device %s -> No ACPI support\n", dev_name(dev));
#endif

	return ret;
}