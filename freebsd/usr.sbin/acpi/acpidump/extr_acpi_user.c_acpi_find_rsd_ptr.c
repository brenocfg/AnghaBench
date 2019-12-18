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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  addr ;
typedef  int /*<<< orphan*/  ACPI_TABLE_RSDP ;

/* Variables and functions */
 int /*<<< orphan*/  KENV_GET ; 
 int /*<<< orphan*/ * acpi_get_rsdp (scalar_t__) ; 
 int /*<<< orphan*/ * acpi_scan_rsd_ptr () ; 
 int /*<<< orphan*/  acpi_user_init () ; 
 int /*<<< orphan*/  hint_acpi_0_rsdp ; 
 scalar_t__ kenv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  machdep_acpi_root ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlbyname (int /*<<< orphan*/ ,scalar_t__*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ACPI_TABLE_RSDP *
acpi_find_rsd_ptr(void)
{
	ACPI_TABLE_RSDP *rsdp;
	char		buf[20];
	u_long		addr;
	size_t		len;

	acpi_user_init();

	addr = 0;

	/* Attempt to use kenv or sysctl to find RSD PTR record. */
	if (kenv(KENV_GET, hint_acpi_0_rsdp, buf, 20) > 0)
		addr = strtoul(buf, NULL, 0);
	if (addr == 0) {
		len = sizeof(addr);
		if (sysctlbyname(machdep_acpi_root, &addr, &len, NULL, 0) != 0)
			addr = 0;
	}
	if (addr != 0 && (rsdp = acpi_get_rsdp(addr)) != NULL)
		return (rsdp);

	return (acpi_scan_rsd_ptr());
}