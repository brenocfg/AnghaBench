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
struct TYPE_7__ {size_t length; int /*<<< orphan*/ * pointer; } ;
struct TYPE_6__ {int /*<<< orphan*/  pointer; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
struct TYPE_8__ {int type; } ;
union acpi_operand_object {TYPE_3__ buffer; TYPE_2__ string; TYPE_1__ integer; TYPE_4__ common; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  size_t acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IMPLICIT_CONVERT_HEX ; 
#define  ACPI_TYPE_BUFFER 129 
#define  ACPI_TYPE_INTEGER 128 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ex_convert_to_string (union acpi_operand_object*,union acpi_operand_object**,int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ut_create_string_object (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

acpi_status
acpi_ns_convert_to_string(union acpi_operand_object *original_object,
			  union acpi_operand_object **return_object)
{
	union acpi_operand_object *new_object;
	acpi_size length;
	acpi_status status;

	switch (original_object->common.type) {
	case ACPI_TYPE_INTEGER:
		/*
		 * Integer-to-String conversion. Commonly, convert
		 * an integer of value 0 to a NULL string. The last element of
		 * _BIF and _BIX packages occasionally need this fix.
		 */
		if (original_object->integer.value == 0) {

			/* Allocate a new NULL string object */

			new_object = acpi_ut_create_string_object(0);
			if (!new_object) {
				return (AE_NO_MEMORY);
			}
		} else {
			status = acpi_ex_convert_to_string(original_object,
							   &new_object,
							   ACPI_IMPLICIT_CONVERT_HEX);
			if (ACPI_FAILURE(status)) {
				return (status);
			}
		}
		break;

	case ACPI_TYPE_BUFFER:
		/*
		 * Buffer-to-String conversion. Use a to_string
		 * conversion, no transform performed on the buffer data. The best
		 * example of this is the _BIF method, where the string data from
		 * the battery is often (incorrectly) returned as buffer object(s).
		 */
		length = 0;
		while ((length < original_object->buffer.length) &&
		       (original_object->buffer.pointer[length])) {
			length++;
		}

		/* Allocate a new string object */

		new_object = acpi_ut_create_string_object(length);
		if (!new_object) {
			return (AE_NO_MEMORY);
		}

		/*
		 * Copy the raw buffer data with no transform. String is already NULL
		 * terminated at Length+1.
		 */
		memcpy(new_object->string.pointer,
		       original_object->buffer.pointer, length);
		break;

	default:

		return (AE_AML_OPERAND_TYPE);
	}

	*return_object = new_object;
	return (AE_OK);
}