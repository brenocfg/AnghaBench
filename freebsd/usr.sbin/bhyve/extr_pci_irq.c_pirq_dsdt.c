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
 int /*<<< orphan*/  IRQ_PERMITTED (int) ; 
 int PIRQ_DIS ; 
 int PIRQ_IRQ ; 
 int /*<<< orphan*/  asprintf (char**,char*,...) ; 
 int /*<<< orphan*/  dsdt_line (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  irq_counts ; 
 int nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pirqs ; 

__attribute__((used)) static void
pirq_dsdt(void)
{
	char *irq_prs, *old;
	int irq, pin;

	irq_prs = NULL;
	for (irq = 0; irq < nitems(irq_counts); irq++) {
		if (!IRQ_PERMITTED(irq))
			continue;
		if (irq_prs == NULL)
			asprintf(&irq_prs, "%d", irq);
		else {
			old = irq_prs;
			asprintf(&irq_prs, "%s,%d", old, irq);
			free(old);
		}
	}

	/*
	 * A helper method to validate a link register's value.  This
	 * duplicates pirq_valid_irq().
	 */
	dsdt_line("");
	dsdt_line("Method (PIRV, 1, NotSerialized)");
	dsdt_line("{");
	dsdt_line("  If (And (Arg0, 0x%02X))", PIRQ_DIS);
	dsdt_line("  {");
	dsdt_line("    Return (0x00)");
	dsdt_line("  }");
	dsdt_line("  And (Arg0, 0x%02X, Local0)", PIRQ_IRQ);
	dsdt_line("  If (LLess (Local0, 0x03))");
	dsdt_line("  {");
	dsdt_line("    Return (0x00)");
	dsdt_line("  }");
	dsdt_line("  If (LEqual (Local0, 0x08))");
	dsdt_line("  {");
	dsdt_line("    Return (0x00)");
	dsdt_line("  }");
	dsdt_line("  If (LEqual (Local0, 0x0D))");
	dsdt_line("  {");
	dsdt_line("    Return (0x00)");
	dsdt_line("  }");
	dsdt_line("  Return (0x01)");
	dsdt_line("}");

	for (pin = 0; pin < nitems(pirqs); pin++) {
		dsdt_line("");
		dsdt_line("Device (LNK%c)", 'A' + pin);
		dsdt_line("{");
		dsdt_line("  Name (_HID, EisaId (\"PNP0C0F\"))");
		dsdt_line("  Name (_UID, 0x%02X)", pin + 1);
		dsdt_line("  Method (_STA, 0, NotSerialized)");
		dsdt_line("  {");
		dsdt_line("    If (PIRV (PIR%c))", 'A' + pin);
		dsdt_line("    {");
		dsdt_line("       Return (0x0B)");
		dsdt_line("    }");
		dsdt_line("    Else");
		dsdt_line("    {");
		dsdt_line("       Return (0x09)");
		dsdt_line("    }");
		dsdt_line("  }");
		dsdt_line("  Name (_PRS, ResourceTemplate ()");
		dsdt_line("  {");
		dsdt_line("    IRQ (Level, ActiveLow, Shared, )");
		dsdt_line("      {%s}", irq_prs);
		dsdt_line("  })");
		dsdt_line("  Name (CB%02X, ResourceTemplate ()", pin + 1);
		dsdt_line("  {");
		dsdt_line("    IRQ (Level, ActiveLow, Shared, )");
		dsdt_line("      {}");
		dsdt_line("  })");
		dsdt_line("  CreateWordField (CB%02X, 0x01, CIR%c)",
		    pin + 1, 'A' + pin);
		dsdt_line("  Method (_CRS, 0, NotSerialized)");
		dsdt_line("  {");
		dsdt_line("    And (PIR%c, 0x%02X, Local0)", 'A' + pin,
		    PIRQ_DIS | PIRQ_IRQ);
		dsdt_line("    If (PIRV (Local0))");
		dsdt_line("    {");
		dsdt_line("      ShiftLeft (0x01, Local0, CIR%c)", 'A' + pin);
		dsdt_line("    }");
		dsdt_line("    Else");
		dsdt_line("    {");
		dsdt_line("      Store (0x00, CIR%c)", 'A' + pin);
		dsdt_line("    }");
		dsdt_line("    Return (CB%02X)", pin + 1);
		dsdt_line("  }");
		dsdt_line("  Method (_DIS, 0, NotSerialized)");
		dsdt_line("  {");
		dsdt_line("    Store (0x80, PIR%c)", 'A' + pin);
		dsdt_line("  }");
		dsdt_line("  Method (_SRS, 1, NotSerialized)");
		dsdt_line("  {");
		dsdt_line("    CreateWordField (Arg0, 0x01, SIR%c)", 'A' + pin);
		dsdt_line("    FindSetRightBit (SIR%c, Local0)", 'A' + pin);
		dsdt_line("    Store (Decrement (Local0), PIR%c)", 'A' + pin);
		dsdt_line("  }");
		dsdt_line("}");
	}
	free(irq_prs);
}