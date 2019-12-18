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
typedef  int /*<<< orphan*/ * psci_callfn_t ;

/* Variables and functions */
 int PSCI_MISSING ; 
 int PSCI_RETVAL_SUCCESS ; 
 scalar_t__ USE_ACPI ; 
 scalar_t__ USE_FDT ; 
 int psci_acpi_callfn (int /*<<< orphan*/ **) ; 
 int psci_fdt_callfn (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
psci_find_callfn(psci_callfn_t *callfn)
{
	int error;

	*callfn = NULL;
#ifdef FDT
	if (USE_FDT) {
		error = psci_fdt_callfn(callfn);
		if (error != 0)
			return (error);
	}
#endif
#ifdef DEV_ACPI
	if (*callfn == NULL && USE_ACPI) {
		error = psci_acpi_callfn(callfn);
		if (error != 0)
			return (error);
	}
#endif

	if (*callfn == NULL)
		return (PSCI_MISSING);

	return (PSCI_RETVAL_SUCCESS);
}