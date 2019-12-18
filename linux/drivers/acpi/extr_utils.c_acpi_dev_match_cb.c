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
struct TYPE_2__ {int /*<<< orphan*/  unique_id; } ;
struct acpi_device {int /*<<< orphan*/  handle; TYPE_1__ pnp; } ;
struct acpi_dev_match_info {int hrv; scalar_t__ uid; int /*<<< orphan*/  hid; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 scalar_t__ acpi_match_device_ids (struct acpi_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static int acpi_dev_match_cb(struct device *dev, const void *data)
{
	struct acpi_device *adev = to_acpi_device(dev);
	const struct acpi_dev_match_info *match = data;
	unsigned long long hrv;
	acpi_status status;

	if (acpi_match_device_ids(adev, match->hid))
		return 0;

	if (match->uid && (!adev->pnp.unique_id ||
	    strcmp(adev->pnp.unique_id, match->uid)))
		return 0;

	if (match->hrv == -1)
		return 1;

	status = acpi_evaluate_integer(adev->handle, "_HRV", NULL, &hrv);
	if (ACPI_FAILURE(status))
		return 0;

	return hrv == match->hrv;
}