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
struct acpi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  __acpi_nfit_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfit_device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfit_device_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_nfit_notify(struct acpi_device *adev, u32 event)
{
	nfit_device_lock(&adev->dev);
	__acpi_nfit_notify(&adev->dev, adev->handle, event);
	nfit_device_unlock(&adev->dev);
}