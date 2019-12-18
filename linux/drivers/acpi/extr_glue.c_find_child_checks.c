#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  platform_id; } ;
struct TYPE_3__ {TYPE_2__ type; } ;
struct acpi_device {TYPE_1__ pnp; int /*<<< orphan*/  children; int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 unsigned long long ACPI_STA_DEVICE_ENABLED ; 
 scalar_t__ AE_NOT_FOUND ; 
 int ENODEV ; 
 int FIND_CHILD_MAX_SCORE ; 
 int FIND_CHILD_MIN_SCORE ; 
 scalar_t__ acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_child_checks(struct acpi_device *adev, bool check_children)
{
	bool sta_present = true;
	unsigned long long sta;
	acpi_status status;

	status = acpi_evaluate_integer(adev->handle, "_STA", NULL, &sta);
	if (status == AE_NOT_FOUND)
		sta_present = false;
	else if (ACPI_FAILURE(status) || !(sta & ACPI_STA_DEVICE_ENABLED))
		return -ENODEV;

	if (check_children && list_empty(&adev->children))
		return -ENODEV;

	/*
	 * If the device has a _HID returning a valid ACPI/PNP device ID, it is
	 * better to make it look less attractive here, so that the other device
	 * with the same _ADR value (that may not have a valid device ID) can be
	 * matched going forward.  [This means a second spec violation in a row,
	 * so whatever we do here is best effort anyway.]
	 */
	return sta_present && !adev->pnp.type.platform_id ?
			FIND_CHILD_MAX_SCORE : FIND_CHILD_MIN_SCORE;
}