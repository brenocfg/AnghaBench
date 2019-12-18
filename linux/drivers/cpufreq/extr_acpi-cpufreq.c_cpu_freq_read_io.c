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
struct acpi_pct_register {int /*<<< orphan*/  bit_width; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_os_read_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 cpu_freq_read_io(struct acpi_pct_register *reg)
{
	u32 val;

	acpi_os_read_port(reg->address, &val, reg->bit_width);
	return val;
}