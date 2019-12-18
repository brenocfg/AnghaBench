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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_ID_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
acpi_smbat_probe(device_t dev)
{
	static char *smbat_ids[] = {"ACPI0001", "ACPI0005", NULL};
	ACPI_STATUS status;
	int rv;

	if (acpi_disabled("smbat"))
		return (ENXIO);
	rv = ACPI_ID_PROBE(device_get_parent(dev), dev, smbat_ids, NULL);
	if (rv > 0)
	  return (rv);
	status = AcpiEvaluateObject(acpi_get_handle(dev), "_EC", NULL, NULL);
	if (ACPI_FAILURE(status))
		return (ENXIO);
	device_set_desc(dev, "ACPI Smart Battery");
	return (rv);
}