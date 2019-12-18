#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* pointer; } ;
union acpi_operand_object {TYPE_1__ buffer; } ;
typedef  int u8 ;
struct aml_resource_end_tag {int dummy; } ;
struct acpi_walk_state {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_size ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_PTR_DIFF (int*,int*) ; 
 int ACPI_RESOURCE_NAME_END_TAG ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 union acpi_operand_object* acpi_ut_create_buffer_object (int) ; 
 int /*<<< orphan*/  acpi_ut_get_resource_end_tag (union acpi_operand_object*,int**) ; 
 int /*<<< orphan*/  ex_concat_template ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_concat_template(union acpi_operand_object *operand0,
			union acpi_operand_object *operand1,
			union acpi_operand_object **actual_return_desc,
			struct acpi_walk_state *walk_state)
{
	acpi_status status;
	union acpi_operand_object *return_desc;
	u8 *new_buf;
	u8 *end_tag;
	acpi_size length0;
	acpi_size length1;
	acpi_size new_length;

	ACPI_FUNCTION_TRACE(ex_concat_template);

	/*
	 * Find the end_tag descriptor in each resource template.
	 * Note1: returned pointers point TO the end_tag, not past it.
	 * Note2: zero-length buffers are allowed; treated like one end_tag
	 */

	/* Get the length of the first resource template */

	status = acpi_ut_get_resource_end_tag(operand0, &end_tag);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	length0 = ACPI_PTR_DIFF(end_tag, operand0->buffer.pointer);

	/* Get the length of the second resource template */

	status = acpi_ut_get_resource_end_tag(operand1, &end_tag);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	length1 = ACPI_PTR_DIFF(end_tag, operand1->buffer.pointer);

	/* Combine both lengths, minimum size will be 2 for end_tag */

	new_length = length0 + length1 + sizeof(struct aml_resource_end_tag);

	/* Create a new buffer object for the result (with one end_tag) */

	return_desc = acpi_ut_create_buffer_object(new_length);
	if (!return_desc) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/*
	 * Copy the templates to the new buffer, 0 first, then 1 follows. One
	 * end_tag descriptor is copied from Operand1.
	 */
	new_buf = return_desc->buffer.pointer;
	memcpy(new_buf, operand0->buffer.pointer, length0);
	memcpy(new_buf + length0, operand1->buffer.pointer, length1);

	/* Insert end_tag and set the checksum to zero, means "ignore checksum" */

	new_buf[new_length - 1] = 0;
	new_buf[new_length - 2] = ACPI_RESOURCE_NAME_END_TAG | 1;

	/* Return the completed resource template */

	*actual_return_desc = return_desc;
	return_ACPI_STATUS(AE_OK);
}