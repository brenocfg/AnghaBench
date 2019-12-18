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
 int /*<<< orphan*/  OFW_TYPE_PCI ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * schizo_get_desc (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
schizo_probe(device_t dev)
{
	const char *dtype;

	dtype = ofw_bus_get_type(dev);
	if (dtype != NULL && strcmp(dtype, OFW_TYPE_PCI) == 0 &&
	    schizo_get_desc(dev) != NULL) {
		device_set_desc(dev, "Sun Host-PCI bridge");
		return (0);
	}
	return (ENXIO);
}