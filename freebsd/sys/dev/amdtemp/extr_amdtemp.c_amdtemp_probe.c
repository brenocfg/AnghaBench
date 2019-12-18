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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_GENERIC ; 
 int CPUID_STEPPING ; 
 int CPUID_TO_FAMILY (int) ; 
 int CPUID_TO_MODEL (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  amdtemp_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cpu_id ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amdtemp_probe(device_t dev)
{
	uint32_t family, model;

	if (resource_disabled("amdtemp", 0))
		return (ENXIO);
	if (!amdtemp_match(device_get_parent(dev), NULL))
		return (ENXIO);

	family = CPUID_TO_FAMILY(cpu_id);
	model = CPUID_TO_MODEL(cpu_id);

	switch (family) {
	case 0x0f:
		if ((model == 0x04 && (cpu_id & CPUID_STEPPING) == 0) ||
		    (model == 0x05 && (cpu_id & CPUID_STEPPING) <= 1))
			return (ENXIO);
		break;
	case 0x10:
	case 0x11:
	case 0x12:
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
		break;
	default:
		return (ENXIO);
	}
	device_set_desc(dev, "AMD CPU On-Die Thermal Sensors");

	return (BUS_PROBE_GENERIC);
}