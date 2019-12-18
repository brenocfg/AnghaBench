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
typedef  scalar_t__ u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int acpi_ut_dword_byte_swap (int) ; 
 char acpi_ut_hex_to_ascii_char (scalar_t__,int) ; 

void acpi_ex_eisa_id_to_string(char *out_string, u64 compressed_id)
{
	u32 swapped_id;

	ACPI_FUNCTION_ENTRY();

	/* The EISAID should be a 32-bit integer */

	if (compressed_id > ACPI_UINT32_MAX) {
		ACPI_WARNING((AE_INFO,
			      "Expected EISAID is larger than 32 bits: "
			      "0x%8.8X%8.8X, truncating",
			      ACPI_FORMAT_UINT64(compressed_id)));
	}

	/* Swap ID to big-endian to get contiguous bits */

	swapped_id = acpi_ut_dword_byte_swap((u32)compressed_id);

	/* First 3 bytes are uppercase letters. Next 4 bytes are hexadecimal */

	out_string[0] =
	    (char)(0x40 + (((unsigned long)swapped_id >> 26) & 0x1F));
	out_string[1] = (char)(0x40 + ((swapped_id >> 21) & 0x1F));
	out_string[2] = (char)(0x40 + ((swapped_id >> 16) & 0x1F));
	out_string[3] = acpi_ut_hex_to_ascii_char((u64) swapped_id, 12);
	out_string[4] = acpi_ut_hex_to_ascii_char((u64) swapped_id, 8);
	out_string[5] = acpi_ut_hex_to_ascii_char((u64) swapped_id, 4);
	out_string[6] = acpi_ut_hex_to_ascii_char((u64) swapped_id, 0);
	out_string[7] = 0;
}