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
typedef  int /*<<< orphan*/  sxd ;
struct acpi_softc {int acpi_sstate; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ AE_NOT_FOUND ; 
 int /*<<< orphan*/  AcpiFormatException (scalar_t__) ; 
 int ENXIO ; 
 scalar_t__ acpi_GetInteger (int /*<<< orphan*/ *,char*,int*) ; 
 scalar_t__ acpi_MatchHid (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_name (int /*<<< orphan*/ *) ; 
 struct acpi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int
acpi_device_pwr_for_sleep(device_t bus, device_t dev, int *dstate)
{
    struct acpi_softc *sc;
    ACPI_HANDLE handle;
    ACPI_STATUS status;
    char sxd[8];

    handle = acpi_get_handle(dev);

    /*
     * XXX If we find these devices, don't try to power them down.
     * The serial and IRDA ports on my T23 hang the system when
     * set to D3 and it appears that such legacy devices may
     * need special handling in their drivers.
     */
    if (dstate == NULL || handle == NULL ||
	acpi_MatchHid(handle, "PNP0500") ||
	acpi_MatchHid(handle, "PNP0501") ||
	acpi_MatchHid(handle, "PNP0502") ||
	acpi_MatchHid(handle, "PNP0510") ||
	acpi_MatchHid(handle, "PNP0511"))
	return (ENXIO);

    /*
     * Override next state with the value from _SxD, if present.
     * Note illegal _S0D is evaluated because some systems expect this.
     */
    sc = device_get_softc(bus);
    snprintf(sxd, sizeof(sxd), "_S%dD", sc->acpi_sstate);
    status = acpi_GetInteger(handle, sxd, dstate);
    if (ACPI_FAILURE(status) && status != AE_NOT_FOUND) {
	    device_printf(dev, "failed to get %s on %s: %s\n", sxd,
		acpi_name(handle), AcpiFormatException(status));
	    return (ENXIO);
    }

    return (0);
}