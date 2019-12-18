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
 int /*<<< orphan*/  ACPI_DEBUG_DEFAULT ; 
 int /*<<< orphan*/  AcpiDbgLevel ; 
 int /*<<< orphan*/  AcpiGbl_EnableInterpreterSlack ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  aml_simulation_regdump (char*) ; 
 int /*<<< orphan*/  aml_simulation_regload (char*) ; 
 scalar_t__ load_dsdt (char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char *argv[])
{
	char	*progname;

	progname = argv[0];

	if (argc == 1) {
		usage(progname);
	}

	AcpiDbgLevel = ACPI_DEBUG_DEFAULT;

	/*
	 * Match kernel options for the interpreter.  Global variable names
	 * can be found in acglobal.h.
	 */
	AcpiGbl_EnableInterpreterSlack = TRUE;

	aml_simulation_regload("region.ini");
	if (load_dsdt(argv[1]) == 0) {
		aml_simulation_regdump("region.dmp");
	}

	return (0);
}