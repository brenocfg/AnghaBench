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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUS_PROBE_GENERIC ; 
 int CPUID_TO_FAMILY (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  amdsmn_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_id ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
amdsmn_probe(device_t dev)
{
	uint32_t family;
	char buf[64];

	if (resource_disabled("amdsmn", 0))
		return (ENXIO);
	if (!amdsmn_match(device_get_parent(dev), NULL))
		return (ENXIO);

	family = CPUID_TO_FAMILY(cpu_id);

	switch (family) {
	case 0x15:
	case 0x17:
		break;
	default:
		return (ENXIO);
	}
	snprintf(buf, sizeof(buf), "AMD Family %xh System Management Network",
	    family);
	device_set_desc_copy(dev, buf);

	return (BUS_PROBE_GENERIC);
}