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
struct sp_dev_vdata {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;

/* Variables and functions */
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sp_acpi_match ; 

__attribute__((used)) static struct sp_dev_vdata *sp_get_acpi_version(struct platform_device *pdev)
{
#ifdef CONFIG_ACPI
	const struct acpi_device_id *match;

	match = acpi_match_device(sp_acpi_match, &pdev->dev);
	if (match && match->driver_data)
		return (struct sp_dev_vdata *)match->driver_data;
#endif
	return NULL;
}