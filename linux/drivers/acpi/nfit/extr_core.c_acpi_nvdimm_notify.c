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
typedef  int /*<<< orphan*/  u32 ;
struct device {int /*<<< orphan*/  parent; } ;
struct acpi_device {struct device dev; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  __acpi_nvdimm_notify (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfit_device_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfit_device_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_nvdimm_notify(acpi_handle handle, u32 event, void *data)
{
	struct acpi_device *adev = data;
	struct device *dev = &adev->dev;

	nfit_device_lock(dev->parent);
	__acpi_nvdimm_notify(dev, event);
	nfit_device_unlock(dev->parent);
}