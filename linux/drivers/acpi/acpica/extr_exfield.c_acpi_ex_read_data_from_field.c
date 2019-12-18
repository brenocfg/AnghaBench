#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  field_flags; int /*<<< orphan*/  base_byte_offset; int /*<<< orphan*/  start_field_bit_offset; int /*<<< orphan*/  bit_length; } ;
struct TYPE_15__ {scalar_t__ type; int flags; } ;
struct TYPE_14__ {int /*<<< orphan*/  bit_length; scalar_t__ base_byte_offset; TYPE_5__* region_obj; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
struct TYPE_9__ {void* pointer; } ;
union acpi_operand_object {TYPE_8__ common_field; TYPE_7__ common; TYPE_6__ field; TYPE_2__ integer; TYPE_1__ buffer; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct acpi_walk_state {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;
struct TYPE_12__ {scalar_t__ internal_pcc_buffer; } ;
struct TYPE_11__ {scalar_t__ space_id; } ;
struct TYPE_13__ {TYPE_4__ field; TYPE_3__ region; } ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_GPIO ; 
 scalar_t__ ACPI_ADR_SPACE_GSBUS ; 
 scalar_t__ ACPI_ADR_SPACE_IPMI ; 
 scalar_t__ ACPI_ADR_SPACE_PLATFORM_COMM ; 
 scalar_t__ ACPI_ADR_SPACE_SMBUS ; 
 int /*<<< orphan*/  ACPI_DB_BFIELD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 scalar_t__ ACPI_ROUND_BITS_UP_TO_BYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER_FIELD ; 
 scalar_t__ ACPI_TYPE_LOCAL_REGION_FIELD ; 
 int /*<<< orphan*/  AE_AML_NO_OPERAND ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  acpi_ds_get_buffer_field_arguments (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ex_acquire_global_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_extract_from_field (union acpi_operand_object*,void*,scalar_t__) ; 
 int /*<<< orphan*/  acpi_ex_read_gpio (union acpi_operand_object*,void*) ; 
 int /*<<< orphan*/  acpi_ex_read_serial_bus (union acpi_operand_object*,union acpi_operand_object**) ; 
 int /*<<< orphan*/  acpi_ex_release_global_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_gbl_integer_byte_width ; 
 union acpi_operand_object* acpi_ut_create_buffer_object (scalar_t__) ; 
 union acpi_operand_object* acpi_ut_create_integer_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_read_data_from_field ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_read_data_from_field(struct acpi_walk_state *walk_state,
			     union acpi_operand_object *obj_desc,
			     union acpi_operand_object **ret_buffer_desc)
{
	acpi_status status;
	union acpi_operand_object *buffer_desc;
	void *buffer;
	u32 buffer_length;

	ACPI_FUNCTION_TRACE_PTR(ex_read_data_from_field, obj_desc);

	/* Parameter validation */

	if (!obj_desc) {
		return_ACPI_STATUS(AE_AML_NO_OPERAND);
	}
	if (!ret_buffer_desc) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	if (obj_desc->common.type == ACPI_TYPE_BUFFER_FIELD) {
		/*
		 * If the buffer_field arguments have not been previously evaluated,
		 * evaluate them now and save the results.
		 */
		if (!(obj_desc->common.flags & AOPOBJ_DATA_VALID)) {
			status = acpi_ds_get_buffer_field_arguments(obj_desc);
			if (ACPI_FAILURE(status)) {
				return_ACPI_STATUS(status);
			}
		}
	} else if ((obj_desc->common.type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
		   (obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_SMBUS
		    || obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_GSBUS
		    || obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_IPMI)) {

		/* SMBus, GSBus, IPMI serial */

		status = acpi_ex_read_serial_bus(obj_desc, ret_buffer_desc);
		return_ACPI_STATUS(status);
	}

	/*
	 * Allocate a buffer for the contents of the field.
	 *
	 * If the field is larger than the current integer width, create
	 * a BUFFER to hold it. Otherwise, use an INTEGER. This allows
	 * the use of arithmetic operators on the returned value if the
	 * field size is equal or smaller than an Integer.
	 *
	 * Note: Field.length is in bits.
	 */
	buffer_length =
	    (acpi_size)ACPI_ROUND_BITS_UP_TO_BYTES(obj_desc->field.bit_length);

	if (buffer_length > acpi_gbl_integer_byte_width) {

		/* Field is too large for an Integer, create a Buffer instead */

		buffer_desc = acpi_ut_create_buffer_object(buffer_length);
		if (!buffer_desc) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}
		buffer = buffer_desc->buffer.pointer;
	} else {
		/* Field will fit within an Integer (normal case) */

		buffer_desc = acpi_ut_create_integer_object((u64) 0);
		if (!buffer_desc) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		buffer_length = acpi_gbl_integer_byte_width;
		buffer = &buffer_desc->integer.value;
	}

	if ((obj_desc->common.type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
	    (obj_desc->field.region_obj->region.space_id ==
	     ACPI_ADR_SPACE_GPIO)) {

		/* General Purpose I/O */

		status = acpi_ex_read_gpio(obj_desc, buffer);
		goto exit;
	} else if ((obj_desc->common.type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
		   (obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_PLATFORM_COMM)) {
		/*
		 * Reading from a PCC field unit does not require the handler because
		 * it only requires reading from the internal_pcc_buffer.
		 */
		ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
				  "PCC FieldRead bits %u\n",
				  obj_desc->field.bit_length));

		memcpy(buffer,
		       obj_desc->field.region_obj->field.internal_pcc_buffer +
		       obj_desc->field.base_byte_offset,
		       (acpi_size)ACPI_ROUND_BITS_UP_TO_BYTES(obj_desc->field.
							      bit_length));

		*ret_buffer_desc = buffer_desc;
		return AE_OK;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "FieldRead [TO]:   Obj %p, Type %X, Buf %p, ByteLen %X\n",
			  obj_desc, obj_desc->common.type, buffer,
			  buffer_length));
	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "FieldRead [FROM]: BitLen %X, BitOff %X, ByteOff %X\n",
			  obj_desc->common_field.bit_length,
			  obj_desc->common_field.start_field_bit_offset,
			  obj_desc->common_field.base_byte_offset));

	/* Lock entire transaction if requested */

	acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

	/* Read from the field */

	status = acpi_ex_extract_from_field(obj_desc, buffer, buffer_length);
	acpi_ex_release_global_lock(obj_desc->common_field.field_flags);

exit:
	if (ACPI_FAILURE(status)) {
		acpi_ut_remove_reference(buffer_desc);
	} else {
		*ret_buffer_desc = buffer_desc;
	}

	return_ACPI_STATUS(status);
}