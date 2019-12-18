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
typedef  size_t u32 ;

/* Variables and functions */
 int /*<<< orphan*/  isprint (scalar_t__) ; 

void acpi_ut_check_and_repair_ascii(u8 *name, char *repaired_name, u32 count)
{
	u32 i;

	for (i = 0; i < count; i++) {
		repaired_name[i] = (char)name[i];

		if (!name[i]) {
			return;
		}
		if (!isprint(name[i])) {
			repaired_name[i] = ' ';
		}
	}
}