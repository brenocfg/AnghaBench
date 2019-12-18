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
struct TYPE_4__ {scalar_t__ type; union acpi_operand_object* next_object; } ;
struct TYPE_3__ {scalar_t__ handler; void* pointer; } ;
union acpi_operand_object {TYPE_2__ common; TYPE_1__ data; } ;
struct acpi_namespace_node {union acpi_operand_object* object; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_object_handler ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_LOCAL_DATA ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_OK ; 

acpi_status
acpi_ns_get_attached_data(struct acpi_namespace_node *node,
			  acpi_object_handler handler, void **data)
{
	union acpi_operand_object *obj_desc;

	obj_desc = node->object;
	while (obj_desc) {
		if ((obj_desc->common.type == ACPI_TYPE_LOCAL_DATA) &&
		    (obj_desc->data.handler == handler)) {
			*data = obj_desc->data.pointer;
			return (AE_OK);
		}

		obj_desc = obj_desc->common.next_object;
	}

	return (AE_NOT_FOUND);
}