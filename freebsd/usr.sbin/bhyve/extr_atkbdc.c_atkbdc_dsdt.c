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

/* Variables and functions */
 int /*<<< orphan*/  KBD_DATA_PORT ; 
 int /*<<< orphan*/  KBD_STS_CTL_PORT ; 
 int /*<<< orphan*/  dsdt_fixed_ioport (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsdt_fixed_irq (int) ; 
 int /*<<< orphan*/  dsdt_indent (int) ; 
 int /*<<< orphan*/  dsdt_line (char*) ; 
 int /*<<< orphan*/  dsdt_unindent (int) ; 

__attribute__((used)) static void
atkbdc_dsdt(void)
{

	dsdt_line("");
	dsdt_line("Device (KBD)");
	dsdt_line("{");
	dsdt_line("  Name (_HID, EisaId (\"PNP0303\"))");
	dsdt_line("  Name (_CRS, ResourceTemplate ()");
	dsdt_line("  {");
	dsdt_indent(2);
	dsdt_fixed_ioport(KBD_DATA_PORT, 1);
	dsdt_fixed_ioport(KBD_STS_CTL_PORT, 1);
	dsdt_fixed_irq(1);
	dsdt_unindent(2);
	dsdt_line("  })");
	dsdt_line("}");

	dsdt_line("");
	dsdt_line("Device (MOU)");
	dsdt_line("{");
	dsdt_line("  Name (_HID, EisaId (\"PNP0F13\"))");
	dsdt_line("  Name (_CRS, ResourceTemplate ()");
	dsdt_line("  {");
	dsdt_indent(2);
	dsdt_fixed_ioport(KBD_DATA_PORT, 1);
	dsdt_fixed_ioport(KBD_STS_CTL_PORT, 1);
	dsdt_fixed_irq(12);
	dsdt_unindent(2);
	dsdt_line("  })");
	dsdt_line("}");
}