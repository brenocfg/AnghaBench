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
struct device {int dummy; } ;
struct acpi_nfit_desc {int /*<<< orphan*/  init_mutex; int /*<<< orphan*/  dwork; int /*<<< orphan*/  scrub_flags; int /*<<< orphan*/  list; int /*<<< orphan*/  nvdimm_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARS_CANCEL ; 
 int /*<<< orphan*/  acpi_desc_lock ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfit_device_lock (struct device*) ; 
 int /*<<< orphan*/  nfit_device_unlock (struct device*) ; 
 int /*<<< orphan*/  nfit_wq ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct device* to_nvdimm_bus_dev (int /*<<< orphan*/ ) ; 

void acpi_nfit_shutdown(void *data)
{
	struct acpi_nfit_desc *acpi_desc = data;
	struct device *bus_dev = to_nvdimm_bus_dev(acpi_desc->nvdimm_bus);

	/*
	 * Destruct under acpi_desc_lock so that nfit_handle_mce does not
	 * race teardown
	 */
	mutex_lock(&acpi_desc_lock);
	list_del(&acpi_desc->list);
	mutex_unlock(&acpi_desc_lock);

	mutex_lock(&acpi_desc->init_mutex);
	set_bit(ARS_CANCEL, &acpi_desc->scrub_flags);
	cancel_delayed_work_sync(&acpi_desc->dwork);
	mutex_unlock(&acpi_desc->init_mutex);

	/*
	 * Bounce the nvdimm bus lock to make sure any in-flight
	 * acpi_nfit_ars_rescan() submissions have had a chance to
	 * either submit or see ->cancel set.
	 */
	nfit_device_lock(bus_dev);
	nfit_device_unlock(bus_dev);

	flush_workqueue(nfit_wq);
}