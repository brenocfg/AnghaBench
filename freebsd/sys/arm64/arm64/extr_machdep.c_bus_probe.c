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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_SPCR ; 
 scalar_t__ ARM64_BUS_ACPI ; 
 scalar_t__ ARM64_BUS_FDT ; 
 scalar_t__ ARM64_BUS_NONE ; 
 scalar_t__ OF_peer (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_find_table (int /*<<< orphan*/ ) ; 
 scalar_t__ arm64_bus_method ; 
 int /*<<< orphan*/  freeenv (char*) ; 
 char* kern_getenv (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static bool
bus_probe(void)
{
	bool has_acpi, has_fdt;
	char *order, *env;

	has_acpi = has_fdt = false;

#ifdef FDT
	has_fdt = (OF_peer(0) != 0);
#endif
#ifdef DEV_ACPI
	has_acpi = (acpi_find_table(ACPI_SIG_SPCR) != 0);
#endif

	env = kern_getenv("kern.cfg.order");
	if (env != NULL) {
		order = env;
		while (order != NULL) {
			if (has_acpi &&
			    strncmp(order, "acpi", 4) == 0 &&
			    (order[4] == ',' || order[4] == '\0')) {
				arm64_bus_method = ARM64_BUS_ACPI;
				break;
			}
			if (has_fdt &&
			    strncmp(order, "fdt", 3) == 0 &&
			    (order[3] == ',' || order[3] == '\0')) {
				arm64_bus_method = ARM64_BUS_FDT;
				break;
			}
			order = strchr(order, ',');
		}
		freeenv(env);

		/* If we set the bus method it is valid */
		if (arm64_bus_method != ARM64_BUS_NONE)
			return (true);
	}
	/* If no order or an invalid order was set use the default */
	if (arm64_bus_method == ARM64_BUS_NONE) {
		if (has_fdt)
			arm64_bus_method = ARM64_BUS_FDT;
		else if (has_acpi)
			arm64_bus_method = ARM64_BUS_ACPI;
	}

	/*
	 * If no option was set the default is valid, otherwise we are
	 * setting one to get cninit() working, then calling panic to tell
	 * the user about the invalid bus setup.
	 */
	return (env == NULL);
}