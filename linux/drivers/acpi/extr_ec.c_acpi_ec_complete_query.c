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
struct acpi_ec {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EC_COMMAND_QUERY ; 
 int /*<<< orphan*/  EC_FLAGS_QUERY_PENDING ; 
 int /*<<< orphan*/  acpi_ec_cmd_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ec_unmask_gpe (struct acpi_ec*) ; 
 int /*<<< orphan*/  ec_dbg_evt (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_ec_complete_query(struct acpi_ec *ec)
{
	if (test_and_clear_bit(EC_FLAGS_QUERY_PENDING, &ec->flags))
		ec_dbg_evt("Command(%s) unblocked",
			   acpi_ec_cmd_string(ACPI_EC_COMMAND_QUERY));
	acpi_ec_unmask_gpe(ec);
}