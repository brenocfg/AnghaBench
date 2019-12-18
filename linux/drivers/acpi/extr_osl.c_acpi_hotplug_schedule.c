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
struct acpi_hp_work {int /*<<< orphan*/  work; int /*<<< orphan*/  src; struct acpi_device* adev; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_hotplug_work_fn ; 
 int /*<<< orphan*/  kacpi_hotplug_wq ; 
 int /*<<< orphan*/  kfree (struct acpi_hp_work*) ; 
 struct acpi_hp_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

acpi_status acpi_hotplug_schedule(struct acpi_device *adev, u32 src)
{
	struct acpi_hp_work *hpw;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
		  "Scheduling hotplug event (%p, %u) for deferred execution.\n",
		  adev, src));

	hpw = kmalloc(sizeof(*hpw), GFP_KERNEL);
	if (!hpw)
		return AE_NO_MEMORY;

	INIT_WORK(&hpw->work, acpi_hotplug_work_fn);
	hpw->adev = adev;
	hpw->src = src;
	/*
	 * We can't run hotplug code in kacpid_wq/kacpid_notify_wq etc., because
	 * the hotplug code may call driver .remove() functions, which may
	 * invoke flush_scheduled_work()/acpi_os_wait_events_complete() to flush
	 * these workqueues.
	 */
	if (!queue_work(kacpi_hotplug_wq, &hpw->work)) {
		kfree(hpw);
		return AE_ERROR;
	}
	return AE_OK;
}