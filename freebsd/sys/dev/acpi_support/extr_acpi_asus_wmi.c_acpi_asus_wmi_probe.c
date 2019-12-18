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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ASUS_WMI_MGMT_GUID ; 
 int /*<<< orphan*/  ACPI_WMI_PROVIDES_GUID_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
acpi_asus_wmi_probe(device_t dev)
{

	if (!ACPI_WMI_PROVIDES_GUID_STRING(device_get_parent(dev),
	    ACPI_ASUS_WMI_MGMT_GUID))
		return (EINVAL);
	device_set_desc(dev, "ASUS WMI device");
	return (0);
}