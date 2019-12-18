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
 scalar_t__ TUMBLER_IICADDR ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ iicbus_get_addr (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
tumbler_probe(device_t dev)
{
	const char *name;

	name = ofw_bus_get_name(dev);
	if (name == NULL)
		return (ENXIO);

	if (strcmp(name, "deq") == 0 && iicbus_get_addr(dev) == 
	    TUMBLER_IICADDR) {
		device_set_desc(dev, "Texas Instruments TAS3001 Audio Codec");
		return (0);
	}

	return (ENXIO);
}