#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; TYPE_3__* next_object; } ;
union acpi_operand_object {TYPE_2__ common; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_6__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 scalar_t__ ACPI_TYPE_LOCAL_DATA ; 
 int /*<<< orphan*/  ns_get_secondary_object ; 
 int /*<<< orphan*/  return_PTR (TYPE_3__*) ; 

union acpi_operand_object *acpi_ns_get_secondary_object(union
							acpi_operand_object
							*obj_desc)
{
	ACPI_FUNCTION_TRACE_PTR(ns_get_secondary_object, obj_desc);

	if ((!obj_desc) ||
	    (obj_desc->common.type == ACPI_TYPE_LOCAL_DATA) ||
	    (!obj_desc->common.next_object) ||
	    ((obj_desc->common.next_object)->common.type ==
	     ACPI_TYPE_LOCAL_DATA)) {
		return_PTR(NULL);
	}

	return_PTR(obj_desc->common.next_object);
}