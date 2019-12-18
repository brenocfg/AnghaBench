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
typedef  scalar_t__ u32 ;
struct zpodd {int from_notify; } ;
struct device {int dummy; } ;
struct ata_device {TYPE_1__* sdev; struct zpodd* zpodd; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {struct device sdev_gendev; } ;

/* Variables and functions */
 scalar_t__ ACPI_NOTIFY_DEVICE_WAKE ; 
 int /*<<< orphan*/  pm_runtime_resume (struct device*) ; 
 scalar_t__ pm_runtime_suspended (struct device*) ; 

__attribute__((used)) static void zpodd_wake_dev(acpi_handle handle, u32 event, void *context)
{
	struct ata_device *ata_dev = context;
	struct zpodd *zpodd = ata_dev->zpodd;
	struct device *dev = &ata_dev->sdev->sdev_gendev;

	if (event == ACPI_NOTIFY_DEVICE_WAKE && pm_runtime_suspended(dev)) {
		zpodd->from_notify = true;
		pm_runtime_resume(dev);
	}
}