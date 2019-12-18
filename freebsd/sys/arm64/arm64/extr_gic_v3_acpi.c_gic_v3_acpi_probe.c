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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  ACPI_MADT_GIC_VERSION_V3 128 
 int BUS_PROBE_NOWILDCARD ; 
 int ENXIO ; 
 int /*<<< orphan*/  GIC_V3_DEVSTR ; 
 int /*<<< orphan*/  acpi_get_private (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gic_v3_acpi_probe(device_t dev)
{

	switch((uintptr_t)acpi_get_private(dev)) {
	case ACPI_MADT_GIC_VERSION_V3:
		break;
	default:
		return (ENXIO);
	}

	device_set_desc(dev, GIC_V3_DEVSTR);
	return (BUS_PROBE_NOWILDCARD);
}