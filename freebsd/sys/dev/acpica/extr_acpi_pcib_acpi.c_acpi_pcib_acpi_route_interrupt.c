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
struct acpi_hpcib_softc {int /*<<< orphan*/  ap_prt; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int acpi_pcib_route_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct acpi_hpcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_pcib_acpi_route_interrupt(device_t pcib, device_t dev, int pin)
{
    struct acpi_hpcib_softc *sc = device_get_softc(pcib);

    return (acpi_pcib_route_interrupt(pcib, dev, pin, &sc->ap_prt));
}