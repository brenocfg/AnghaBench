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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ITERATIONS_LONG ; 
 scalar_t__ SONYPI_ACPI_ACTIVE ; 
 int /*<<< orphan*/  SONYPI_CST_IOPORT ; 
 int /*<<< orphan*/  SONYPI_DATA_IOPORT ; 
 int ec_read (int,int*) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_command (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sonypi_ec_read(u8 addr, u8 *value)
{
#ifdef CONFIG_ACPI
	if (SONYPI_ACPI_ACTIVE)
		return ec_read(addr, value);
#endif
	wait_on_command(1, inb_p(SONYPI_CST_IOPORT) & 3, ITERATIONS_LONG);
	outb_p(0x80, SONYPI_CST_IOPORT);
	wait_on_command(0, inb_p(SONYPI_CST_IOPORT) & 2, ITERATIONS_LONG);
	outb_p(addr, SONYPI_DATA_IOPORT);
	wait_on_command(0, inb_p(SONYPI_CST_IOPORT) & 2, ITERATIONS_LONG);
	*value = inb_p(SONYPI_DATA_IOPORT);
	return 0;
}