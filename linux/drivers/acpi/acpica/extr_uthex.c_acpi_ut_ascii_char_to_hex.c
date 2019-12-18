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

/* Variables and functions */

u8 acpi_ut_ascii_char_to_hex(int hex_char)
{

	/* Values 0-9 */

	if (hex_char <= '9') {
		return ((u8)(hex_char - '0'));
	}

	/* Upper case A-F */

	if (hex_char <= 'F') {
		return ((u8)(hex_char - 0x37));
	}

	/* Lower case a-f */

	return ((u8)(hex_char - 0x57));
}