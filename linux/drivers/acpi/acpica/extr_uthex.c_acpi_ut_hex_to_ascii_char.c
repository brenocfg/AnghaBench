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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 char* acpi_gbl_hex_to_ascii ; 
 int /*<<< orphan*/  acpi_ut_short_shift_right (int,int /*<<< orphan*/ ,int*) ; 

char acpi_ut_hex_to_ascii_char(u64 integer, u32 position)
{
	u64 index;

	acpi_ut_short_shift_right(integer, position, &index);
	return (acpi_gbl_hex_to_ascii[index & 0xF]);
}