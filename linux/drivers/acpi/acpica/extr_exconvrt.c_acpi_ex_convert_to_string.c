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
struct TYPE_8__ {char* pointer; size_t length; } ;
struct TYPE_7__ {size_t length; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int type; } ;
union acpi_operand_object {TYPE_4__ buffer; TYPE_3__ string; TYPE_2__ integer; TYPE_1__ common; } ;
typedef  char u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
#define  ACPI_EXPLICIT_CONVERT_DECIMAL 133 
#define  ACPI_EXPLICIT_CONVERT_HEX 132 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
#define  ACPI_IMPLICIT_CONVERT_HEX 131 
 size_t ACPI_MAX_DECIMAL_DIGITS ; 
 size_t ACPI_MUL_2 (int) ; 
#define  ACPI_TYPE_BUFFER 130 
#define  ACPI_TYPE_INTEGER 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 size_t acpi_ex_convert_to_ascii (int /*<<< orphan*/ ,int,char*,int) ; 
 int acpi_gbl_integer_byte_width ; 
 union acpi_operand_object* acpi_ut_create_string_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_convert_to_string ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_convert_to_string(union acpi_operand_object * obj_desc,
			  union acpi_operand_object ** result_desc, u32 type)
{
	union acpi_operand_object *return_desc;
	u8 *new_buf;
	u32 i;
	u32 string_length = 0;
	u16 base = 16;
	u8 separator = ',';

	ACPI_FUNCTION_TRACE_PTR(ex_convert_to_string, obj_desc);

	switch (obj_desc->common.type) {
	case ACPI_TYPE_STRING:

		/* No conversion necessary */

		*result_desc = obj_desc;
		return_ACPI_STATUS(AE_OK);

	case ACPI_TYPE_INTEGER:

		switch (type) {
		case ACPI_EXPLICIT_CONVERT_DECIMAL:
			/*
			 * From to_decimal_string, integer source.
			 *
			 * Make room for the maximum decimal number size
			 */
			string_length = ACPI_MAX_DECIMAL_DIGITS;
			base = 10;
			break;

		default:

			/* Two hex string characters for each integer byte */

			string_length = ACPI_MUL_2(acpi_gbl_integer_byte_width);
			break;
		}

		/*
		 * Create a new String
		 * Need enough space for one ASCII integer (plus null terminator)
		 */
		return_desc =
		    acpi_ut_create_string_object((acpi_size)string_length);
		if (!return_desc) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		new_buf = return_desc->buffer.pointer;

		/* Convert integer to string */

		string_length =
		    acpi_ex_convert_to_ascii(obj_desc->integer.value, base,
					     new_buf,
					     acpi_gbl_integer_byte_width);

		/* Null terminate at the correct place */

		return_desc->string.length = string_length;
		new_buf[string_length] = 0;
		break;

	case ACPI_TYPE_BUFFER:

		/* Setup string length, base, and separator */

		switch (type) {
		case ACPI_EXPLICIT_CONVERT_DECIMAL:	/* Used by to_decimal_string */
			/*
			 * Explicit conversion from the to_decimal_string ASL operator.
			 *
			 * From ACPI: "If the input is a buffer, it is converted to a
			 * a string of decimal values separated by commas."
			 */
			base = 10;

			/*
			 * Calculate the final string length. Individual string values
			 * are variable length (include separator for each)
			 */
			for (i = 0; i < obj_desc->buffer.length; i++) {
				if (obj_desc->buffer.pointer[i] >= 100) {
					string_length += 4;
				} else if (obj_desc->buffer.pointer[i] >= 10) {
					string_length += 3;
				} else {
					string_length += 2;
				}
			}
			break;

		case ACPI_IMPLICIT_CONVERT_HEX:
			/*
			 * Implicit buffer-to-string conversion
			 *
			 * From the ACPI spec:
			 * "The entire contents of the buffer are converted to a string of
			 * two-character hexadecimal numbers, each separated by a space."
			 *
			 * Each hex number is prefixed with 0x (11/2018)
			 */
			separator = ' ';
			string_length = (obj_desc->buffer.length * 5);
			break;

		case ACPI_EXPLICIT_CONVERT_HEX:
			/*
			 * Explicit conversion from the to_hex_string ASL operator.
			 *
			 * From ACPI: "If Data is a buffer, it is converted to a string of
			 * hexadecimal values separated by commas."
			 *
			 * Each hex number is prefixed with 0x (11/2018)
			 */
			separator = ',';
			string_length = (obj_desc->buffer.length * 5);
			break;

		default:
			return_ACPI_STATUS(AE_BAD_PARAMETER);
		}

		/*
		 * Create a new string object and string buffer
		 * (-1 because of extra separator included in string_length from above)
		 * Allow creation of zero-length strings from zero-length buffers.
		 */
		if (string_length) {
			string_length--;
		}

		return_desc =
		    acpi_ut_create_string_object((acpi_size)string_length);
		if (!return_desc) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		new_buf = return_desc->buffer.pointer;

		/*
		 * Convert buffer bytes to hex or decimal values
		 * (separated by commas or spaces)
		 */
		for (i = 0; i < obj_desc->buffer.length; i++) {
			if (base == 16) {

				/* Emit 0x prefix for explicit/implicit hex conversion */

				*new_buf++ = '0';
				*new_buf++ = 'x';
			}

			new_buf += acpi_ex_convert_to_ascii((u64) obj_desc->
							    buffer.pointer[i],
							    base, new_buf, 1);

			/* Each digit is separated by either a comma or space */

			*new_buf++ = separator;
		}

		/*
		 * Null terminate the string
		 * (overwrites final comma/space from above)
		 */
		if (obj_desc->buffer.length) {
			new_buf--;
		}
		*new_buf = 0;
		break;

	default:

		return_ACPI_STATUS(AE_TYPE);
	}

	*result_desc = return_desc;
	return_ACPI_STATUS(AE_OK);
}