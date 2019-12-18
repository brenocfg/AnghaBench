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
struct TYPE_4__ {int /*<<< orphan*/  arg; } ;
struct TYPE_3__ {int /*<<< orphan*/  next; int /*<<< orphan*/  parent; TYPE_2__ value; int /*<<< orphan*/  aml_opcode; } ;
union acpi_parse_object {TYPE_1__ common; } ;
struct acpi_opcode_info {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEBUG_ONLY_MEMBERS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 struct acpi_opcode_info* acpi_ps_get_opcode_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_db_dump_parser_descriptor(union acpi_parse_object *op)
{
	const struct acpi_opcode_info *info;

	info = acpi_ps_get_opcode_info(op->common.aml_opcode);

	acpi_os_printf("Parser Op Descriptor:\n");
	acpi_os_printf("%20.20s : %4.4X\n", "Opcode", op->common.aml_opcode);

	ACPI_DEBUG_ONLY_MEMBERS(acpi_os_printf("%20.20s : %s\n", "Opcode Name",
					       info->name));

	acpi_os_printf("%20.20s : %p\n", "Value/ArgList", op->common.value.arg);
	acpi_os_printf("%20.20s : %p\n", "Parent", op->common.parent);
	acpi_os_printf("%20.20s : %p\n", "NextOp", op->common.next);
}