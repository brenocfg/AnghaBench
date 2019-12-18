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
struct acpi_ec_softc {int /*<<< orphan*/  ec_suspending; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 struct acpi_ec_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_ec_resume(device_t dev)
{
    struct acpi_ec_softc	*sc;

    sc = device_get_softc(dev);
    sc->ec_suspending = FALSE;
    return (0);
}