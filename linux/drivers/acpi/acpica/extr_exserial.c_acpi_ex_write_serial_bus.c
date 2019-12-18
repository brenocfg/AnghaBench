#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  field_flags; } ;
struct TYPE_11__ {scalar_t__ length; void* pointer; } ;
struct TYPE_10__ {int attribute; TYPE_3__* region_obj; } ;
struct TYPE_7__ {scalar_t__ type; } ;
union acpi_operand_object {TYPE_6__ common_field; TYPE_5__ buffer; TYPE_4__ field; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_8__ {int space_id; } ;
struct TYPE_9__ {TYPE_2__ region; } ;

/* Variables and functions */
#define  ACPI_ADR_SPACE_GSBUS 130 
#define  ACPI_ADR_SPACE_IPMI 129 
#define  ACPI_ADR_SPACE_SMBUS 128 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 scalar_t__ ACPI_IPMI_BUFFER_SIZE ; 
 int /*<<< orphan*/  ACPI_SERIAL_HEADER_SIZE ; 
 scalar_t__ ACPI_SMBUS_BUFFER_SIZE ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int ACPI_WRITE ; 
 int /*<<< orphan*/  AE_AML_INVALID_SPACE_ID ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  acpi_ex_access_region (union acpi_operand_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  acpi_ex_acquire_global_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_get_protocol_buffer_length (int,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_ex_release_global_lock (int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ut_create_buffer_object (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_write_serial_bus ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_write_serial_bus(union acpi_operand_object *source_desc,
			 union acpi_operand_object *obj_desc,
			 union acpi_operand_object **return_buffer)
{
	acpi_status status;
	u32 buffer_length;
	u32 data_length;
	void *buffer;
	union acpi_operand_object *buffer_desc;
	u32 function;
	u16 accessor_type;

	ACPI_FUNCTION_TRACE_PTR(ex_write_serial_bus, obj_desc);

	/*
	 * This is an SMBus, GSBus or IPMI write. We will bypass the entire
	 * field mechanism and handoff the buffer directly to the handler.
	 * For these address spaces, the buffer is bidirectional; on a
	 * write, return data is returned in the same buffer.
	 *
	 * Source must be a buffer of sufficient size, these are fixed size:
	 * ACPI_SMBUS_BUFFER_SIZE, or ACPI_IPMI_BUFFER_SIZE.
	 *
	 * Note: SMBus and GSBus protocol type is passed in upper 16-bits
	 * of Function
	 *
	 * Common buffer format:
	 *     Status;    (Byte 0 of the data buffer)
	 *     Length;    (Byte 1 of the data buffer)
	 *     Data[x-1]: (Bytes 2-x of the arbitrary length data buffer)
	 */
	if (source_desc->common.type != ACPI_TYPE_BUFFER) {
		ACPI_ERROR((AE_INFO,
			    "SMBus/IPMI/GenericSerialBus write requires "
			    "Buffer, found type %s",
			    acpi_ut_get_object_type_name(source_desc)));

		return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	}

	switch (obj_desc->field.region_obj->region.space_id) {
	case ACPI_ADR_SPACE_SMBUS:

		buffer_length = ACPI_SMBUS_BUFFER_SIZE;
		function = ACPI_WRITE | (obj_desc->field.attribute << 16);
		break;

	case ACPI_ADR_SPACE_IPMI:

		buffer_length = ACPI_IPMI_BUFFER_SIZE;
		function = ACPI_WRITE;
		break;

	case ACPI_ADR_SPACE_GSBUS:

		accessor_type = obj_desc->field.attribute;
		status =
		    acpi_ex_get_protocol_buffer_length(accessor_type,
						       &buffer_length);
		if (ACPI_FAILURE(status)) {
			ACPI_ERROR((AE_INFO,
				    "Invalid protocol ID for GSBus: 0x%4.4X",
				    accessor_type));

			return_ACPI_STATUS(status);
		}

		/* Add header length to get the full size of the buffer */

		buffer_length += ACPI_SERIAL_HEADER_SIZE;
		function = ACPI_WRITE | (accessor_type << 16);
		break;

	default:
		return_ACPI_STATUS(AE_AML_INVALID_SPACE_ID);
	}

	/* Create the transfer/bidirectional/return buffer */

	buffer_desc = acpi_ut_create_buffer_object(buffer_length);
	if (!buffer_desc) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/* Copy the input buffer data to the transfer buffer */

	buffer = buffer_desc->buffer.pointer;
	data_length = (buffer_length < source_desc->buffer.length ?
		       buffer_length : source_desc->buffer.length);
	memcpy(buffer, source_desc->buffer.pointer, data_length);

	/* Lock entire transaction if requested */

	acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

	/*
	 * Perform the write (returns status and perhaps data in the
	 * same buffer)
	 */
	status = acpi_ex_access_region(obj_desc, 0, (u64 *)buffer, function);
	acpi_ex_release_global_lock(obj_desc->common_field.field_flags);

	*return_buffer = buffer_desc;
	return_ACPI_STATUS(status);
}