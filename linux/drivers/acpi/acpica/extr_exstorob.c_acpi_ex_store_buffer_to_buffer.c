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
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/  flags; int /*<<< orphan*/  pointer; } ;
union acpi_operand_object {TYPE_2__ common; TYPE_1__ buffer; } ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_CAST_PTR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_STATIC_POINTER ; 
 int buffer ; 
 int /*<<< orphan*/  ex_store_buffer_to_buffer ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ original_src_type ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int u8 ; 

acpi_status
acpi_ex_store_buffer_to_buffer(union acpi_operand_object *source_desc,
			       union acpi_operand_object *target_desc)
{
	u32 length;
	u8 *buffer;

	ACPI_FUNCTION_TRACE_PTR(ex_store_buffer_to_buffer, source_desc);

	/* If Source and Target are the same, just return */

	if (source_desc == target_desc) {
		return_ACPI_STATUS(AE_OK);
	}

	/* We know that source_desc is a buffer by now */

	buffer = ACPI_CAST_PTR(u8, source_desc->buffer.pointer);
	length = source_desc->buffer.length;

	/*
	 * If target is a buffer of length zero or is a static buffer,
	 * allocate a new buffer of the proper length
	 */
	if ((target_desc->buffer.length == 0) ||
	    (target_desc->common.flags & AOPOBJ_STATIC_POINTER)) {
		target_desc->buffer.pointer = ACPI_ALLOCATE(length);
		if (!target_desc->buffer.pointer) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		target_desc->buffer.length = length;
	}

	/* Copy source buffer to target buffer */

	if (length <= target_desc->buffer.length) {

		/* Clear existing buffer and copy in the new one */

		memset(target_desc->buffer.pointer, 0,
		       target_desc->buffer.length);
		memcpy(target_desc->buffer.pointer, buffer, length);

#ifdef ACPI_OBSOLETE_BEHAVIOR
		/*
		 * NOTE: ACPI versions up to 3.0 specified that the buffer must be
		 * truncated if the string is smaller than the buffer. However, "other"
		 * implementations of ACPI never did this and thus became the defacto
		 * standard. ACPI 3.0A changes this behavior such that the buffer
		 * is no longer truncated.
		 */

		/*
		 * OBSOLETE BEHAVIOR:
		 * If the original source was a string, we must truncate the buffer,
		 * according to the ACPI spec. Integer-to-Buffer and Buffer-to-Buffer
		 * copy must not truncate the original buffer.
		 */
		if (original_src_type == ACPI_TYPE_STRING) {

			/* Set the new length of the target */

			target_desc->buffer.length = length;
		}
#endif
	} else {
		/* Truncate the source, copy only what will fit */

		memcpy(target_desc->buffer.pointer, buffer,
		       target_desc->buffer.length);

		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Truncating source buffer from %X to %X\n",
				  length, target_desc->buffer.length));
	}

	/* Copy flags */

	target_desc->buffer.flags = source_desc->buffer.flags;
	target_desc->common.flags &= ~AOPOBJ_STATIC_POINTER;
	return_ACPI_STATUS(AE_OK);
}