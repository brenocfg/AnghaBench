#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  field_flags; } ;
struct TYPE_7__ {scalar_t__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  bit_length; int /*<<< orphan*/  pin_number_index; } ;
struct TYPE_5__ {scalar_t__ type; } ;
union acpi_operand_object {TYPE_4__ common_field; TYPE_3__ integer; TYPE_2__ field; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_BFIELD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_WRITE ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  acpi_ex_access_region (union acpi_operand_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_acquire_global_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_release_global_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (scalar_t__) ; 
 int /*<<< orphan*/  ex_write_gpio ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_write_gpio(union acpi_operand_object *source_desc,
		   union acpi_operand_object *obj_desc,
		   union acpi_operand_object **return_buffer)
{
	acpi_status status;
	void *buffer;

	ACPI_FUNCTION_TRACE_PTR(ex_write_gpio, obj_desc);

	/*
	 * For GPIO (general_purpose_io), we will bypass the entire field
	 * mechanism and handoff the bit address and bit width directly to
	 * the handler. The Address will be the bit offset
	 * from the previous Connection() operator, making it effectively a
	 * pin number index. The bit_length is the length of the field, which
	 * is thus the number of pins.
	 */
	if (source_desc->common.type != ACPI_TYPE_INTEGER) {
		return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	}

	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "GPIO FieldWrite [FROM]: (%s:%X), Value %.8X  [TO]: Pin %u Bits %u\n",
			  acpi_ut_get_type_name(source_desc->common.type),
			  source_desc->common.type,
			  (u32)source_desc->integer.value,
			  obj_desc->field.pin_number_index,
			  obj_desc->field.bit_length));

	buffer = &source_desc->integer.value;

	/* Lock entire transaction if requested */

	acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

	/* Perform the write */

	status = acpi_ex_access_region(obj_desc, 0, (u64 *)buffer, ACPI_WRITE);
	acpi_ex_release_global_lock(obj_desc->common_field.field_flags);
	return_ACPI_STATUS(status);
}