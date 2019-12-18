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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static ssize_t
acpi_device_sun_show(struct device *dev, struct device_attribute *attr,
		     char *buf) {
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	acpi_status status;
	unsigned long long sun;

	status = acpi_evaluate_integer(acpi_dev->handle, "_SUN", NULL, &sun);
	if (ACPI_FAILURE(status))
		return -EIO;

	return sprintf(buf, "%llu\n", sun);
}