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
typedef  union acpi_parse_object {int dummy; } acpi_parse_object ;
struct acpi_parse_state {TYPE_2__* scope; } ;
struct TYPE_3__ {union acpi_parse_object* op; } ;
struct TYPE_4__ {TYPE_1__ parse_scope; } ;

/* Variables and functions */

union acpi_parse_object *acpi_ps_get_parent_scope(struct acpi_parse_state
						  *parser_state)
{

	return (parser_state->scope->parse_scope.op);
}