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
 scalar_t__ SNAPPER_IICADDR ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ iicbus_get_addr (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
snapper_probe(device_t dev)
{
	const char *name, *compat;

	name = ofw_bus_get_name(dev);
	if (name == NULL)
		return (ENXIO);

	if (strcmp(name, "deq") == 0) {
		if (iicbus_get_addr(dev) != SNAPPER_IICADDR)
			return (ENXIO);
	} else if (strcmp(name, "codec") == 0) {
		compat = ofw_bus_get_compat(dev);
		if (compat == NULL || strcmp(compat, "tas3004") != 0)
			return (ENXIO);
	} else {
		return (ENXIO);
	}

	device_set_desc(dev, "Texas Instruments TAS3004 Audio Codec");
	return (0);
}