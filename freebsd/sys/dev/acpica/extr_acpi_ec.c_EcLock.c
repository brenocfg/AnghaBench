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
struct acpi_ec_softc {int /*<<< orphan*/  ec_glkhandle; scalar_t__ ec_glk; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiAcquireGlobalLock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_LOCK_TIMEOUT ; 
 int /*<<< orphan*/  ec ; 

__attribute__((used)) static ACPI_STATUS
EcLock(struct acpi_ec_softc *sc)
{
    ACPI_STATUS	status;

    /* If _GLK is non-zero, acquire the global lock. */
    status = AE_OK;
    if (sc->ec_glk) {
	status = AcpiAcquireGlobalLock(EC_LOCK_TIMEOUT, &sc->ec_glkhandle);
	if (ACPI_FAILURE(status))
	    return (status);
    }
    ACPI_SERIAL_BEGIN(ec);
    return (status);
}