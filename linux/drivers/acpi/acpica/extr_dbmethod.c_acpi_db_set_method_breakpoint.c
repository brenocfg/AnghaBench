#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  aml; } ;
union acpi_parse_object {TYPE_1__ common; } ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  aml_start; } ;
struct acpi_walk_state {scalar_t__ user_breakpoint; TYPE_2__ parser_state; } ;

/* Variables and functions */
 scalar_t__ ACPI_PTR_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 

void
acpi_db_set_method_breakpoint(char *location,
			      struct acpi_walk_state *walk_state,
			      union acpi_parse_object *op)
{
	u32 address;
	u32 aml_offset;

	if (!op) {
		acpi_os_printf("There is no method currently executing\n");
		return;
	}

	/* Get and verify the breakpoint address */

	address = strtoul(location, NULL, 16);
	aml_offset = (u32)ACPI_PTR_DIFF(op->common.aml,
					walk_state->parser_state.aml_start);
	if (address <= aml_offset) {
		acpi_os_printf("Breakpoint %X is beyond current address %X\n",
			       address, aml_offset);
	}

	/* Save breakpoint in current walk */

	walk_state->user_breakpoint = address;
	acpi_os_printf("Breakpoint set at AML offset %X\n", address);
}