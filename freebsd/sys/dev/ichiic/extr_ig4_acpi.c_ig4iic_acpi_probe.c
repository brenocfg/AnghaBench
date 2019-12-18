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
typedef  int /*<<< orphan*/  ig4iic_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ACPI_ID_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ig4iic_ids ; 

__attribute__((used)) static int
ig4iic_acpi_probe(device_t dev)
{
	ig4iic_softc_t *sc;
	int rv;

	sc = device_get_softc(dev);
	if (acpi_disabled("ig4iic"))
		return (ENXIO);
	rv = ACPI_ID_PROBE(device_get_parent(dev), dev, ig4iic_ids, NULL);
	if (rv > 0)
		return (rv);

	device_set_desc(dev, "Designware I2C Controller");
	return (rv);
}