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
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
hme_sbus_probe(device_t dev)
{
	const char *name;

	name = ofw_bus_get_name(dev);
	if (strcmp(name, "SUNW,qfe") == 0 ||
	    strcmp(name, "SUNW,hme") == 0) {
		device_set_desc(dev, "Sun HME 10/100 Ethernet");
		return (0);
	}
	return (ENXIO);
}