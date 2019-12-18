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
typedef  scalar_t__ uint32_t ;
struct uart_bas {int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 scalar_t__ SBBC_CONS_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBBC_PCI_INT_STATUS ; 
 scalar_t__ SBBC_REGS_READ_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBBC_REGS_WRITE_4 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SBBC_SRAM_CONS_BRK ; 
 scalar_t__ SBBC_SRAM_CONS_IN ; 
 scalar_t__ SBBC_SRAM_CONS_SPACE_OUT ; 
 scalar_t__ SBBC_SRAM_READ_4 (scalar_t__) ; 
 int /*<<< orphan*/  SBBC_SRAM_WRITE_4 (scalar_t__,int /*<<< orphan*/ ) ; 
 int SER_INT_BREAK ; 
 int SER_INT_RXREADY ; 
 int SER_INT_TXIDLE ; 
 int /*<<< orphan*/  cons_out_rdptr ; 
 int /*<<< orphan*/  cons_out_wrptr ; 
 scalar_t__ sbbc_scsolir ; 
 scalar_t__ sbbc_solcons ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sbbc_uart_bus_ipend(struct uart_softc *sc)
{
	struct uart_bas *bas;
	bus_space_tag_t bst;
	bus_space_handle_t bsh;
	int ipend;
	uint32_t reason, status;

	bas = &sc->sc_bas;
	bst = bas->bst;
	bsh = bas->bsh;

	uart_lock(sc->sc_hwmtx);
	status = SBBC_REGS_READ_4(SBBC_PCI_INT_STATUS);
	if (status == 0) {
		uart_unlock(sc->sc_hwmtx);
		return (0);
	}

	/*
	 * Unfortunately, we can't use compare and swap for non-cachable
	 * memory.
	 */
	reason = SBBC_SRAM_READ_4(sbbc_scsolir);
	SBBC_SRAM_WRITE_4(sbbc_scsolir, 0);
	uart_barrier(bas);
	/* Acknowledge the interrupt. */
	SBBC_REGS_WRITE_4(SBBC_PCI_INT_STATUS, status);
	uart_barrier(bas);

	uart_unlock(sc->sc_hwmtx);

	ipend = 0;
	if ((reason & SBBC_SRAM_CONS_IN) != 0)
		ipend |= SER_INT_RXREADY;
	if ((reason & SBBC_SRAM_CONS_BRK) != 0)
		ipend |= SER_INT_BREAK;
	if ((reason & SBBC_SRAM_CONS_SPACE_OUT) != 0 &&
	    SBBC_SRAM_READ_4(sbbc_solcons + SBBC_CONS_OFF(cons_out_rdptr)) ==
	    SBBC_SRAM_READ_4(sbbc_solcons + SBBC_CONS_OFF(cons_out_wrptr)))
		ipend |= SER_INT_TXIDLE;
	return (ipend);
}