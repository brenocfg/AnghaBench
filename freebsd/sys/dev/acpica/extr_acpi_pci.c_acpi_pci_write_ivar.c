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
struct acpi_pci_devinfo {int ap_flags; int /*<<< orphan*/  ap_handle; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
#define  ACPI_IVAR_FLAGS 129 
#define  ACPI_IVAR_HANDLE 128 
 struct acpi_pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int pci_write_ivar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t) ; 

__attribute__((used)) static int
acpi_pci_write_ivar(device_t dev, device_t child, int which, uintptr_t value)
{
    struct acpi_pci_devinfo *dinfo;

    dinfo = device_get_ivars(child);
    switch (which) {
    case ACPI_IVAR_HANDLE:
	dinfo->ap_handle = (ACPI_HANDLE)value;
	return (0);
    case ACPI_IVAR_FLAGS:
	dinfo->ap_flags = (int)value;
	return (0);
    }
    return (pci_write_ivar(dev, child, which, value));
}