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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ bus_address; } ;
struct acpi_device {TYPE_1__ pnp; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ U32_MAX ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static ssize_t acpi_device_adr_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct acpi_device *acpi_dev = to_acpi_device(dev);

	if (acpi_dev->pnp.bus_address > U32_MAX)
		return sprintf(buf, "0x%016llx\n", acpi_dev->pnp.bus_address);
	else
		return sprintf(buf, "0x%08llx\n", acpi_dev->pnp.bus_address);
}