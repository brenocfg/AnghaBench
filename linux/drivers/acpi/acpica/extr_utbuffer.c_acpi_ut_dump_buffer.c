#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  size_t acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_MOVE_16_TO_32 (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_MOVE_32_TO_32 (int*,int /*<<< orphan*/ *) ; 
#define  DB_BYTE_DISPLAY 131 
#define  DB_DWORD_DISPLAY 130 
#define  DB_QWORD_DISPLAY 129 
#define  DB_WORD_DISPLAY 128 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 scalar_t__ isprint (int /*<<< orphan*/ ) ; 

void acpi_ut_dump_buffer(u8 *buffer, u32 count, u32 display, u32 base_offset)
{
	u32 i = 0;
	u32 j;
	u32 temp32;
	u8 buf_char;

	if (!buffer) {
		acpi_os_printf("Null Buffer Pointer in DumpBuffer!\n");
		return;
	}

	if ((count < 4) || (count & 0x01)) {
		display = DB_BYTE_DISPLAY;
	}

	/* Nasty little dump buffer routine! */

	while (i < count) {

		/* Print current offset */

		acpi_os_printf("%8.4X: ", (base_offset + i));

		/* Print 16 hex chars */

		for (j = 0; j < 16;) {
			if (i + j >= count) {

				/* Dump fill spaces */

				acpi_os_printf("%*s", ((display * 2) + 1), " ");
				j += display;
				continue;
			}

			switch (display) {
			case DB_BYTE_DISPLAY:
			default:	/* Default is BYTE display */

				acpi_os_printf("%02X ",
					       buffer[(acpi_size)i + j]);
				break;

			case DB_WORD_DISPLAY:

				ACPI_MOVE_16_TO_32(&temp32,
						   &buffer[(acpi_size)i + j]);
				acpi_os_printf("%04X ", temp32);
				break;

			case DB_DWORD_DISPLAY:

				ACPI_MOVE_32_TO_32(&temp32,
						   &buffer[(acpi_size)i + j]);
				acpi_os_printf("%08X ", temp32);
				break;

			case DB_QWORD_DISPLAY:

				ACPI_MOVE_32_TO_32(&temp32,
						   &buffer[(acpi_size)i + j]);
				acpi_os_printf("%08X", temp32);

				ACPI_MOVE_32_TO_32(&temp32,
						   &buffer[(acpi_size)i + j +
							   4]);
				acpi_os_printf("%08X ", temp32);
				break;
			}

			j += display;
		}

		/*
		 * Print the ASCII equivalent characters but watch out for the bad
		 * unprintable ones (printable chars are 0x20 through 0x7E)
		 */
		acpi_os_printf(" ");
		for (j = 0; j < 16; j++) {
			if (i + j >= count) {
				acpi_os_printf("\n");
				return;
			}

			/*
			 * Add comment characters so rest of line is ignored when
			 * compiled
			 */
			if (j == 0) {
				acpi_os_printf("// ");
			}

			buf_char = buffer[(acpi_size)i + j];
			if (isprint(buf_char)) {
				acpi_os_printf("%c", buf_char);
			} else {
				acpi_os_printf(".");
			}
		}

		/* Done with that line. */

		acpi_os_printf("\n");
		i += 16;
	}

	return;
}