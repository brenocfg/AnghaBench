#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* platform_t ;
typedef  int /*<<< orphan*/  phandle_t ;
struct TYPE_6__ {char* fdt_compatible; } ;
struct TYPE_5__ {int /*<<< orphan*/ * cls; } ;

/* Variables and functions */
 TYPE_3__* FDT_PLATFORM (TYPE_1__*) ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 scalar_t__ ofw_bus_node_is_compatible (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
fdt_platform_probe(platform_t plat)
{
	const char *compat;
	phandle_t root;

	/*
	 * TODO: Make these KASSERTs, we should only be here if we
	 * are using the FDT platform magic.
	 */
	if (plat->cls == NULL || FDT_PLATFORM(plat) == NULL)
		return 1;

	/* Is the device is compatible? */
	root = OF_finddevice("/");
	compat = FDT_PLATFORM(plat)->fdt_compatible;
	if (ofw_bus_node_is_compatible(root, compat) != 0)
		return 0;

	/* Not compatible, return an error */
	return 1;
}