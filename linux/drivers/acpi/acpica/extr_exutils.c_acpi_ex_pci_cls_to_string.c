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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 char acpi_ut_hex_to_ascii_char (int /*<<< orphan*/ ,int) ; 

void acpi_ex_pci_cls_to_string(char *out_string, u8 class_code[3])
{

	ACPI_FUNCTION_ENTRY();

	/* All 3 bytes are hexadecimal */

	out_string[0] = acpi_ut_hex_to_ascii_char((u64)class_code[0], 4);
	out_string[1] = acpi_ut_hex_to_ascii_char((u64)class_code[0], 0);
	out_string[2] = acpi_ut_hex_to_ascii_char((u64)class_code[1], 4);
	out_string[3] = acpi_ut_hex_to_ascii_char((u64)class_code[1], 0);
	out_string[4] = acpi_ut_hex_to_ascii_char((u64)class_code[2], 4);
	out_string[5] = acpi_ut_hex_to_ascii_char((u64)class_code[2], 0);
	out_string[6] = 0;
}