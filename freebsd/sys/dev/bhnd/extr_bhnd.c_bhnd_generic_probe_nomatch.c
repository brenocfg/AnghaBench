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
struct resource_list {int dummy; } ;
struct bhnd_nomatch {scalar_t__ device; scalar_t__ vendor; scalar_t__ if_verbose; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BHND_COREID_INVALID ; 
 struct resource_list* BUS_GET_RESOURCE_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bhnd_get_core_index (int /*<<< orphan*/ ) ; 
 scalar_t__ bhnd_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_get_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_get_hwrev (int /*<<< orphan*/ ) ; 
 scalar_t__ bhnd_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_get_vendor_name (int /*<<< orphan*/ ) ; 
 struct bhnd_nomatch* bhnd_nomatch_table ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  resource_list_print_type (struct resource_list*,char*,int /*<<< orphan*/ ,char*) ; 

void
bhnd_generic_probe_nomatch(device_t dev, device_t child)
{
	struct resource_list		*rl;
	const struct bhnd_nomatch	*nm;
	bool				 report;

	/* Fetch reporting configuration for this device */
	report = true;
	for (nm = bhnd_nomatch_table; nm->device != BHND_COREID_INVALID; nm++) {
		if (nm->vendor != bhnd_get_vendor(child))
			continue;

		if (nm->device != bhnd_get_device(child))
			continue;

		report = false;
		if (bootverbose && nm->if_verbose)
			report = true;
		break;
	}
	
	if (!report)
		return;

	/* Print the non-matched device info */
	device_printf(dev, "<%s %s, rev %hhu>", bhnd_get_vendor_name(child),
		bhnd_get_device_name(child), bhnd_get_hwrev(child));

	rl = BUS_GET_RESOURCE_LIST(dev, child);
	if (rl != NULL) {
		resource_list_print_type(rl, "mem", SYS_RES_MEMORY, "%#jx");
		resource_list_print_type(rl, "irq", SYS_RES_IRQ, "%#jd");
	}

	printf(" at core %u (no driver attached)\n",
	    bhnd_get_core_index(child));
}