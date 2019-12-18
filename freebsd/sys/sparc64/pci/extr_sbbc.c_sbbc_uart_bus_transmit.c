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
struct uart_softc {int sc_txdatasz; int sc_txbusy; int /*<<< orphan*/  sc_hwmtx; int /*<<< orphan*/ * sc_txbuf; struct uart_bas sc_bas; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 scalar_t__ SBBC_CONS_OFF (int /*<<< orphan*/ ) ; 
 scalar_t__ SBBC_SRAM_CONS_OUT ; 
 scalar_t__ SBBC_SRAM_READ_4 (scalar_t__) ; 
 int /*<<< orphan*/  SBBC_SRAM_WRITE_1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBBC_SRAM_WRITE_4 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cons_out_begin ; 
 int /*<<< orphan*/  cons_out_end ; 
 int /*<<< orphan*/  cons_out_wrptr ; 
 int /*<<< orphan*/  sbbc_send_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sbbc_solcons ; 
 scalar_t__ sbbc_solscir ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sbbc_uart_bus_transmit(struct uart_softc *sc)
{
	struct uart_bas *bas;
	bus_space_tag_t bst;
	bus_space_handle_t bsh;
	int i;
	uint32_t end, wrptr;

	bas = &sc->sc_bas;
	bst = bas->bst;
	bsh = bas->bsh;

	uart_lock(sc->sc_hwmtx);

	end = SBBC_SRAM_READ_4(sbbc_solcons + SBBC_CONS_OFF(cons_out_end));
	wrptr = SBBC_SRAM_READ_4(sbbc_solcons +
	    SBBC_CONS_OFF(cons_out_wrptr));
	for (i = 0; i < sc->sc_txdatasz; i++) {
		SBBC_SRAM_WRITE_1(sbbc_solcons + wrptr, sc->sc_txbuf[i]);
		if (++wrptr == end)
			wrptr = SBBC_SRAM_READ_4(sbbc_solcons +
			    SBBC_CONS_OFF(cons_out_begin));
	}
	uart_barrier(bas);
	SBBC_SRAM_WRITE_4(sbbc_solcons + SBBC_CONS_OFF(cons_out_wrptr),
	    wrptr);
	uart_barrier(bas);
	SBBC_SRAM_WRITE_4(sbbc_solscir, SBBC_SRAM_READ_4(sbbc_solscir) |
	    SBBC_SRAM_CONS_OUT);
	uart_barrier(bas);
	sbbc_send_intr(bst, bsh);
	sc->sc_txbusy = 1;

	uart_unlock(sc->sc_hwmtx);
	return (0);
}