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
struct nvdimm_bus_descriptor {int dummy; } ;
struct device {int dummy; } ;
struct acpi_nfit_desc {int /*<<< orphan*/  init_mutex; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfit_device_lock (struct device*) ; 
 int /*<<< orphan*/  nfit_device_unlock (struct device*) ; 
 struct acpi_nfit_desc* to_acpi_desc (struct nvdimm_bus_descriptor*) ; 

__attribute__((used)) static int acpi_nfit_flush_probe(struct nvdimm_bus_descriptor *nd_desc)
{
	struct acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	struct device *dev = acpi_desc->dev;

	/* Bounce the device lock to flush acpi_nfit_add / acpi_nfit_notify */
	nfit_device_lock(dev);
	nfit_device_unlock(dev);

	/* Bounce the init_mutex to complete initial registration */
	mutex_lock(&acpi_desc->init_mutex);
	mutex_unlock(&acpi_desc->init_mutex);

	return 0;
}