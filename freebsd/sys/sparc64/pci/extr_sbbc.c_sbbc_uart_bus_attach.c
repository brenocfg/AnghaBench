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
typedef  int uint32_t ;
struct uart_bas {int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 scalar_t__ SBBC_CONS_OFF (int /*<<< orphan*/ ) ; 
 int SBBC_PCI_ENABLE_INT_A ; 
 int /*<<< orphan*/  SBBC_PCI_INT_ENABLE ; 
 int /*<<< orphan*/  SBBC_PCI_INT_STATUS ; 
 int /*<<< orphan*/  SBBC_REGS_WRITE_4 (int /*<<< orphan*/ ,int) ; 
 int SBBC_SRAM_CONS_BRK ; 
 int SBBC_SRAM_CONS_IN ; 
 int SBBC_SRAM_CONS_SPACE_OUT ; 
 int SBBC_SRAM_READ_4 (scalar_t__) ; 
 int /*<<< orphan*/  SBBC_SRAM_WRITE_4 (scalar_t__,int) ; 
 int /*<<< orphan*/  cons_out_rdptr ; 
 int /*<<< orphan*/  cons_out_wrptr ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 scalar_t__ sbbc_scsolie ; 
 scalar_t__ sbbc_scsolir ; 
 scalar_t__ sbbc_solcons ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sbbc_uart_bus_attach(struct uart_softc *sc)
{
	struct uart_bas *bas;
	bus_space_tag_t bst;
	bus_space_handle_t bsh;
	uint32_t wrptr;

	bas = &sc->sc_bas;
	bst = bas->bst;
	bsh = bas->bsh;

	uart_lock(sc->sc_hwmtx);

	/*
	 * Let the current output drain before enabling interrupts.  Not
	 * doing so tends to cause lost output when turning them on.
	 */
	wrptr = SBBC_SRAM_READ_4(sbbc_solcons +
	    SBBC_CONS_OFF(cons_out_wrptr));
	while (SBBC_SRAM_READ_4(sbbc_solcons +
	    SBBC_CONS_OFF(cons_out_rdptr)) != wrptr);
		cpu_spinwait();

	/* Clear and acknowledge possibly outstanding interrupts. */
	SBBC_SRAM_WRITE_4(sbbc_scsolir, 0);
	uart_barrier(bas);
	SBBC_REGS_WRITE_4(SBBC_PCI_INT_STATUS,
	    SBBC_SRAM_READ_4(sbbc_scsolir));
	uart_barrier(bas);
	/* Enable PCI interrupts. */
	SBBC_REGS_WRITE_4(SBBC_PCI_INT_ENABLE, SBBC_PCI_ENABLE_INT_A);
	uart_barrier(bas);
	/* Enable input from and output to SC as well as break interrupts. */
	SBBC_SRAM_WRITE_4(sbbc_scsolie, SBBC_SRAM_READ_4(sbbc_scsolie) |
	    SBBC_SRAM_CONS_IN | SBBC_SRAM_CONS_BRK |
	    SBBC_SRAM_CONS_SPACE_OUT);
	uart_barrier(bas);

	uart_unlock(sc->sc_hwmtx);
	return (0);
}