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
struct acpi_tz_softc {int tz_temperature; int /*<<< orphan*/  tz_dev; int /*<<< orphan*/  tz_handle; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_VALUES ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (char*) ; 
 int /*<<< orphan*/  ACPI_VPRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  TZ_KELVTOC (int) ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tz_sanity (struct acpi_tz_softc*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tz_tmp_name ; 

__attribute__((used)) static int
acpi_tz_get_temperature(struct acpi_tz_softc *sc)
{
    int		temp;
    ACPI_STATUS	status;

    ACPI_FUNCTION_NAME ("acpi_tz_get_temperature");

    /* Evaluate the thermal zone's _TMP method. */
    status = acpi_GetInteger(sc->tz_handle, acpi_tz_tmp_name, &temp);
    if (ACPI_FAILURE(status)) {
	ACPI_VPRINT(sc->tz_dev, acpi_device_get_parent_softc(sc->tz_dev),
	    "error fetching current temperature -- %s\n",
	     AcpiFormatException(status));
	return (FALSE);
    }

    /* Check it for validity. */
    acpi_tz_sanity(sc, &temp, acpi_tz_tmp_name);
    if (temp == -1)
	return (FALSE);

    ACPI_DEBUG_PRINT((ACPI_DB_VALUES, "got %d.%dC\n", TZ_KELVTOC(temp)));
    sc->tz_temperature = temp;
    return (TRUE);
}