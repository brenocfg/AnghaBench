#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  field_flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  pointer; } ;
struct TYPE_8__ {int attribute; TYPE_2__* region_obj; } ;
union acpi_operand_object {TYPE_5__ common_field; TYPE_4__ buffer; TYPE_3__ field; } ;
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_6__ {int space_id; } ;
struct TYPE_7__ {TYPE_1__ region; } ;

/* Variables and functions */
#define  ACPI_ADR_SPACE_GSBUS 130 
#define  ACPI_ADR_SPACE_IPMI 129 
#define  ACPI_ADR_SPACE_SMBUS 128 
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 int ACPI_IPMI_BUFFER_SIZE ; 
 int ACPI_READ ; 
 int ACPI_SERIAL_HEADER_SIZE ; 
 int ACPI_SMBUS_BUFFER_SIZE ; 
 int /*<<< orphan*/  AE_AML_INVALID_SPACE_ID ; 
 int /*<<< orphan*/  AE_AML_PROTOCOL ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int AML_FIELD_ATTRIB_RAW_PROCESS_BYTES ; 
 int /*<<< orphan*/  acpi_ex_access_region (union acpi_operand_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_ex_acquire_global_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_get_protocol_buffer_length (int,int*) ; 
 int /*<<< orphan*/  acpi_ex_release_global_lock (int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ut_create_buffer_object (int) ; 
 int /*<<< orphan*/  ex_read_serial_bus ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64 ; 

acpi_status
acpi_ex_read_serial_bus(union acpi_operand_object *obj_desc,
			union acpi_operand_object **return_buffer)
{
	acpi_status status;
	u32 buffer_length;
	union acpi_operand_object *buffer_desc;
	u32 function;
	u16 accessor_type;

	ACPI_FUNCTION_TRACE_PTR(ex_read_serial_bus, obj_desc);

	/*
	 * This is an SMBus, GSBus or IPMI read. We must create a buffer to
	 * hold the data and then directly access the region handler.
	 *
	 * Note: SMBus and GSBus protocol value is passed in upper 16-bits
	 * of Function
	 *
	 * Common buffer format:
	 *     Status;    (Byte 0 of the data buffer)
	 *     Length;    (Byte 1 of the data buffer)
	 *     Data[x-1]: (Bytes 2-x of the arbitrary length data buffer)
	 */
	switch (obj_desc->field.region_obj->region.space_id) {
	case ACPI_ADR_SPACE_SMBUS:

		buffer_length = ACPI_SMBUS_BUFFER_SIZE;
		function = ACPI_READ | (obj_desc->field.attribute << 16);
		break;

	case ACPI_ADR_SPACE_IPMI:

		buffer_length = ACPI_IPMI_BUFFER_SIZE;
		function = ACPI_READ;
		break;

	case ACPI_ADR_SPACE_GSBUS:

		accessor_type = obj_desc->field.attribute;
		if (accessor_type == AML_FIELD_ATTRIB_RAW_PROCESS_BYTES) {
			ACPI_ERROR((AE_INFO,
				    "Invalid direct read using bidirectional write-then-read protocol"));

			return_ACPI_STATUS(AE_AML_PROTOCOL);
		}

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
		function = ACPI_READ | (accessor_type << 16);
		break;

	default:
		return_ACPI_STATUS(AE_AML_INVALID_SPACE_ID);
	}

	/* Create the local transfer buffer that is returned to the caller */

	buffer_desc = acpi_ut_create_buffer_object(buffer_length);
	if (!buffer_desc) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/* Lock entire transaction if requested */

	acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

	/* Call the region handler for the write-then-read */

	status = acpi_ex_access_region(obj_desc, 0,
				       ACPI_CAST_PTR(u64,
						     buffer_desc->buffer.
						     pointer), function);
	acpi_ex_release_global_lock(obj_desc->common_field.field_flags);

	*return_buffer = buffer_desc;
	return_ACPI_STATUS(status);
}