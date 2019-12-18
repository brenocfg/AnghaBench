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
struct TYPE_2__ {char* pointer; scalar_t__ length; } ;
union acpi_operand_object {TYPE_1__ string; } ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 char* ACPI_ALLOCATE_ZEROED (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_U32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  AE_INFO ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  return_PTR (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ut_create_string_object ; 

union acpi_operand_object *acpi_ut_create_string_object(acpi_size string_size)
{
	union acpi_operand_object *string_desc;
	char *string;

	ACPI_FUNCTION_TRACE_U32(ut_create_string_object, string_size);

	/* Create a new String object */

	string_desc = acpi_ut_create_internal_object(ACPI_TYPE_STRING);
	if (!string_desc) {
		return_PTR(NULL);
	}

	/*
	 * Allocate the actual string buffer -- (Size + 1) for NULL terminator.
	 * NOTE: Zero-length strings are NULL terminated
	 */
	string = ACPI_ALLOCATE_ZEROED(string_size + 1);
	if (!string) {
		ACPI_ERROR((AE_INFO, "Could not allocate size %u",
			    (u32)string_size));

		acpi_ut_remove_reference(string_desc);
		return_PTR(NULL);
	}

	/* Complete string object initialization */

	string_desc->string.pointer = string;
	string_desc->string.length = (u32) string_size;

	/* Return the new string descriptor */

	return_PTR(string_desc);
}