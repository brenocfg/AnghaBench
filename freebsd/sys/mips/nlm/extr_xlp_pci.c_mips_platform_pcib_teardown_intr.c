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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,void*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
mips_platform_pcib_teardown_intr(device_t dev, device_t child,
    struct resource *irq, void *cookie)
{
	if (strcmp(device_get_name(child), "pci") == 0) {
		/* if needed reprogram the pic to clear pcix related entry */
		device_printf(dev, "teardown intr\n");
	}
	return (bus_generic_teardown_intr(dev, child, irq, cookie));
}