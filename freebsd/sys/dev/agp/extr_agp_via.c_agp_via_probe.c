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
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 char* agp_via_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_via_probe(device_t dev)
{
	const char *desc;

	if (resource_disabled("agp", device_get_unit(dev)))
		return (ENXIO);
	desc = agp_via_match(dev);
	if (desc) {
		device_set_desc(dev, desc);
		return BUS_PROBE_DEFAULT;
	}

	return ENXIO;
}