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
struct acpi_interface {int num; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiInstallInterface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiRemoveInterface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_free_interfaces (struct acpi_interface*) ; 
 int /*<<< orphan*/  acpi_install_interface ; 
 scalar_t__ acpi_parse_interfaces (int /*<<< orphan*/ ,struct acpi_interface*) ; 
 int /*<<< orphan*/  acpi_remove_interface ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
acpi_reset_interfaces(device_t dev)
{
	struct acpi_interface list;
	ACPI_STATUS status;
	int i;

	if (acpi_parse_interfaces(acpi_install_interface, &list) > 0) {
		for (i = 0; i < list.num; i++) {
			status = AcpiInstallInterface(list.data[i]);
			if (ACPI_FAILURE(status))
				device_printf(dev,
				    "failed to install _OSI(\"%s\"): %s\n",
				    list.data[i], AcpiFormatException(status));
			else if (bootverbose)
				device_printf(dev, "installed _OSI(\"%s\")\n",
				    list.data[i]);
		}
		acpi_free_interfaces(&list);
	}
	if (acpi_parse_interfaces(acpi_remove_interface, &list) > 0) {
		for (i = 0; i < list.num; i++) {
			status = AcpiRemoveInterface(list.data[i]);
			if (ACPI_FAILURE(status))
				device_printf(dev,
				    "failed to remove _OSI(\"%s\"): %s\n",
				    list.data[i], AcpiFormatException(status));
			else if (bootverbose)
				device_printf(dev, "removed _OSI(\"%s\")\n",
				    list.data[i]);
		}
		acpi_free_interfaces(&list);
	}
}