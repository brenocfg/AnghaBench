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
struct mtx {int dummy; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int SBBC_CONS_OFF (int /*<<< orphan*/ ) ; 
 int SBBC_SRAM_CONS_SPACE_IN ; 
 int SBBC_SRAM_READ_1 (int) ; 
 int SBBC_SRAM_READ_4 (int) ; 
 int /*<<< orphan*/  SBBC_SRAM_WRITE_4 (int,int) ; 
 int /*<<< orphan*/  cons_in_begin ; 
 int /*<<< orphan*/  cons_in_end ; 
 int /*<<< orphan*/  cons_in_rdptr ; 
 int /*<<< orphan*/  sbbc_send_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sbbc_solcons ; 
 int sbbc_solscir ; 
 scalar_t__ sbbc_uart_rxready (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (struct mtx*) ; 
 int /*<<< orphan*/  uart_unlock (struct mtx*) ; 

__attribute__((used)) static int
sbbc_uart_getc(struct uart_bas *bas, struct mtx *hwmtx)
{
	bus_space_tag_t bst;
	bus_space_handle_t bsh;
	int c;
	uint32_t rdptr;

	bst = bas->bst;
	bsh = bas->bsh;

	uart_lock(hwmtx);

	while (sbbc_uart_rxready(bas) == 0) {
		uart_unlock(hwmtx);
		DELAY(4);
		uart_lock(hwmtx);
	}

	rdptr = SBBC_SRAM_READ_4(sbbc_solcons + SBBC_CONS_OFF(cons_in_rdptr));
	c = SBBC_SRAM_READ_1(sbbc_solcons + rdptr);
	uart_barrier(bas);
	if (++rdptr == SBBC_SRAM_READ_4(sbbc_solcons +
	    SBBC_CONS_OFF(cons_in_end)))
		rdptr = SBBC_SRAM_READ_4(sbbc_solcons +
		    SBBC_CONS_OFF(cons_in_begin));
	SBBC_SRAM_WRITE_4(sbbc_solcons + SBBC_CONS_OFF(cons_in_rdptr),
	    rdptr);
	uart_barrier(bas);
	SBBC_SRAM_WRITE_4(sbbc_solscir, SBBC_SRAM_READ_4(sbbc_solscir) |
	    SBBC_SRAM_CONS_SPACE_IN);
	uart_barrier(bas);
	sbbc_send_intr(bst, bsh);

	uart_unlock(hwmtx);
	return (c);
}