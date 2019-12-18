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
struct acpi_hpcib_softc {uintptr_t ap_bus; int ap_flags; int /*<<< orphan*/  ap_handle; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
#define  ACPI_IVAR_FLAGS 131 
#define  ACPI_IVAR_HANDLE 130 
 int EINVAL ; 
 int ENOENT ; 
#define  PCIB_IVAR_BUS 129 
#define  PCIB_IVAR_DOMAIN 128 
 struct acpi_hpcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_pcib_write_ivar(device_t dev, device_t child, int which, uintptr_t value)
{
    struct acpi_hpcib_softc	*sc = device_get_softc(dev);

    switch (which) {
    case PCIB_IVAR_DOMAIN:
	return (EINVAL);
    case PCIB_IVAR_BUS:
	sc->ap_bus = value;
	return (0);
    case ACPI_IVAR_HANDLE:
	sc->ap_handle = (ACPI_HANDLE)value;
	return (0);
    case ACPI_IVAR_FLAGS:
	sc->ap_flags = (int)value;
	return (0);
    }
    return (ENOENT);
}