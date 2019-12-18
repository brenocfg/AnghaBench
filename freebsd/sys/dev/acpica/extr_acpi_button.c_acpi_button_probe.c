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
struct acpi_button_softc {int fixed; void* button_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ACPI_ID_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 void* ACPI_POWER_BUTTON ; 
 void* ACPI_SLEEP_BUTTON ; 
 int ENXIO ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/  btn_ids ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct acpi_button_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
acpi_button_probe(device_t dev)
{
    struct acpi_button_softc *sc;
    char *str; 
    int rv;

    if (acpi_disabled("button"))
	return (ENXIO);
    rv = ACPI_ID_PROBE(device_get_parent(dev), dev, btn_ids, &str);
    if (rv > 0)
	return (ENXIO);
    
    sc = device_get_softc(dev);
    if (strcmp(str, "PNP0C0C") == 0) {
	device_set_desc(dev, "Power Button");
	sc->button_type = ACPI_POWER_BUTTON;
    } else if (strcmp(str, "ACPI_FPB") == 0) {
	device_set_desc(dev, "Power Button (fixed)");
	sc->button_type = ACPI_POWER_BUTTON;
	sc->fixed = 1;
    } else if (strcmp(str, "PNP0C0E") == 0) {
	device_set_desc(dev, "Sleep Button");
	sc->button_type = ACPI_SLEEP_BUTTON;
    } else if (strcmp(str, "ACPI_FSB") == 0) {
	device_set_desc(dev, "Sleep Button (fixed)");
	sc->button_type = ACPI_SLEEP_BUTTON;
	sc->fixed = 1;
    }

    return (rv);
}