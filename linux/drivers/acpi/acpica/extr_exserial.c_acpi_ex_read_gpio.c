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
struct TYPE_4__ {int /*<<< orphan*/  field_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  bit_length; int /*<<< orphan*/  pin_number_index; } ;
union acpi_operand_object {TYPE_2__ common_field; TYPE_1__ field; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_BFIELD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 int /*<<< orphan*/  ACPI_READ ; 
 int /*<<< orphan*/  acpi_ex_access_region (union acpi_operand_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_acquire_global_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_release_global_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_read_gpio ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_read_gpio(union acpi_operand_object *obj_desc, void *buffer)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ex_read_gpio, obj_desc);

	/*
	 * For GPIO (general_purpose_io), the Address will be the bit offset
	 * from the previous Connection() operator, making it effectively a
	 * pin number index. The bit_length is the length of the field, which
	 * is thus the number of pins.
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "GPIO FieldRead [FROM]:  Pin %u Bits %u\n",
			  obj_desc->field.pin_number_index,
			  obj_desc->field.bit_length));

	/* Lock entire transaction if requested */

	acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

	/* Perform the read */

	status = acpi_ex_access_region(obj_desc, 0, (u64 *)buffer, ACPI_READ);

	acpi_ex_release_global_lock(obj_desc->common_field.field_flags);
	return_ACPI_STATUS(status);
}