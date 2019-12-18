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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiReleaseGlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ec ; 

__attribute__((used)) static void
EcUnlock(struct acpi_ec_softc *sc)
{
    ACPI_SERIAL_END(ec);
    if (sc->ec_glk)
	AcpiReleaseGlobalLock(sc->ec_glkhandle);
}