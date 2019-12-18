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
struct lpc_uart_softc {int /*<<< orphan*/  irq; int /*<<< orphan*/  iobase; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int LPC_UART_NUM ; 
 int /*<<< orphan*/  UART_IO_BAR_SIZE ; 
 int /*<<< orphan*/  dsdt_fixed_ioport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsdt_fixed_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsdt_indent (int) ; 
 int /*<<< orphan*/  dsdt_line (char*,...) ; 
 int /*<<< orphan*/  dsdt_unindent (int) ; 
 int /*<<< orphan*/ * lpc_uart_names ; 
 struct lpc_uart_softc* lpc_uart_softc ; 

__attribute__((used)) static void
pci_lpc_uart_dsdt(void)
{
	struct lpc_uart_softc *sc;
	int unit;

	for (unit = 0; unit < LPC_UART_NUM; unit++) {
		sc = &lpc_uart_softc[unit];
		if (!sc->enabled)
			continue;
		dsdt_line("");
		dsdt_line("Device (%s)", lpc_uart_names[unit]);
		dsdt_line("{");
		dsdt_line("  Name (_HID, EisaId (\"PNP0501\"))");
		dsdt_line("  Name (_UID, %d)", unit + 1);
		dsdt_line("  Name (_CRS, ResourceTemplate ()");
		dsdt_line("  {");
		dsdt_indent(2);
		dsdt_fixed_ioport(sc->iobase, UART_IO_BAR_SIZE);
		dsdt_fixed_irq(sc->irq);
		dsdt_unindent(2);
		dsdt_line("  })");
		dsdt_line("}");
	}
}