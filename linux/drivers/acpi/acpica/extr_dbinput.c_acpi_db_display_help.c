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
struct acpi_db_command_help {int /*<<< orphan*/  description; scalar_t__ invocation; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_db_display_command_info (char*,int /*<<< orphan*/ ) ; 
 struct acpi_db_command_help* acpi_gbl_db_command_help ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 

__attribute__((used)) static void acpi_db_display_help(char *command)
{
	const struct acpi_db_command_help *next = acpi_gbl_db_command_help;

	if (!command) {

		/* No argument to help, display help for all commands */

		acpi_os_printf("\nSummary of AML Debugger Commands\n\n");

		while (next->invocation) {
			acpi_os_printf("%-38s%s", next->invocation,
				       next->description);
			next++;
		}
		acpi_os_printf("\n");

	} else {
		/* Display help for all commands that match the subtring */

		acpi_db_display_command_info(command, TRUE);
	}
}