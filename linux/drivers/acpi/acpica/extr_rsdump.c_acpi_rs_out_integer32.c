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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_os_printf (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_rs_out_integer32(const char *title, u32 value)
{

	acpi_os_printf("%27s : %8.8X\n", title, value);
}