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
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int
esp_probe(device_t dev)
{
	const char *name;

	name = ofw_bus_get_name(dev);
	if (strcmp("SUNW,fas", name) == 0) {
		device_set_desc(dev, "Sun FAS366 Fast-Wide SCSI");
	        return (BUS_PROBE_DEFAULT);
	} else if (strcmp("esp", name) == 0) {
		device_set_desc(dev, "Sun ESP SCSI/Sun FAS Fast-SCSI");
	        return (BUS_PROBE_DEFAULT);
	}

	return (ENXIO);
}