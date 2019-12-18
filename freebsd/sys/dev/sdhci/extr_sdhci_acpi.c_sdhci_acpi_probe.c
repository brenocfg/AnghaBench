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
struct sdhci_acpi_device {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sdhci_acpi_device* sdhci_acpi_find_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sdhci_acpi_probe(device_t dev)
{
	const struct sdhci_acpi_device *acpi_dev;

	acpi_dev = sdhci_acpi_find_device(dev);
	if (acpi_dev == NULL)
		return (ENXIO);

	device_set_desc(dev, acpi_dev->desc);

	return (BUS_PROBE_DEFAULT);
}