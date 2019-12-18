#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * Pointer; } ;
struct acpi_pcib_softc {TYPE_1__ ap_prt; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int acpi_pcib_route_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 struct acpi_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pcib_route_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
acpi_pcib_pci_route_interrupt(device_t pcib, device_t dev, int pin)
{
    struct acpi_pcib_softc *sc;

    sc = device_get_softc(pcib);

    /*
     * If we don't have a _PRT, fall back to the swizzle method
     * for routing interrupts.
     */
    if (sc->ap_prt.Pointer == NULL)
	return (pcib_route_interrupt(pcib, dev, pin));
    else
	return (acpi_pcib_route_interrupt(pcib, dev, pin, &sc->ap_prt));
}